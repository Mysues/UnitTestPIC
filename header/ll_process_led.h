/*******************************************************************************
 * This file provide the initialization and the process function for all RGB 
 * LEDs.
 * - process mirror the value of the modbus register to all LEDs colour
 * - init function turn off all LEDs
 * - this process also require the interrupt enable and disable handler to be
 *   passed for the LED processes as it is timing critical
 ******************************************************************************/ 

#ifndef LL_PROCESS_LED_H
#define	LL_PROCESS_LED_H

#include "stdint.h"


void ledInterruptHandler(
        void (* interruptDisable_)(void),
        void (* interruptEnable_)(void));

void ledInit(void);

void ledProcess(void);
void led1Process(void);
void led2Process(void);

void led1Reset(void);
void led1WriteByte(uint8_t data);
void led2Reset(void);
void led2WriteByte(uint8_t data);


#endif	/* LL_PROCESS_LED_H */

