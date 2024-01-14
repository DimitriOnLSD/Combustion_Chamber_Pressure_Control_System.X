/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC18F46K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set MPX4250_AN aliases
#define MPX4250_AN_TRIS                 TRISAbits.TRISA0
#define MPX4250_AN_LAT                  LATAbits.LATA0
#define MPX4250_AN_PORT                 PORTAbits.RA0
#define MPX4250_AN_ANS                  ANSELAbits.ANSA0
#define MPX4250_AN_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define MPX4250_AN_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define MPX4250_AN_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define MPX4250_AN_GetValue()           PORTAbits.RA0
#define MPX4250_AN_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define MPX4250_AN_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define MPX4250_AN_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define MPX4250_AN_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISAbits.TRISA5
#define LED_LAT                  LATAbits.LATA5
#define LED_PORT                 PORTAbits.RA5
#define LED_ANS                  ANSELAbits.ANSA5
#define LED_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_GetValue()           PORTAbits.RA5
#define LED_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set disableAlarm aliases
#define disableAlarm_TRIS                 TRISBbits.TRISB0
#define disableAlarm_LAT                  LATBbits.LATB0
#define disableAlarm_PORT                 PORTBbits.RB0
#define disableAlarm_WPU                  WPUBbits.WPUB0
#define disableAlarm_ANS                  ANSELBbits.ANSB0
#define disableAlarm_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define disableAlarm_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define disableAlarm_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define disableAlarm_GetValue()           PORTBbits.RB0
#define disableAlarm_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define disableAlarm_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define disableAlarm_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define disableAlarm_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define disableAlarm_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define disableAlarm_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set IN1 aliases
#define IN1_TRIS                 TRISBbits.TRISB4
#define IN1_LAT                  LATBbits.LATB4
#define IN1_PORT                 PORTBbits.RB4
#define IN1_WPU                  WPUBbits.WPUB4
#define IN1_ANS                  ANSELBbits.ANSB4
#define IN1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IN1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IN1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IN1_GetValue()           PORTBbits.RB4
#define IN1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IN1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IN1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IN1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IN1_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IN1_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IN2 aliases
#define IN2_TRIS                 TRISBbits.TRISB5
#define IN2_LAT                  LATBbits.LATB5
#define IN2_PORT                 PORTBbits.RB5
#define IN2_WPU                  WPUBbits.WPUB5
#define IN2_ANS                  ANSELBbits.ANSB5
#define IN2_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IN2_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IN2_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IN2_GetValue()           PORTBbits.RB5
#define IN2_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IN2_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IN2_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IN2_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IN2_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define IN2_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set IN3 aliases
#define IN3_TRIS                 TRISBbits.TRISB6
#define IN3_LAT                  LATBbits.LATB6
#define IN3_PORT                 PORTBbits.RB6
#define IN3_WPU                  WPUBbits.WPUB6
#define IN3_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IN3_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IN3_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IN3_GetValue()           PORTBbits.RB6
#define IN3_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IN3_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IN3_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IN3_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set IN4 aliases
#define IN4_TRIS                 TRISBbits.TRISB7
#define IN4_LAT                  LATBbits.LATB7
#define IN4_PORT                 PORTBbits.RB7
#define IN4_WPU                  WPUBbits.WPUB7
#define IN4_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define IN4_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define IN4_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define IN4_GetValue()           PORTBbits.RB7
#define IN4_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define IN4_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define IN4_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define IN4_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set RD1 procedures
#define RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RD1_GetValue()              PORTDbits.RD1
#define RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RD1_SetAnalogMode()         do { ANSELDbits.ANSD1 = 1; } while(0)
#define RD1_SetDigitalMode()        do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set RD4 procedures
#define RD4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define RD4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define RD4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define RD4_GetValue()              PORTDbits.RD4
#define RD4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define RD4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define RD4_SetAnalogMode()         do { ANSELDbits.ANSD4 = 1; } while(0)
#define RD4_SetDigitalMode()        do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set DC aliases
#define DC_TRIS                 TRISEbits.TRISE0
#define DC_LAT                  LATEbits.LATE0
#define DC_PORT                 PORTEbits.RE0
#define DC_ANS                  ANSELEbits.ANSE0
#define DC_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define DC_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define DC_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define DC_GetValue()           PORTEbits.RE0
#define DC_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define DC_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define DC_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define DC_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set CS aliases
#define CS_TRIS                 TRISEbits.TRISE1
#define CS_LAT                  LATEbits.LATE1
#define CS_PORT                 PORTEbits.RE1
#define CS_ANS                  ANSELEbits.ANSE1
#define CS_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define CS_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define CS_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define CS_GetValue()           PORTEbits.RE1
#define CS_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define CS_SetAnalogMode()      do { ANSELEbits.ANSE1 = 1; } while(0)
#define CS_SetDigitalMode()     do { ANSELEbits.ANSE1 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/