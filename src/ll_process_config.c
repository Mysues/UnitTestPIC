
/*******************************************************************************
 * This file provide the initialization and the process function for all config.
 * - process check for changes in the config, upon changes detected, it update
 *   the value to flash memory
 * - init function read all flash memory and place them onto the correct modbus
 *   register
 ******************************************************************************/ 

#include "../header/ll_process_config.h"
#include "stdbool.h"
#include "../header/modbus_registers.h"
#include "../header/hardware.h"


/*******************************************************************************
 * configInit
 * - read all flash memory and write them onto corresponding modbus_registers
 ******************************************************************************/

void configInit(void)
{
    //read id from dip switch
    uint8_t address = (uint8_t)(!(MCC_ID3_GetValue() & 0x01) << 3);
    address += (uint8_t)(!(MCC_ID2_GetValue() & 0x01) << 2);
    address += (uint8_t)(!(MCC_ID1_GetValue() & 0x01) << 1);
    address += (uint8_t)(!(MCC_ID0_GetValue() & 0x01) << 0);
    modbus_registers[IND_MODBUS_ID] = address;
    
    //read baudrate from eeprom
    uint16_t baudrate = configReadEeprom16(0);
    //check if baudrate is valid
    if ((baudrate != 1) &&
            (baudrate != 2) &&
            (baudrate != 3) &&
            (baudrate != 4))
    {
        baudrate = 1;
        configWriteEeprom16(0, baudrate);
    }
    modbus_registers[IND_BAUDRATE] = baudrate;
    
    //configure baudrate to hardware according to configuration (only run on init)
    switch (baudrate)
    {
        case 1:  //115.2 kbps
            Set_Baudrate(0x8A,0x00);
            break;
        case 2:  //250 kbps
            Set_Baudrate(63,0x00);
            break;
        case 3:  //500 kbps
            Set_Baudrate(31,0x00);
            break;
        case 4:  //1 mbps
            Set_Baudrate(15,0x00);
            break;
    }   

    //read safety input config
    uint16_t config_safety_input = configReadEeprom16(1);
    //check if config_safety_input is valid
    if (config_safety_input > 0b11111)
    {
        config_safety_input = 0b00000;
        configWriteEeprom16(1, config_safety_input);
    }
    modbus_registers[IND_CONFIG_SAFETY_INPUT] = config_safety_input;

    //read safety output config
    uint16_t config_safety_output = configReadEeprom16(2);
    //check if config_safety_output is valid
    if (config_safety_output > 0b11111)
    {
        config_safety_output = 0b00000;
        configWriteEeprom16(2, config_safety_output);
    }
    modbus_registers[IND_CONFIG_SAFETY_OUTPUT] = config_safety_output;
    
    //call config process for the first time
    // configProcess();
}


/*******************************************************************************
 * configProcess
 * - check for changes on the modbus_registers for config, if changes is 
 *   detected, it will write the changes to flash memory.
 * - also change the baudrate for com port immediately after baudrate changes
 *   detected.
 ******************************************************************************/

void configProcess(void)
{
    static bool init_process = false; //flag to detect the first run
    static uint16_t baudrate = 0;
    static uint16_t config_safety_input = 0;
    static uint16_t config_safety_output = 0;
    
    if (init_process == false)
    {
        //this should only run after configInit has run
        //save all register value to memory
        baudrate = modbus_registers[IND_BAUDRATE];
        config_safety_input = modbus_registers[IND_CONFIG_SAFETY_INPUT];
        config_safety_output = modbus_registers[IND_CONFIG_SAFETY_OUTPUT];
        init_process = true;
        return;
    }
    
    //detect changes
    if (baudrate != modbus_registers[IND_BAUDRATE])
    {
        //save changes
        baudrate = modbus_registers[IND_BAUDRATE];
        //write value to eeprom
        configWriteEeprom16(0, baudrate);
    }
    if (config_safety_input != modbus_registers[IND_CONFIG_SAFETY_INPUT])
    {
        //save changes
        config_safety_input = modbus_registers[IND_CONFIG_SAFETY_INPUT];
        //write value to eeprom
        configWriteEeprom16(1, config_safety_input);
    }
    if (config_safety_output != modbus_registers[IND_CONFIG_SAFETY_OUTPUT])
    {
        //save changes
        config_safety_output = modbus_registers[IND_CONFIG_SAFETY_OUTPUT];
        //write value to eeprom
        configWriteEeprom16(2, config_safety_output);
    }
}


/*******************************************************************************
 * configReadEeprom16
 * - read a 16 bit data from EEPROM
 ******************************************************************************/

uint16_t configReadEeprom16(uint8_t address)
{
    return ((uint16_t)(MCC_DATAEE_ReadByte(address * 2)) << 8) |
            ((uint16_t)(MCC_DATAEE_ReadByte(address * 2 + 1)));
}


/*******************************************************************************
 * configWriteEeprom16
 * - write a 16 bit data to EEPROM
 ******************************************************************************/

void configWriteEeprom16(uint8_t address, uint16_t data)
{
    MCC_DATAEE_WriteByte((address * 2), (uint8_t)(data >> 8));
    MCC_DATAEE_WriteByte((address * 2 + 1), (uint8_t)(data & 0xff));    
}
