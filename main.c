#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"
#include "main.h"

#define BUZZER_ON 100
#define BUZZER_OFF 0
#define BUZZER_DURATION 1000
#define TMR2_COUNTER 1000
#define MIN_PRESSURE_THRESHOLD 10
#define MAX_PRESSURE_THRESHOLD 150
#define MAX_INPUT_LENGTH 4
#define MAX_TFT_LENGTH 50
#define MAX_ADC_VALUE 1023.0
#define VREF 5.0

bool bufferData = false;
bool can_exit_loop = false;
bool user_input = false;
bool show_main_menu = true;
bool show_error = false;
bool set_threshold = false;
bool alarm_disabled = false; // disable the alarm
bool user_override = false; // user can change stepper opening manually if true

char receivedData;
char string[MAX_TFT_LENGTH] = "";
int option = 0;
int option_2nd = 0;
int type = 0;
int count = 0; // Stores timer 2 counter

// 0.263658V -> 0kPa
// 4.87084V -> 250kPa
// y=mx+b
// m=(y2-y1)/(x2-x1) = (250 - 0)/(4.87084 - 0.263658) = 54.263104865403624167658234469574 ~= 54.263105
// b=y2-m*x1 = 0 - 54.263105 * 0.263658 = -14.306901702602588740796434783779 ~= -14.306917
const static double m = 54.263105;
const static double b = -14.306917;

// uint16_t *paulo = &image_data_paulo[0];
// uint16_t *diogo = &image_data_diogo[0];

struct sensor mpx4250 = {
    .min_threshold = MIN_PRESSURE_THRESHOLD,
    .max_threshold = MAX_PRESSURE_THRESHOLD,
    .current_data = 0.0,
    .previous_data = 0.0
};

struct valve stepper = {
    .current_angle = 0.0,
    .current_angle_percentage = 0.0,
    .target_angle = 0.0,
    .previous_angle = 0.0,
    .user_input_angle = 0.0
};

struct data adc = {
    .voltage = 0.0,
    .result = 0.0,
    .update = false
};

void INT0_interruptHandler(void) {
    alarm_disabled = !alarm_disabled;
    EXT_INT0_InterruptFlagClear();
}

void TMR0_interruptHandler(void) {
    LED_LAT = !LED_LAT;
    TMR0_InterruptFlagClear();
}

void TMR1_interruptHandler(void) {
    ADC_StartConversion();
    TMR1_InterruptFlagClear();
}

void TMR2_interruptHandler(void) {
    count++;
    if (count >= TMR2_COUNTER) {
        EPWM1_LoadDutyValue(BUZZER_ON);
        if (count >= (TMR2_COUNTER + BUZZER_DURATION)) {
            EPWM1_LoadDutyValue(BUZZER_OFF);
            count = 0;
        }
    }
    TMR2_InterruptFlagClear();
}

void ADC_interruptHandler(void) {
    adc.update = true;
    adc.result = ADC_GetConversionResult();
}

void updatePressureFromADC() {
    adc.voltage = (double) adc.result * VREF / MAX_ADC_VALUE;
    mpx4250.current_data = m * adc.voltage + b;
    adc.update = false;
}

void shutdownAlarm() {
    LED_LAT = 0;
    EPWM1_LoadDutyValue(0);
    TMR0_StopTimer();
    TMR2_StopTimer();
    count = TMR2_COUNTER;
    lcd_draw_string(20, 80, "                                                 ", RED, BLACK);
}

void triggerAlarm() {
    if (mpx4250.current_data <= mpx4250.min_threshold) {
        snprintf(string, sizeof (string), "ALARME! Pressao baixa!");
    } else {
        snprintf(string, sizeof (string), "ALARME! Pressao alta!");
    }
    lcd_draw_string(20, 80, string, RED, BLACK);
    TMR0_StartTimer();
    TMR2_StartTimer();
}

bool pressureOutsideThreshold() {
    return (mpx4250.current_data <= mpx4250.min_threshold || mpx4250.current_data >= mpx4250.max_threshold);
}

bool dataIsDifferent(double old_data, double new_data) {
    if (old_data != new_data) {
        return true;
    } else {
        return false;
    }
}

