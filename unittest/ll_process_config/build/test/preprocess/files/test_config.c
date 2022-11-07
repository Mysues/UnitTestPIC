#include "../../header/ll_process_config.h"
#include "build/test/mocks/mock_hardware.h"
#include "build/test/mocks/mock_modbus_registers.h"
#include "C:/Ruby27-x64/lib/ruby/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






uint16_t modbus_registers[IND_LAST_REG] = {0};





void setUp(void)

{



}



void tearDown()

{

}



void test_Default_Init(void)

{

    MCC_ID3_GetValue_CMockExpectAndReturn(22, 0);

    MCC_ID2_GetValue_CMockExpectAndReturn(23, 0);

    MCC_ID1_GetValue_CMockExpectAndReturn(24, 0);

    MCC_ID0_GetValue_CMockExpectAndReturn(25, 0);



    MCC_DATAEE_ReadByte_CMockExpectAndReturn(27, 0, 0);

    MCC_DATAEE_ReadByte_CMockExpectAndReturn(28, 1, 0);



    MCC_DATAEE_WriteByte_CMockExpect(30, 0, 0);

    MCC_DATAEE_WriteByte_CMockExpect(31, 1, 1);



    Set_Baudrate_CMockExpect(33, 0x8A, 0x00);



    MCC_DATAEE_ReadByte_CMockExpectAndReturn(35, 2, 0);

    MCC_DATAEE_ReadByte_CMockExpectAndReturn(36, 3, 0);





    MCC_DATAEE_ReadByte_CMockExpectAndReturn(39, 4, 0);

    MCC_DATAEE_ReadByte_CMockExpectAndReturn(40, 5, 0);



    configInit();

}
