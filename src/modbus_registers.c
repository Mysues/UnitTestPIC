/*******************************************************************************
 * This declare the modbus_registers for modbus RTU communication
 * - modbusRegistersInit function will initialize the ping, model and firmware 
 *   value according to the h file definition.
 ******************************************************************************/ 

#include "modbus_registers.h"


/*******************************************************************************
* PUBLIC GLOBAL VARIABLES                                                      *
*******************************************************************************/

// MODBUS register.
uint16_t modbus_registers[IND_LAST_REG] = {0};


/*******************************************************************************
* modbusRegistersInit                                                    *
*******************************************************************************/

void modbusRegistersInit(void)
{
    modbus_registers[IND_PING] = PING;
    modbus_registers[IND_MODEL] = MODEL;
    modbus_registers[IND_FIRMWARE] = FIRMWARE;
}
