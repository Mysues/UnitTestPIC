
/*******************************************************************************
 * This file provide the initialization and the process function for all io.
 * - process mirror the value in the modbus register to the outputs and vise 
 *   versa for inputs
 * - init function clear all the output on start
 ******************************************************************************/ 

#include "ll_process_io.h"
#include "modbus_registers.h"
#include "mcc_generated_files/mcc.h"


/*******************************************************************************
 * ioInit
 * - clear all the output on start
 ******************************************************************************/ 

void ioInit(void)
{
    //clear all output on start
    PIC_S_OUT1_SetLow();
    PIC_S_OUT2_SetLow();
    PIC_S_OUT3_SetLow();
    PIC_S_OUT4_SetLow();
    PIC_S_OUT5_SetLow();
    
    //trigger safety soft trigger by default
    modbus_registers[IND_SAFETY_SOFT_TRIGGER] = 1;
}


/*******************************************************************************
 * ioProcess
 * - mirror the value in the modbus register to the output and vise versa for 
 *   inputs
 ******************************************************************************/ 

void ioProcess(bool heartbeat_triggered)
{
    //read input pin and update to register
    modbus_registers[IND_INPUT1] = (uint16_t)(!PIC_S_IN1_GetValue());
    modbus_registers[IND_INPUT2] = (uint16_t)(!PIC_S_IN2_GetValue());
    modbus_registers[IND_INPUT3] = (uint16_t)(!PIC_S_IN3_GetValue());
    modbus_registers[IND_INPUT4] = (uint16_t)(!PIC_S_IN4_GetValue());
    modbus_registers[IND_INPUT5] = (uint16_t)(!PIC_S_IN5_GetValue());
    
    //check if there is any safety trigger
    bool safety_trigger = false;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x01) != 0) &&
        (PIC_S_IN1_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x02) != 0) &&
        (PIC_S_IN2_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x04) != 0) &&
        (PIC_S_IN3_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x08) != 0) &&
        (PIC_S_IN4_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x10) != 0) &&
        (PIC_S_IN5_GetValue() == 1)) safety_trigger = true;
    if (modbus_registers[IND_SAFETY_SOFT_TRIGGER] != 0) safety_trigger = true;
    if (heartbeat_triggered) safety_trigger = true;

    //update output pin according to register
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x01) != 0)
    {
        if (safety_trigger) PIC_S_OUT1_SetLow();
        else PIC_S_OUT1_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT1] == 1) 
    {
        PIC_S_OUT1_SetHigh();
    }
    else 
    {
        PIC_S_OUT1_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x02) != 0)
    {
        if (safety_trigger) PIC_S_OUT2_SetLow();
        else PIC_S_OUT2_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT2] == 1) 
    {
        PIC_S_OUT2_SetHigh();
    }
    else 
    {
        PIC_S_OUT2_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x04) != 0)
    {
        if (safety_trigger) PIC_S_OUT3_SetLow();
        else PIC_S_OUT3_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT3] == 1) 
    {
        PIC_S_OUT3_SetHigh();
    }
    else 
    {
        PIC_S_OUT3_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x08) != 0)
    {
        if (safety_trigger) PIC_S_OUT4_SetLow();
        else PIC_S_OUT4_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT4] == 1) 
    {
        PIC_S_OUT4_SetHigh();
    }
    else 
    {
        PIC_S_OUT4_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x10) != 0)
    {
        if (safety_trigger) PIC_S_OUT5_SetLow();
        else PIC_S_OUT5_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT5] == 1) 
    {
        PIC_S_OUT5_SetHigh();
    }
    else 
    {
        PIC_S_OUT5_SetLow();
    }
}


