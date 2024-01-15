/*
 * MINIPROJ: 9
 * TURMA: PL3
 * GRUPO: 11
 *
 * NOME: Diogo Cravo
 * NUMERO: 2222030
 *
 * NOME: Paulo Sousa
 * NUMERO: 2222031
 */

#include "mcc_generated_files/mcc.h"
#include "lib_ili9341.h"
#include "main.h"

#define BUZZER_ON 255
#define BUZZER_OFF 0
#define BUZZER_DURATION 100
#define TMR2_COUNTER 100
#define MIN_PRESSURE_THRESHOLD 10
#define MAX_PRESSURE_THRESHOLD 150
#define MAX_INPUT_LENGTH 4
#define MAX_TFT_LENGTH 50
#define MAX_ADC_VALUE 1023.0
#define VREF 5.0

bool buffer_data = false; // see if buffer available
bool can_exit_loop = false; // wait for user input for valve
bool user_input = false; // true: user controls valve. false: valve control is automatic
bool show_main_menu = true; // show main menu in terminal
bool show_error = false; // show errors in terminal
bool set_threshold = false; // can set the threshold
bool alarm_disabled = false; // disable the alarm
bool user_override = false; // user can change stepper opening manually if true

char string[MAX_TFT_LENGTH] = "";
int option = 0;
int option_2nd = 0;
int type = 0; // steps for stepper: 1 -> 270, 2 -> 90, 3 -> 0, 4 -> 180
int count = 0; // Stores timer 2 counter

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
    TMR0_StopTimer();
    TMR2_StopTimer();
    EPWM1_LoadDutyValue(BUZZER_OFF);
    LED_LAT = 0;
    lcd_fill_rect(20, 80, 200, 95, BLACK); // Clear alarm message
    count = TMR2_COUNTER; // Prepare the buzzer for startup once the alarm is triggered again
}

void triggerAlarm() {
    TMR0_StartTimer();
    TMR2_StartTimer();
    if (mpx4250.current_data <= mpx4250.min_threshold) {
        lcd_draw_string(20, 80, "ALERTA! Pressao baixa!", RED, BLACK);
    } else {
        lcd_draw_string(20, 80, "ALERTA! Pressao alta!", RED, BLACK);
    }
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
            char received_data = EUSART1_Read();

            if (isdigit(received_data) && i < MAX_INPUT_LENGTH - 1) {
                str[i++] = received_data;
                EUSART1_Write(received_data);
            } else if (received_data == 8 && i > 0) { // Backspace
                i--;
                EUSART1_Write(8);
                EUSART1_Write(' '); // Clear the character on terminal
                EUSART1_Write(8);
            } else if (received_data == 13) { // Enter
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
    char received_data = EUSART1_Read();
    if (isdigit(received_data)) {
        EUSART1_Write(received_data);
        buffer_data = true;
        return received_data;
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
    // lcd_draw_image(180, 0, 75, 92, paulo);
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

        if (show_main_menu || dataIsDifferent(mpx4250.previous_data, mpx4250.current_data) || dataIsDifferent(stepper.previous_angle, stepper.current_angle)) {
            mpx4250.previous_data = mpx4250.current_data;
            stepper.previous_angle = stepper.current_angle;
            lcd_fill_rect(85, 105, 225, 145, BLACK); // Clear old values
            snprintf(string, sizeof (string), "Pressao: %.2f kPa", mpx4250.current_data);
            lcd_draw_string(20, 130, string, RED, BLACK);
            snprintf(string, sizeof (string), "Valvula: %d graus ( %d%% )", stepper.current_angle, stepper.current_angle_percentage);
            lcd_draw_string(20, 105, string, RED, BLACK);
            mainMenu();
            show_error = false;
            show_main_menu = false;
        }

        if (EUSART1_is_rx_ready() && !set_threshold) {
            option = readDigitFromSerial();
        }

        if (buffer_data) {
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
                    mpx4250.min_threshold = setPressureThreshold(MIN_PRESSURE_THRESHOLD);
                    printf("\r\nNovo valor maximo: ");
                    mpx4250.max_threshold = setPressureThreshold(MAX_PRESSURE_THRESHOLD);
                    break;
            }
            show_main_menu = true;
            buffer_data = false;
            option = 0;
            option_2nd = 0;
        }
    }
}