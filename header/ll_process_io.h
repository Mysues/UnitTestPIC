/*******************************************************************************
 * This file provide the initialization and the process function for all io.
 * - process mirror the value in the modbus register to the outputs and vise 
 *   versa for inputs
 * - init function clear all the output on start
 ******************************************************************************/ 

#ifndef LL_PROCESS_IO_H
#define	LL_PROCESS_IO_H

#include "stdint.h"
#include "stdbool.h"

void ioInit(void);
void ioProcess(bool heartbeat_triggered);


#endif	/* LL_PROCESS_IO_H */

