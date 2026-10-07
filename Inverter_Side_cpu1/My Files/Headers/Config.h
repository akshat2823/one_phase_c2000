/*
 * Config.h
 *
 *  Created on: Jul 25, 2025
 *      Author: admin
 */

#ifndef MY_FILES_HEADERS_CONFIG_H_
#define MY_FILES_HEADERS_CONFIG_H_

#define MAX_LENGTH          1500
#define MAX_HARMONIC_NO     50
#define LUT_SIZE            720
#define TWO_PI              6.283185307f

typedef union
{
    float32_t floatVal;
    uint16_t int16data[2];
}FloatToUint16;

extern FloatToUint16 floatConv;

typedef union
{
    int32_t intVal;
    uint16_t int16data[2];
}IntToUint16;

extern IntToUint16 intConv;
extern uint32_t readGPIO;
extern uint32_t StatusRegA;
extern uint32_t Prot_StatusResetFlag;

typedef struct{
    uint16_t VarAddr[2];
    uint16_t dataLength[2];
}SharedFlags;

extern volatile SharedFlags cpu1Read_Flags;
extern volatile int cpu1Write_Flag;
extern volatile uint16_t cpu1Read[MAX_LENGTH];
extern volatile uint16_t cpu1Write[MAX_LENGTH];

extern volatile bool masterFlag;
extern volatile bool Slave1Flag;
extern volatile bool Slave2Flag;

extern volatile signed int BaseLUT_A[LUT_SIZE];
extern volatile signed int BaseLUT_B[LUT_SIZE];
extern volatile signed int BaseLUT_C[LUT_SIZE];
extern volatile float32_t HarmonicA[50][3];
extern volatile float32_t HarmonicB[50][3];
extern volatile float32_t HarmonicC[50][3];


extern volatile uint16_t handshake;
extern volatile bool handshake_flag;


extern volatile uint16_t seqIndex;
extern volatile bool seq_run;
extern volatile float32_t seq_time;
extern volatile float32_t volt_step_rise_time;
extern volatile float32_t freq_step_rise_time;
extern volatile float32_t total_step_time;
extern volatile uint32_t total_timer_count_per_step;
extern volatile uint32_t timerCount;


#endif /* MY_FILES_HEADERS_CONFIG_H_ */
