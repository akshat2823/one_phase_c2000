/*
 * uart.h
 *
 *  Created on: Jul 22, 2025
 *      Author: Anamitra Sarkar
 */

#ifndef UART_H_
#define UART_H_


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Control_Variables.h"
#include "Device/driverlib/sci.h"
#include "device.h"
#include "driverlib.h"
#include "Config.h"
#include "Common_Memmap.h"
#include "modbus_CRC.h"


extern uint16_t txBuf[256];

extern void handle_Display_uart(uint16_t r_Buff[], uint16_t size);
extern void send_Data_to_STM(void);
extern void DSP_ready(void);
extern void ReadDatafromEEPROM(void);
static inline void ackDataReceive(void);
extern void handle_PFC_uart(uint16_t Pfc_buff[], uint16_t size);
extern void SyncCommToControl(void);

static inline void WriteFloatToBuff(uint8_t *buff, uint32_t addr, float32_t value);

void send_Data_to_STM_5C(void);
void send_Data_to_STM_6C(void);
void send_Data_to_STM_7C(void);
;
extern uint16_t DataSize;
extern bool MemRead;
extern int MemReadCount;
extern bool TransmitData;

extern uint16_t crcACKglobal[4];

extern int harmonicChunk;

#endif /* UART_H_ */
