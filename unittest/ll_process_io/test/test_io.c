/* code/test/test_rechner.c */
#include "unity.h"
#define IGNORE 0

#include "mock_modbus_registers.h"
uint16_t modbus_registers[IND_LAST_REG] = {0};

#include "mock_hardware.h"
#include "ll_process_io.h"

void setUp(void)
{
}

void tearDown()
{
}

void test_ioInit(){
    MCC_PIC_S_OUT1_SetLow_Expect();
    MCC_PIC_S_OUT2_SetLow_Expect();
    MCC_PIC_S_OUT3_SetLow_Expect();
    MCC_PIC_S_OUT4_SetLow_Expect();
    MCC_PIC_S_OUT5_SetLow_Expect();

    ioInit();
}

void test_ioProcess(){
    MCC_PIC_S_IN1_GetValue_ExpectAndReturn(IGNORE);
    MCC_PIC_S_IN2_GetValue_ExpectAndReturn(IGNORE);
    MCC_PIC_S_IN3_GetValue_ExpectAndReturn(IGNORE);
    MCC_PIC_S_IN4_GetValue_ExpectAndReturn(IGNORE);
    MCC_PIC_S_IN5_GetValue_ExpectAndReturn(IGNORE);

    MCC_PIC_S_OUT1_SetLow_Expect();
    MCC_PIC_S_OUT2_SetLow_Expect();
    MCC_PIC_S_OUT3_SetLow_Expect();
    MCC_PIC_S_OUT4_SetLow_Expect();
    MCC_PIC_S_OUT5_SetLow_Expect();

    ioProcess(true);
}