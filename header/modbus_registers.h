/*******************************************************************************
 * This declare the modbus_registers for modbus RTU communication
 * - modbusRegistersInit function will initialize the ping, model and firmware 
 *   value according to the h file definition.
 ******************************************************************************/ 

#ifndef MODBUS_REGISTERS_H
#define	MODBUS_REGISTERS_H

#include "stdint.h"


/*******************************************************************************
 * PUBLIC DEFINITION
 *******************************************************************************/

// Index for MODBUS registers.
typedef enum {
    IND_PING        = 0x00,
    IND_MODEL       = 0x01,
    IND_FIRMWARE    = 0x02,
    IND_MODBUS_ID   = 0x03,
    
    IND_INPUT1 = 0x10,  //input
    IND_INPUT2 = 0x11,
    IND_INPUT3 = 0x12,
    IND_INPUT4 = 0x13,
    IND_INPUT5 = 0x14,

    IND_REG_RW_START = 0x20,

    IND_LED1 = 0x20,  //0x20-0x5F
    IND_LED2 = 0x60,  //0x60-0x9F

    IND_OUTPUT1 = 0xA0,
    IND_OUTPUT2 = 0xA1,
    IND_OUTPUT3 = 0xA2,
    IND_OUTPUT4 = 0xA3,
    IND_OUTPUT5 = 0xA4,

    IND_BAUDRATE = 0xA5,

    IND_HEARTBEAT = 0xA6,
    IND_SAFETY_SOFT_TRIGGER = 0xA7,
    IND_CONFIG_SAFETY_INPUT = 0xA8,
    IND_CONFIG_SAFETY_OUTPUT = 0xA9,

    IND_REG_RW_END  = 0xAF,
            
    IND_LAST_REG = 0xB0,
            
} MODBUS_REG_IND;


/*******************************************************************************
 * AGV Controller definition
 *******************************************************************************/

// Unique ping response
#define PING   0x55AA

// Firmware revision.
#define FIRMWARE    (2 << 8) | (0)  //version 2.00

// Model.
#define MODEL           10 //AGV-LL-1.00



/*******************************************************************************
* PUBLIC GLOBAL VARAIBLES PROTOTYPES                                           *
*******************************************************************************/

extern uint16_t modbus_registers[IND_LAST_REG];

void modbusRegistersInit(void);


#endif	/* MODBUS_REGISTERS_H */
