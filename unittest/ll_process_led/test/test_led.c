/* code/test/test_rechner.c */
#include "unity.h"
#define IGNORE 0

#include "mock_modbus_registers.h"
uint16_t modbus_registers[IND_LAST_REG] = {0};

#include "mock_hardware.h"
#include "ll_process_led.h"

static int counterEnableInterrupt;
static int counterDisableIntertupt;

void setUp(void)
{
}

void tearDown()
{
}

void intteruptEnableMockup()
{
    printf("Enable Interrupt : %d\n", counterEnableInterrupt);
    counterEnableInterrupt++;
}

void intteruptDisableMockup()
{
    printf("Disable Interrupt : %d\n", counterDisableIntertupt);
    counterDisableIntertupt++;
}

void haha()
{
    MCC_PIC_RGB_CONTROL_SetHigh_Expect();
    MCC_PIC_RGB_CONTROL_SetLow_Expect();
}

void test_ledInit()
{
    counterEnableInterrupt = 1;
    counterDisableIntertupt = 1;

    ledInterruptHandler(intteruptDisableMockup, intteruptEnableMockup);
    uC_delay_ms_Expect(10);

    MCC_PIC_RGB_CONTROL_SetLow_Expect();
    uC_delay_us_Expect(10);

    MCC_PIC_RGB_CONTROL2_SetLow_Expect();
    uC_delay_us_Expect(100);

    for (size_t i = 0; i < 3 * 3 * 8; i++) // 3*3*8
    {
        MCC_PIC_RGB_CONTROL_SetHigh_Expect();
        MCC_PIC_RGB_CONTROL_SetLow_Expect();
    }

    for (size_t i = 0; i < 3 * 3 * 8; i++) // 3*3*8
    {
        MCC_PIC_RGB_CONTROL2_SetHigh_Expect();
        MCC_PIC_RGB_CONTROL2_SetLow_Expect();
    }

    ledInit();
}

void test_ledProcess(){
    counterEnableInterrupt = 1;
    counterDisableIntertupt = 1;

    modbus_registers[IND_LED1] = 1;
    modbus_registers[IND_LED1+1] = 1;

    modbus_registers[IND_LED2] = 1;
    modbus_registers[IND_LED2+1] = 1;

    ledInterruptHandler(intteruptDisableMockup, intteruptEnableMockup);

    for (size_t i = 0; i < 3 * 3 * 8; i++)
    {
        MCC_PIC_RGB_CONTROL_SetHigh_Expect();
        MCC_PIC_RGB_CONTROL_SetLow_Expect();
    }

    for (size_t i = 0; i < 3 * 3 * 8; i++)
    {
        MCC_PIC_RGB_CONTROL2_SetHigh_Expect();
        MCC_PIC_RGB_CONTROL2_SetLow_Expect();
    }

    ledProcess();
    ledProcess();
}