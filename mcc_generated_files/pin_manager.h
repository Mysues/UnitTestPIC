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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

// get/set PIC_S_IN1 aliases
#define PIC_S_IN1_TRIS                 TRISAbits.TRISA0
#define PIC_S_IN1_LAT                  LATAbits.LATA0
#define PIC_S_IN1_PORT                 PORTAbits.RA0
#define PIC_S_IN1_ANS                  ANSELAbits.ANSA0
#define PIC_S_IN1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define PIC_S_IN1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define PIC_S_IN1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define PIC_S_IN1_GetValue()           PORTAbits.RA0
#define PIC_S_IN1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define PIC_S_IN1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define PIC_S_IN1_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define PIC_S_IN1_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set PIC_S_IN2 aliases
#define PIC_S_IN2_TRIS                 TRISAbits.TRISA1
#define PIC_S_IN2_LAT                  LATAbits.LATA1
#define PIC_S_IN2_PORT                 PORTAbits.RA1
#define PIC_S_IN2_ANS                  ANSELAbits.ANSA1
#define PIC_S_IN2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PIC_S_IN2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PIC_S_IN2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PIC_S_IN2_GetValue()           PORTAbits.RA1
#define PIC_S_IN2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PIC_S_IN2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PIC_S_IN2_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define PIC_S_IN2_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set PIC_S_IN3 aliases
#define PIC_S_IN3_TRIS                 TRISAbits.TRISA2
#define PIC_S_IN3_LAT                  LATAbits.LATA2
#define PIC_S_IN3_PORT                 PORTAbits.RA2
#define PIC_S_IN3_ANS                  ANSELAbits.ANSA2
#define PIC_S_IN3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define PIC_S_IN3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define PIC_S_IN3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define PIC_S_IN3_GetValue()           PORTAbits.RA2
#define PIC_S_IN3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define PIC_S_IN3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define PIC_S_IN3_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define PIC_S_IN3_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set PIC_S_IN4 aliases
#define PIC_S_IN4_TRIS                 TRISAbits.TRISA3
#define PIC_S_IN4_LAT                  LATAbits.LATA3
#define PIC_S_IN4_PORT                 PORTAbits.RA3
#define PIC_S_IN4_ANS                  ANSELAbits.ANSA3
#define PIC_S_IN4_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define PIC_S_IN4_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define PIC_S_IN4_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define PIC_S_IN4_GetValue()           PORTAbits.RA3
#define PIC_S_IN4_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define PIC_S_IN4_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define PIC_S_IN4_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define PIC_S_IN4_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set PIC_S_IN5 aliases
#define PIC_S_IN5_TRIS                 TRISAbits.TRISA4
#define PIC_S_IN5_LAT                  LATAbits.LATA4
#define PIC_S_IN5_PORT                 PORTAbits.RA4
#define PIC_S_IN5_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define PIC_S_IN5_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define PIC_S_IN5_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define PIC_S_IN5_GetValue()           PORTAbits.RA4
#define PIC_S_IN5_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define PIC_S_IN5_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set ID3 aliases
#define ID3_TRIS                 TRISAbits.TRISA5
#define ID3_LAT                  LATAbits.LATA5
#define ID3_PORT                 PORTAbits.RA5
#define ID3_ANS                  ANSELAbits.ANSA5
#define ID3_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define ID3_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define ID3_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define ID3_GetValue()           PORTAbits.RA5
#define ID3_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define ID3_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define ID3_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define ID3_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set PIC_S_OUT1 aliases
#define PIC_S_OUT1_TRIS                 TRISBbits.TRISB0
#define PIC_S_OUT1_LAT                  LATBbits.LATB0
#define PIC_S_OUT1_PORT                 PORTBbits.RB0
#define PIC_S_OUT1_WPU                  WPUBbits.WPUB0
#define PIC_S_OUT1_ANS                  ANSELBbits.ANSB0
#define PIC_S_OUT1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define PIC_S_OUT1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define PIC_S_OUT1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define PIC_S_OUT1_GetValue()           PORTBbits.RB0
#define PIC_S_OUT1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define PIC_S_OUT1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define PIC_S_OUT1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define PIC_S_OUT1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define PIC_S_OUT1_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define PIC_S_OUT1_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set PIC_S_OUT2 aliases
#define PIC_S_OUT2_TRIS                 TRISBbits.TRISB1
#define PIC_S_OUT2_LAT                  LATBbits.LATB1
#define PIC_S_OUT2_PORT                 PORTBbits.RB1
#define PIC_S_OUT2_WPU                  WPUBbits.WPUB1
#define PIC_S_OUT2_ANS                  ANSELBbits.ANSB1
#define PIC_S_OUT2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define PIC_S_OUT2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define PIC_S_OUT2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define PIC_S_OUT2_GetValue()           PORTBbits.RB1
#define PIC_S_OUT2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define PIC_S_OUT2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define PIC_S_OUT2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define PIC_S_OUT2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define PIC_S_OUT2_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define PIC_S_OUT2_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set PIC_S_OUT3 aliases
#define PIC_S_OUT3_TRIS                 TRISBbits.TRISB2
#define PIC_S_OUT3_LAT                  LATBbits.LATB2
#define PIC_S_OUT3_PORT                 PORTBbits.RB2
#define PIC_S_OUT3_WPU                  WPUBbits.WPUB2
#define PIC_S_OUT3_ANS                  ANSELBbits.ANSB2
#define PIC_S_OUT3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define PIC_S_OUT3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define PIC_S_OUT3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define PIC_S_OUT3_GetValue()           PORTBbits.RB2
#define PIC_S_OUT3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define PIC_S_OUT3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define PIC_S_OUT3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define PIC_S_OUT3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define PIC_S_OUT3_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define PIC_S_OUT3_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set PIC_S_OUT4 aliases
#define PIC_S_OUT4_TRIS                 TRISBbits.TRISB3
#define PIC_S_OUT4_LAT                  LATBbits.LATB3
#define PIC_S_OUT4_PORT                 PORTBbits.RB3
#define PIC_S_OUT4_WPU                  WPUBbits.WPUB3
#define PIC_S_OUT4_ANS                  ANSELBbits.ANSB3
#define PIC_S_OUT4_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define PIC_S_OUT4_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define PIC_S_OUT4_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define PIC_S_OUT4_GetValue()           PORTBbits.RB3
#define PIC_S_OUT4_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define PIC_S_OUT4_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define PIC_S_OUT4_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define PIC_S_OUT4_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define PIC_S_OUT4_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define PIC_S_OUT4_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set PIC_S_OUT5 aliases
#define PIC_S_OUT5_TRIS                 TRISBbits.TRISB4
#define PIC_S_OUT5_LAT                  LATBbits.LATB4
#define PIC_S_OUT5_PORT                 PORTBbits.RB4
#define PIC_S_OUT5_WPU                  WPUBbits.WPUB4
#define PIC_S_OUT5_ANS                  ANSELBbits.ANSB4
#define PIC_S_OUT5_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define PIC_S_OUT5_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define PIC_S_OUT5_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define PIC_S_OUT5_GetValue()           PORTBbits.RB4
#define PIC_S_OUT5_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define PIC_S_OUT5_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define PIC_S_OUT5_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define PIC_S_OUT5_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define PIC_S_OUT5_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define PIC_S_OUT5_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set LED_COM aliases
#define LED_COM_TRIS                 TRISCbits.TRISC1
#define LED_COM_LAT                  LATCbits.LATC1
#define LED_COM_PORT                 PORTCbits.RC1
#define LED_COM_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED_COM_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED_COM_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED_COM_GetValue()           PORTCbits.RC1
#define LED_COM_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED_COM_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set LED_STATUS aliases
#define LED_STATUS_TRIS                 TRISCbits.TRISC2
#define LED_STATUS_LAT                  LATCbits.LATC2
#define LED_STATUS_PORT                 PORTCbits.RC2
#define LED_STATUS_ANS                  ANSELCbits.ANSC2
#define LED_STATUS_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LED_STATUS_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LED_STATUS_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LED_STATUS_GetValue()           PORTCbits.RC2
#define LED_STATUS_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LED_STATUS_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LED_STATUS_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define LED_STATUS_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set TXEN aliases
#define TXEN_TRIS                 TRISCbits.TRISC5
#define TXEN_LAT                  LATCbits.LATC5
#define TXEN_PORT                 PORTCbits.RC5
#define TXEN_ANS                  ANSELCbits.ANSC5
#define TXEN_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define TXEN_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define TXEN_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define TXEN_GetValue()           PORTCbits.RC5
#define TXEN_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define TXEN_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define TXEN_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define TXEN_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

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