int setPressureThreshold(int original_threshold) {
    int i = 0;
    char str[MAX_INPUT_LENGTH] = {0}; // Initialize the string buffer
    bool set_threshold = true;

    while (set_threshold) {
        if (EUSART1_is_rx_ready()) {
            char receivedData = EUSART1_Read();

            if (isdigit(receivedData) && i < MAX_INPUT_LENGTH - 1) {
                str[i++] = receivedData;
                EUSART1_Write(receivedData);
            } else if (receivedData == 8 && i > 0) { // Backspace
                i--;
                EUSART1_Write(8);
                EUSART1_Write(' '); // Clear the character on terminal
                EUSART1_Write(8);
            } else if (receivedData == 13) { // Enter
                set_threshold = false;
                str[i] = '\0';
                return atoi(str);
            }
        }
    }

    return original_threshold; // Return the original threshold if not updated
}

void rotateSteps(int steps) {
    const char sequence[4] = {0b0001, 0b0010, 0b0100, 0b1000};

    for (int i = 0; i < steps; i++) {
        IN1_LAT = (sequence[i % 4] & 0b0001) > 0 ? 1 : 0;
        IN2_LAT = (sequence[i % 4] & 0b0010) > 0 ? 1 : 0;
        IN3_LAT = (sequence[i % 4] & 0b0100) > 0 ? 1 : 0;
        IN4_LAT = (sequence[i % 4] & 0b1000) > 0 ? 1 : 0;
    }
}

int readDigitFromSerial() {
    receivedData = EUSART1_Read();
    if (isdigit(receivedData)) {
        EUSART1_Write(receivedData);
        bufferData = true;
        return receivedData;
    }
}

void mainMenu() {
    EUSART1_Write(12);
    printf("\r\n# SISTEMA DE CONTROLO DA PRESSAO DE UMA CAMARA DE COMBUSTAO #\r\n");

    printf("\r\n[1] - Trocar o tipo de controlo da pressao");
    printf("\r\n[2] - Definicao do grau de abertura da valvula");
    printf("\r\n[3] - Definicao dos limiares do alarme para a pressao (MIN/MAX)\r\n");

    printf("\r\nTipo de controlo: %s", user_override ? "Manual" : "Automatico");
    printf("\r\nValor de pressao: %.2f kPa", mpx4250.current_data);
    printf("\r\nAbertura da valvula: %d %%\r\n", stepper.current_angle_percentage);

    if (show_error) {
        printf("\r\nControlo da pressao tem de ser manual para definir um grau de abertura da valvula.\r\n");
    }

    printf("\r\nOpcao: ");
}

void valveMenu() {
    EUSART1_Write(12);
    printf("\r\n[1] - 0%%");
    printf("\r\n[2] - 25%%");
    printf("\r\n[3] - 50%%");
    printf("\r\n[4] - 75%%");
    printf("\r\n[5] - 100%%");
    printf("\r\n[0] - Sair (Controlo da pressao -> Automatico)\r\n");

    printf("\r\nOpcao: ");
}

