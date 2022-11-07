#include "../header/hardware.h"
#include <pic18.h>
#include "../mcc_generated_files/mcc.h"

void uC_delay_ms(unsigned long ms){
    __delay_ms(ms);
}

uint8_t MCC_ID0_GetValue(void)
{
    return (uint8_t)ID0_GetValue();
}

uint8_t MCC_ID1_GetValue(void)
{
    return (uint8_t)ID1_GetValue();
}

uint8_t MCC_ID2_GetValue(void)
{
    return (uint8_t)ID2_GetValue();
}

uint8_t MCC_ID3_GetValue(void)
{
    return (uint8_t)ID3_GetValue();
}

void MCC_PIC_S_OUT1_SetHigh(void)
{
    PIC_S_OUT1_SetHigh();
}

void MCC_PIC_S_OUT2_SetHigh(void)
{
    PIC_S_OUT2_SetHigh();
}

void MCC_PIC_S_OUT3_SetHigh(void)
{
    PIC_S_OUT3_SetHigh();
}

void MCC_PIC_S_OUT4_SetHigh(void)
{
    PIC_S_OUT4_SetHigh();
}

void MCC_PIC_S_OUT5_SetHigh(void)
{
    PIC_S_OUT5_SetHigh();
}

void MCC_PIC_S_OUT1_SetLow(void)
{
    PIC_S_OUT1_SetLow();
}

void MCC_PIC_S_OUT2_SetLow(void)
{
    PIC_S_OUT2_SetLow();
}

void MCC_PIC_S_OUT3_SetLow(void)
{
    PIC_S_OUT3_SetLow();
}

void MCC_PIC_S_OUT4_SetLow(void)
{
    PIC_S_OUT4_SetLow();
}

void MCC_PIC_S_OUT5_SetLow(void)
{
    PIC_S_OUT5_SetLow();
}

uint16_t MCC_PIC_S_IN1_GetValue(void){
    return uint16_t PIC_S_IN1_GetValue();
}
uint16_t MCC_PIC_S_IN2_GetValue(void){
    return uint16_t PIC_S_IN2_GetValue();
}
uint16_t MCC_PIC_S_IN3_GetValue(void){
    return uint16_t PIC_S_IN3_GetValue();
}
uint16_t MCC_PIC_S_IN4_GetValue(void){
    return uint16_t PIC_S_IN4_GetValue();
}
uint16_t MCC_PIC_S_IN5_GetValue(void){
    return uint16_t PIC_S_IN5_GetValue();
}

uint8_t MCC_DATAEE_ReadByte(uint16_t bAdd)
{
    return DATAEE_ReadByte(bAdd);
}

void MCC_DATAEE_WriteByte(uint16_t bAdd, uint8_t bData)
{
    DATAEE_WriteByte(uint16_t bAdd, uint8_t bData)
}

void Set_Baudrate(uint8_t lowbyte, uint8_t highbyte)
{
    SPBRG1 = lowbyte;
    SPBRGH1 = highbyte;
}