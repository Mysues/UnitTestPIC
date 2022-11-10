#ifndef HARDWARE
#define	HARDWARE

#include <stdbool.h>

void uC_delay_ms(unsigned long ms);
void uC_delay_us(unsigned long us);

uint8_t MCC_ID0_GetValue(void);
uint8_t MCC_ID1_GetValue(void);
uint8_t MCC_ID2_GetValue(void);
uint8_t MCC_ID3_GetValue(void);

void MCC_PIC_S_OUT1_SetHigh(void);
void MCC_PIC_S_OUT2_SetHigh(void);
void MCC_PIC_S_OUT3_SetHigh(void);
void MCC_PIC_S_OUT4_SetHigh(void);
void MCC_PIC_S_OUT5_SetHigh(void);

void MCC_PIC_S_OUT1_SetLow(void);
void MCC_PIC_S_OUT2_SetLow(void);
void MCC_PIC_S_OUT3_SetLow(void);
void MCC_PIC_S_OUT4_SetLow(void);
void MCC_PIC_S_OUT5_SetLow(void);

uint16_t MCC_PIC_S_IN1_GetValue(void);
uint16_t MCC_PIC_S_IN2_GetValue(void);
uint16_t MCC_PIC_S_IN3_GetValue(void);
uint16_t MCC_PIC_S_IN4_GetValue(void);
uint16_t MCC_PIC_S_IN5_GetValue(void);

uint8_t MCC_DATAEE_ReadByte(uint16_t bAdd);
void MCC_DATAEE_WriteByte(uint16_t bAdd, uint8_t bData);

void Set_Baudrate(uint8_t lowbyte, uint8_t highbyte);

void MCC_PIC_RGB_CONTROL_SetHigh(void);
void MCC_PIC_RGB_CONTROL_SetLow(void);

void MCC_PIC_RGB_CONTROL2_SetHigh(void);
void MCC_PIC_RGB_CONTROL2_SetLow(void);

void MCC_TMR0_SetInterruptHandler(void (* InterruptHandler)(void));
void MCC_TMR1_SetInterruptHandler(void (* InterruptHandler)(void));
void MCC_TMR2_SetInterruptHandler(void (* InterruptHandler)(void));

void MCC_EUSART1_SetRxInterruptHandler(void (* interruptHandler)(void));
bool MCC_EUSART1_is_rx_ready(void);
uint8_t MCC_EUSART1_Read(void);
void MCC_EUSART1_Write(uint8_t data);

void MCC_TMR0_StartTimer(void);
void MCC_TMR0_StopTimer(void);
void MCC_TMR1_StartTimer(void);
void MCC_TMR1_StopTimer(void);

void MCC_TMR0_Reload(void);
void MCC_TMR1_Reload(void);

void MCC_EUSART1_Receive_ISR(void);

void MCC_INTERRUPT_GlobalInterruptHighEnable(void);
void MCC_INTERRUPT_GlobalInterruptHighDisable(void);

void MCC_LED_STATUS_SetHigh(void);
void MCC_LED_COM_SetLow(void);
void MCC_LED_COM_Toggle(void);

#endif