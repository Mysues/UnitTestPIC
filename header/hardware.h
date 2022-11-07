#ifndef HARDWARE
#define	HARDWARE

void uC_delay_ms(unsigned long ms);

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

#endif