// get/set PIC_RGB_CONTROL aliases
#define PIC_RGB_CONTROL_TRIS                 TRISDbits.TRISD6
#define PIC_RGB_CONTROL_LAT                  LATDbits.LATD6
#define PIC_RGB_CONTROL_PORT                 PORTDbits.RD6
#define PIC_RGB_CONTROL_ANS                  ANSELDbits.ANSD6
#define PIC_RGB_CONTROL_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define PIC_RGB_CONTROL_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define PIC_RGB_CONTROL_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define PIC_RGB_CONTROL_GetValue()           PORTDbits.RD6
#define PIC_RGB_CONTROL_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define PIC_RGB_CONTROL_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define PIC_RGB_CONTROL_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define PIC_RGB_CONTROL_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set PIC_RGB_CONTROL2 aliases
#define PIC_RGB_CONTROL2_TRIS                 TRISDbits.TRISD7
#define PIC_RGB_CONTROL2_LAT                  LATDbits.LATD7
#define PIC_RGB_CONTROL2_PORT                 PORTDbits.RD7
#define PIC_RGB_CONTROL2_ANS                  ANSELDbits.ANSD7
#define PIC_RGB_CONTROL2_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define PIC_RGB_CONTROL2_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define PIC_RGB_CONTROL2_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define PIC_RGB_CONTROL2_GetValue()           PORTDbits.RD7
#define PIC_RGB_CONTROL2_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define PIC_RGB_CONTROL2_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define PIC_RGB_CONTROL2_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define PIC_RGB_CONTROL2_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

