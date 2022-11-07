
/*******************************************************************************
 * This file provide the initialization and the process function for all io.
 * - process mirror the value in the modbus register to the outputs and vise 
 *   versa for inputs
 * - init function clear all the output on start
 ******************************************************************************/ 

#include "../header/ll_process_io.h"
#include "../header/modbus_registers.h"
#include "../header/hardware.h"


/*******************************************************************************
 * ioInit
 * - clear all the output on start
 ******************************************************************************/ 

void ioInit(void)
{
    //clear all output on start
    MCC_PIC_S_OUT1_SetLow();
    MCC_PIC_S_OUT2_SetLow();
    MCC_PIC_S_OUT3_SetLow();
    MCC_PIC_S_OUT4_SetLow();
    MCC_PIC_S_OUT5_SetLow();
    
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
    modbus_registers[IND_INPUT1] = (uint16_t)(!MCC_PIC_S_IN1_GetValue());
    modbus_registers[IND_INPUT2] = (uint16_t)(!MCC_PIC_S_IN2_GetValue());
    modbus_registers[IND_INPUT3] = (uint16_t)(!MCC_PIC_S_IN3_GetValue());
    modbus_registers[IND_INPUT4] = (uint16_t)(!MCC_PIC_S_IN4_GetValue());
    modbus_registers[IND_INPUT5] = (uint16_t)(!MCC_PIC_S_IN5_GetValue());
    
    //check if there is any safety trigger
    bool safety_trigger = false;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x01) != 0) &&
        (MCC_PIC_S_IN1_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x02) != 0) &&
        (MCC_PIC_S_IN2_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x04) != 0) &&
        (MCC_PIC_S_IN3_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x08) != 0) &&
        (MCC_PIC_S_IN4_GetValue() == 1)) safety_trigger = true;
    if (((modbus_registers[IND_CONFIG_SAFETY_INPUT] & 0x10) != 0) &&
        (MCC_PIC_S_IN5_GetValue() == 1)) safety_trigger = true;
    if (modbus_registers[IND_SAFETY_SOFT_TRIGGER] != 0) safety_trigger = true;
    if (heartbeat_triggered) safety_trigger = true;

    //update output pin according to register
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x01) != 0)
    {
        if (safety_trigger) MCC_PIC_S_OUT1_SetLow();
        else MCC_PIC_S_OUT1_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT1] == 1) 
    {
        MCC_PIC_S_OUT1_SetHigh();
    }
    else 
    {
        MCC_PIC_S_OUT1_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x02) != 0)
    {
        if (safety_trigger) MCC_PIC_S_OUT2_SetLow();
        else MCC_PIC_S_OUT2_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT2] == 1) 
    {
        MCC_PIC_S_OUT2_SetHigh();
    }
    else 
    {
        MCC_PIC_S_OUT2_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x04) != 0)
    {
        if (safety_trigger) MCC_PIC_S_OUT3_SetLow();
        else MCC_PIC_S_OUT3_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT3] == 1) 
    {
        MCC_PIC_S_OUT3_SetHigh();
    }
    else 
    {
        MCC_PIC_S_OUT3_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x08) != 0)
    {
        if (safety_trigger) MCC_PIC_S_OUT4_SetLow();
        else MCC_PIC_S_OUT4_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT4] == 1) 
    {
        MCC_PIC_S_OUT4_SetHigh();
    }
    else 
    {
        MCC_PIC_S_OUT4_SetLow();
    }
    if ((modbus_registers[IND_CONFIG_SAFETY_OUTPUT] & 0x10) != 0)
    {
        if (safety_trigger) MCC_PIC_S_OUT5_SetLow();
        else MCC_PIC_S_OUT5_SetHigh();
    }
    else if (modbus_registers[IND_OUTPUT5] == 1) 
    {
        MCC_PIC_S_OUT5_SetHigh();
    }
    else 
    {
        MCC_PIC_S_OUT5_SetLow();
    }
}


