/* code/test/test_rechner.c */
#include "unity.h"
#define IGNORE 0

// #include "mock_pic18f46k22.h"
#include "mock_xc.h"
#include "mock_pic18.h"
#include "mock_pin_manager.h"
#include "mock_modbus_registers.h"
uint16_t modbus_registers[IND_LAST_REG] = {0};

#include "mock_hardware.h"
#include "ll_process_led.h"

void setUp(void)
{
}

void tearDown()
{
}

void test_ledInit(){
    // ledInit();
}