void main(void) {
    SYSTEM_Initialize();
    ADC_SelectChannel(MPX4250_AN);


    INT0_SetInterruptHandler(INT0_interruptHandler);
    TMR0_SetInterruptHandler(TMR0_interruptHandler);
    TMR1_SetInterruptHandler(TMR1_interruptHandler);
    TMR2_SetInterruptHandler(TMR2_interruptHandler);
    ADC_SetInterruptHandler(ADC_interruptHandler);

    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    INTERRUPT_PeripheralInterruptEnable();

    SPI2_Open(SPI2_DEFAULT);

    shutdownAlarm();

    lcd_init();


    lcd_draw_string(13, 205, "SISTEMA DE CONTROLO DA PRESSAO", FUCHSIA, BLACK);
    lcd_draw_string(40, 175, "DA CAMARA DE COMBUSTAO", FUCHSIA, BLACK);
    lcd_draw_string(20, 45, "Autores: Paulo Sousa", YELLOW, BLACK);
    lcd_draw_string(90, 25, "Diogo Cravo", YELLOW, BLACK);
    //lcd_draw_image(180, 0, 75, 92, paulo);
    // lcd_draw_image(180, 0, 75, 92, diogo);

    while (1) {
        if (adc.update) {
            updatePressureFromADC();
        }

        if (alarm_disabled) {
            shutdownAlarm();
        } else {
            if (pressureOutsideThreshold()) {
                triggerAlarm();
            } else {
                shutdownAlarm();
            }
        }

        if (user_override) {
            if (user_input) {
                rotateSteps(stepper.user_input_angle);
                user_input = false;
            }
        } else {
            if (mpx4250.current_data < 30) {
                type = 3;
                stepper.current_angle = 0;
                stepper.current_angle_percentage = 0;
            } else if (mpx4250.current_data < 60) {
                type = 2;
                stepper.current_angle = 90;
                stepper.current_angle_percentage = 25;
            } else if (mpx4250.current_data < 90) {
                type = 4;
                stepper.current_angle = 180;
                stepper.current_angle_percentage = 50;
            } else if (mpx4250.current_data < 120) {
                type = 1;
                stepper.current_angle = 270;
                stepper.current_angle_percentage = 75;
            } else {
                type = 3;
                stepper.current_angle = 360;
                stepper.current_angle_percentage = 100;
            }
            if (stepper.previous_angle != stepper.current_angle) {
                rotateSteps(type);
            }
            stepper.previous_angle = stepper.current_angle;
        }

        if (show_main_menu || mpx4250.previous_data != mpx4250.current_data || stepper.previous_angle != stepper.current_angle) {
            mpx4250.previous_data = mpx4250.current_data;
            stepper.previous_angle = stepper.current_angle;



            lcd_draw_string(20, 130, "                                                 ", RED, BLACK);
            snprintf(string, sizeof (string), "Pressao: %.2f kPa", mpx4250.current_data);
            lcd_draw_string(20, 130, string, RED, BLACK);
            lcd_draw_string(20, 105, "                                                           ", RED, BLACK);
            snprintf(string, sizeof (string), "Valvula: %d graus ( %d%% )", stepper.current_angle, stepper.current_angle_percentage);
            lcd_draw_string(20, 105, string, RED, BLACK);
            mainMenu();
            show_error = false;
            show_main_menu = false;
        }

        if (EUSART1_is_rx_ready() && !set_threshold) {
            option = readDigitFromSerial();
        }

        if (bufferData) {
            switch (option) {
                default:
                    break;
                case '1':
                    user_override = !user_override;
                    user_input = true;
                    break;
                case '2':
                    if (!user_override) {
                        show_error = true;
                    } else {
                        valveMenu();

                        can_exit_loop = false;

                        do {
                            if (EUSART1_is_rx_ready()) {
                                option_2nd = readDigitFromSerial();
                            }

                            if (option_2nd >= '0' && option_2nd <= '5') {
                                user_input = true;
                                can_exit_loop = true;

                                switch (option_2nd) {
                                    case '0':
                                        user_override = !user_override;
                                        user_input = false;
                                        break;
                                    case '1':
                                        stepper.user_input_angle = 3;
                                        stepper.current_angle = 0;
                                        stepper.current_angle_percentage = 0;
                                        break;
                                    case '2':
                                        stepper.user_input_angle = 2;
                                        stepper.current_angle = 90;
                                        stepper.current_angle_percentage = 25;
                                        break;
                                    case '3':
                                        stepper.user_input_angle = 4;
                                        stepper.current_angle = 180;
                                        stepper.current_angle_percentage = 50;
                                        break;
                                    case '4':
                                        stepper.user_input_angle = 1;
                                        stepper.current_angle = 270;
                                        stepper.current_angle_percentage = 75;
                                        break;
                                    case '5':
                                        stepper.user_input_angle = 3;
                                        stepper.current_angle = 360;
                                        stepper.current_angle_percentage = 100;
                                        break;
                                }
                            }
                        } while (!can_exit_loop);
                    }
                    break;
                case '3':
                    EUSART1_Write(12);
                    printf("\r\nValor minimo atual: %d kPa\t Valor maximo atual: %d kPa\n", mpx4250.min_threshold, mpx4250.max_threshold);
                    printf("\r\nNovo valor minimo: ");
                    mpx4250.min_threshold = setPressureThreshold(mpx4250.min_threshold);
                    printf("\r\nNovo valor maximo: ");
                    mpx4250.max_threshold = setPressureThreshold(mpx4250.max_threshold);
                    break;
            }
            show_main_menu = true;
            bufferData = false;
            option = 0;
            option_2nd = 0;
        }
    }
}