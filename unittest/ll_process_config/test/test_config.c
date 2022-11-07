/* code/test/test_rechner.c */
#include "unity.h"
#define IGNORE 0

#include "mock_modbus_registers.h"
uint16_t modbus_registers[IND_LAST_REG] = {0};

#include "mock_hardware.h"
#include "ll_process_config.h"

void setUp(void)
{

}

void tearDown()
{
}

void test_Default_Init(void)
{
    MCC_ID3_GetValue_ExpectAndReturn(IGNORE);
    MCC_ID2_GetValue_ExpectAndReturn(IGNORE);
    MCC_ID1_GetValue_ExpectAndReturn(IGNORE);
    MCC_ID0_GetValue_ExpectAndReturn(IGNORE); 

    MCC_DATAEE_ReadByte_ExpectAndReturn(0,IGNORE);
    MCC_DATAEE_ReadByte_ExpectAndReturn(1,IGNORE);

    MCC_DATAEE_WriteByte_Expect(0,0);
    MCC_DATAEE_WriteByte_Expect(1,1);

    Set_Baudrate_Expect(0x8A,0x00);

    MCC_DATAEE_ReadByte_ExpectAndReturn(2,IGNORE);
    MCC_DATAEE_ReadByte_ExpectAndReturn(3,IGNORE);
    

    MCC_DATAEE_ReadByte_ExpectAndReturn(4,IGNORE);
    MCC_DATAEE_ReadByte_ExpectAndReturn(5,IGNORE);

    configInit();
}