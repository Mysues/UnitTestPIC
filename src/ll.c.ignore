/*******************************************************************************
 * This file handle the redirect of interrupt handler, initialization and the 
 * processes of ll
 ******************************************************************************/ 

#include "ll.h"
#include "modbus_registers.h"
#include "modbus_rtu/modbus_rtu.h"
#include "mcc_generated_files/mcc.h"
#include "ll_process_config.h"
#include "ll_process_io.h"
#include "ll_process_led.h"
#include "stdbool.h"
#include "stdint.h"

/*******************************************************************************
 * private variable
 ******************************************************************************/

uint16_t millis = 0;  //millis will be +1 every 1ms
#define HEARTBEAT_TIMEOUT 500
bool heartbeat_triggered = true;

/*******************************************************************************
 * llInit
 * - this function will be call at the beginning of uC process
 * - all initialization for processes should be included here
 * - all interrupt handler should configured here
 ******************************************************************************/

void llInit(void)
{
    //timer interrupt handler
    TMR0_SetInterruptHandler(modbusProcessHandler);
    TMR1_SetInterruptHandler(modbusTimeoutHandler);
    TMR2_SetInterruptHandler(millisHandler);
    EUSART1_SetRxInterruptHandler(uartReceiveHandler);
    
    //modbus init
    modbusRegistersInit();
    //initialize tx and rx handler
    MODBUS_RTU_UartHandler(EUSART1_is_rx_ready, EUSART1_Read, EUSART1_Write);
    //initialize interrupt enable and disable handler
    MODBUS_RTU_InterruptHandler(interruptDisableAll, interruptEnableAll);
    //initialize modbus_registers
    MODBUS_RTU_Init(modbus_registers, IND_REG_RW_START,
        IND_REG_RW_END, IND_LAST_REG);
    
    //config init
    configInit();

    //io init
    ioInit();

    //led init
    ledInterruptHandler(interruptDisableAll, interruptEnableAll);
    ledInit();
}


/*******************************************************************************
 * llProcess
 * - this process will be called in the main loop under main.c
 * - all processes should be placed here
 * - processes should not has blocking element
 ******************************************************************************/

void llProcess(void)
{
    //processes to run regardless device active state
    comLedProcess();

    //exit process if id is set to 0
    if (modbus_registers[IND_MODBUS_ID] == 0) return;

    //processes to run only if device is active
    configProcess();
    ioProcess(heartbeat_triggered);
    ledProcess();
}


/*******************************************************************************
 * interrupt handlers
 * - this process will be called in the main loop under main.c
 * - all processes should be placed here
 * - processes should not has blocking element
 ******************************************************************************/

void modbusProcessHandler(void)
{
    //stop timer
    TMR0_StopTimer();
    
    //process modbus
    MODBUS_RTU_ProcessFrame();
}

void modbusTimeoutHandler(void)
{
    //stop timer after timeout happened
    TMR1_StopTimer();
    
    //modbus timeout triggered
    MODBUS_RTU_Timeout();
}

void millisHandler(void)
{
    //increment millis variable
    millis += 1;
}

void uartReceiveHandler(void)
{
    //stop timeout timer
    TMR1_StopTimer();
    
    //call default RX handler
    EUSART1_Receive_ISR();
 
    //start timeout timer
    TMR1_Reload();
    TMR1_StartTimer();
    
    //disable service routine if modbus id is zero (device disabled)
    if (modbus_registers[IND_MODBUS_ID] == 0) return;

    //start process timer
    TMR0_Reload();
    TMR0_StartTimer();
}


/*******************************************************************************
 * interrupt enable and disable
 * - these functions enable & disable interrupt
 * - required as there is high and low interrupt
 * - needed a function to enable/disable all in one function
 ******************************************************************************/

void interruptEnableAll(void)
{
    INTERRUPT_GlobalInterruptHighEnable();
    //INTERRUPT_GlobalInterruptLowEnable();
}

void interruptDisableAll(void)
{
    INTERRUPT_GlobalInterruptHighDisable();
    //INTERRUPT_GlobalInterruptLowDisable();    
}

/*******************************************************************************
 * comProcess
 * - control the co
 * - required as there is high and low interrupt
 * - needed a function to enable/disable all in one function
 ******************************************************************************/

void comLedProcess(void)
{
    /* LED State
     * Disable state - Status ON, COM OFF
     * Enabled Connected state - Status ON, COM blink fast (10Hz)
     * Enabled Disconnected state - Status OFF, COM blink slow (1Hz)
     */

    //check state
    uint8_t state = 0;
    static uint16_t millis_mem = 0;

    //device disabled
    if (modbus_registers[IND_MODBUS_ID] == 0)
    {
        state = 0;
        heartbeat_triggered = true;
    }
    //device enabled
    else
    {
        //heartbeat timeout happened
        if (modbus_registers[IND_HEARTBEAT] > HEARTBEAT_TIMEOUT)
        {
            state = 1;
            heartbeat_triggered = true;
        }
        //system normal
        else
        {
            state = 2;
            modbus_registers[IND_HEARTBEAT] += (millis - millis_mem);
            millis_mem = millis;
            heartbeat_triggered = false;
        }
    }

    //blinking
    static uint16_t millis_com = 0;
    const uint16_t blink_period_slow = 500;
    const uint16_t blink_period_fast = 50;

    //device disabled
    if (state == 0)
    {
        //Status LED ON
        LED_STATUS_SetHigh();
        //COM LED OFF
        LED_COM_SetLow();
    }
    //device enabled, but heartbeat timeout
    else if (state == 1)
    {
        //Status LED ON
        LED_STATUS_SetHigh();
        //COM LED blink at 1Hz
        if ((millis - millis_com) > blink_period_slow)
        {
            millis_com += blink_period_slow;
            LED_COM_Toggle();
        }
    }
    //device enabled, communication normal
    else
    {
        //Status LED ON
        LED_STATUS_SetHigh();
        //COM LED blink at 1Hz
        if ((millis - millis_com) > blink_period_fast)
        {
            millis_com += blink_period_fast;
            LED_COM_Toggle();
        }
    }
}

