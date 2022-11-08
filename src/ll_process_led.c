/*******************************************************************************
 * This file provide the initialization and the process function for all RGB
 * LEDs.
 * - process mirror the value of the modbus register to all LEDs colour
 * - init function turn off all LEDs
 * - this process also require the interrupt enable and disable handler to be
 *   passed for the LED processes as it is timing critical
 ******************************************************************************/ 

#include "../header/ll_process_led.h"
#include "../header/modbus_registers.h"
#include "../header/hardware.h"
#include "stdbool.h"

/*******************************************************************************
 * private variable
 ******************************************************************************/
#ifndef TEST
#define LED1_COUNT 64
#define LED2_COUNT 64
#else
#define LED1_COUNT 3
#define LED2_COUNT 3
#endif

const uint8_t bit_mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

/*******************************************************************************
 * ledInterruptHandler
 * - this function will set the interrupt enable and disable handler
 * - interrupt will be enable and disable accordingly during the led write
 *   process
 ******************************************************************************/

void (*interruptEnable)(void);
void (*interruptDisable)(void);

void ledInterruptHandler(
        void (* interruptDisable_)(void),
        void (* interruptEnable_)(void))
{
    interruptEnable = interruptEnable_;
    interruptDisable = interruptDisable_;
}


/*******************************************************************************
 * ledInit
 * - this function initialize LEDs by turning off to all the LEDs
 * - ledInterruptHandler should be call prior to ledInit as initialization 
 *   require the control of interrupts
 ******************************************************************************/

void ledInit(void)
{
    uC_delay_ms(10);
    led1Reset();
    led2Reset();
    interruptDisable();
    for (uint8_t i = 0; i < (LED1_COUNT * 3); i += 1)
    {
        led1WriteByte(0x00);
    }
    for (uint8_t i = 0; i < (LED2_COUNT * 3); i += 1)
    {
        led2WriteByte(0x00);
    }
    interruptEnable();
}


/*******************************************************************************
 * ledProcess
 * - generally this function will check for the changes in the modbus register
 *   and upon changes detected, it will write the updated value to the RGB LEDs
 * - processes are seperated into 2 section and will be run sequentially to 
 *   avoid taking too long time for this process in 1 iteration
 ******************************************************************************/

void ledProcess(void)
{
    static int process = 0;
    switch (process)
    {
        case 0:
            led1Process();
            process += 1;
            break;
        case 1:
            led2Process();
            process += 1;
            break;
        default:
            process = 0;
            break;
    }
}

void led1Process(void)
{
    bool changed = false;
    static uint16_t led1_raw[LED1_COUNT] = { 0 };
    
    //check for changes
    for (uint8_t i = 0; i < LED1_COUNT; i += 1)
    {
        if (led1_raw[i] != modbus_registers[IND_LED1 + i])
        {
            changed = true;
            led1_raw[i] = modbus_registers[IND_LED1 + i];
        }
    }
    
    //exit if no changes
    if (changed == false) return;
    
    //populate data from raw to 3byte RGB
    uint8_t led_data[(LED1_COUNT * 3)] = { 0 };
    for (uint8_t i = 0; i < LED1_COUNT; i += 1)
    {
        led_data[i * 3 + 0] = 
                (uint8_t)((led1_raw[i] >> 3) & (0x3F << 2));
        led_data[i * 3 + 1] = 
                (uint8_t)((led1_raw[i] >> 8) & (0x1F << 3));
        led_data[i * 3 + 2] = 
                (uint8_t)((led1_raw[i] << 3) & (0x1F << 3));
    }
    
    //write data to led
    interruptDisable();
    for (uint8_t i = 0; i < (LED1_COUNT * 3); i += 1)
    {
        led1WriteByte(led_data[i]);
    }
    interruptEnable();
}

void led2Process(void)
{
    bool changed = false;
    static uint16_t led2_raw[LED2_COUNT] = { 0 };
    
    //check for changes
    for (uint8_t i = 0; i < LED2_COUNT; i += 1)
    {
        if (led2_raw[i] != modbus_registers[IND_LED2 + i])
        {
            changed = true;
            led2_raw[i] = modbus_registers[IND_LED2 + i];
        }
    }
    
    //exit if no changes
    if (changed == false) return;
    
    //populate data from raw to 3byte RGB
    uint8_t led_data[(LED2_COUNT * 3)] = { 0 };
    for (uint8_t i = 0; i < LED2_COUNT; i += 1)
    {
        led_data[i * 3 + 0] = 
                (uint8_t)((led2_raw[i] >> 3) & (0x3F << 2));
        led_data[i * 3 + 1] = 
                (uint8_t)((led2_raw[i] >> 8) & (0x1F << 3));
        led_data[i * 3 + 2] = 
                (uint8_t)((led2_raw[i] << 3) & (0x1F << 3));
    }
    
    //write data to led
    interruptDisable();
    for (uint8_t i = 0; i < (LED2_COUNT * 3); i += 1)
    {
        led2WriteByte(led_data[i]);
    }
    interruptEnable();
}


/*******************************************************************************
 * led helper functions
 * - additional functions to help with the led processes, to clear the LEDs,
 *   to write datas to the LEDs and etc
 ******************************************************************************/

void led1Reset(void)
{
    MCC_PIC_RGB_CONTROL_SetLow();
    uC_delay_us(10);
}

void led1WriteByte(uint8_t data)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i += 1)
    {
        if ((data & bit_mask[i]) == 0)
        {
            //INTERRUPT_GlobalInterruptDisable();
            MCC_PIC_RGB_CONTROL_SetHigh();
#ifndef TEST
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();  //5
#endif
            MCC_PIC_RGB_CONTROL_SetLow();
            //INTERRUPT_GlobalInterruptEnable();

        }
        else
        {
            //INTERRUPT_GlobalInterruptDisable();
            MCC_PIC_RGB_CONTROL_SetHigh();
#ifndef TEST
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();  //5
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();  //15
#endif
            MCC_PIC_RGB_CONTROL_SetLow();
            //INTERRUPT_GlobalInterruptEnable();
        }
    }
}

void led2Reset(void)
{
    MCC_PIC_RGB_CONTROL2_SetLow();
    uC_delay_us(100);
}

void led2WriteByte(uint8_t data)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i += 1)
    {
        if ((data & bit_mask[i]) == 0)
        {
            //INTERRUPT_GlobalInterruptDisable();
            MCC_PIC_RGB_CONTROL2_SetHigh();
#ifndef TEST
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();  //5
#endif
            MCC_PIC_RGB_CONTROL2_SetLow();
            //INTERRUPT_GlobalInterruptEnable();
        }
        else
        {
            //INTERRUPT_GlobalInterruptDisable();
            MCC_PIC_RGB_CONTROL2_SetHigh();
#ifndef TEST
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();  //5
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();  //15
#endif
            MCC_PIC_RGB_CONTROL2_SetLow();
            //INTERRUPT_GlobalInterruptEnable();
        }
    }
}

