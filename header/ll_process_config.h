/* 
 * File:   ll_process_config.h
 * Author: tanpi
 *
 * Created on May 16, 2021, 5:53 PM
 */

#ifndef LL_PROCESS_CONFIG_H
#define	LL_PROCESS_CONFIG_H

#include "stdint.h"

void configInit(void);
void configProcess(void);
uint16_t configReadEeprom16(uint8_t address);
void configWriteEeprom16(uint8_t address, uint16_t data);

#endif	/* LL_PROCESS_CONFIG_H */