// get/set ID0 aliases
#define ID0_TRIS                 TRISEbits.TRISE0
#define ID0_LAT                  LATEbits.LATE0
#define ID0_PORT                 PORTEbits.RE0
#define ID0_ANS                  ANSELEbits.ANSE0
#define ID0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define ID0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define ID0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define ID0_GetValue()           PORTEbits.RE0
#define ID0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define ID0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define ID0_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define ID0_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set ID1 aliases
#define ID1_TRIS                 TRISEbits.TRISE1
#define ID1_LAT                  LATEbits.LATE1
#define ID1_PORT                 PORTEbits.RE1
#define ID1_ANS                  ANSELEbits.ANSE1
#define ID1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define ID1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define ID1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define ID1_GetValue()           PORTEbits.RE1
#define ID1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define ID1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define ID1_SetAnalogMode()      do { ANSELEbits.ANSE1 = 1; } while(0)
#define ID1_SetDigitalMode()     do { ANSELEbits.ANSE1 = 0; } while(0)

// get/set ID2 aliases
#define ID2_TRIS                 TRISEbits.TRISE2
#define ID2_LAT                  LATEbits.LATE2
#define ID2_PORT                 PORTEbits.RE2
#define ID2_ANS                  ANSELEbits.ANSE2
#define ID2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define ID2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define ID2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define ID2_GetValue()           PORTEbits.RE2
#define ID2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define ID2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define ID2_SetAnalogMode()      do { ANSELEbits.ANSE2 = 1; } while(0)
#define ID2_SetDigitalMode()     do { ANSELEbits.ANSE2 = 0; } while(0)

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