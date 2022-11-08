/*******************************************************************************
 * This file provides the functions for the MODBUS RTU Communication Protocol.
 *******************************************************************************/

#ifndef MODBUS_RTU_H
#define	MODBUS_RTU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 *******************************************************************************/

void MODBUS_RTU_UartHandler(
        bool (* uartRxReady_)(void), 
        uint8_t (* uartRead_)(void), 
        void (* uartWrite_)(uint8_t));
void MODBUS_RTU_InterruptHandler(
        void (* interruptDisable_)(void),
        void (* interruptEnable_)(void));
void MODBUS_RTU_Init(uint16_t modbus_reg_[], uint16_t modbus_reg_rw_start_, 
        uint16_t modbus_reg_rw_end_, uint16_t modbus_reg_length_);
uint8_t MODBUS_RTU_ProcessFrame(void);
void MODBUS_RTU_Timeout(void);

#endif	/* MODBUS_RTU_H */
