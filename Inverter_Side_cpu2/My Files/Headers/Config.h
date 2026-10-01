/*
 * Config.h
 *
 *  Created on: Jul 24, 2025
 *      Author: Anamitra Sarkar
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define SINGLE_PHASE     1
#define THREE_PHASE      2
#define CONVERTER_TYPE  SINGLE_PHASE


#define MAX_LENGTH      1174
extern uint16_t Receive_Buf_Secondary[MAX_LENGTH];
extern uint16_t Receive_Buf_Primary[MAX_LENGTH];  // to handle incoming data from IOD, connected to SCIB
extern uint16_t Receive_Buf_Primary1[MAX_LENGTH];  // to handle incoming data from PFC, connected to SCIC

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

typedef struct {
    uint16_t VarAddr[2];
    uint16_t dataLength[2];
}SharedFlags;

extern volatile SharedFlags cpu2Write_Flags;
extern volatile int cpu2Read_Flag;
extern volatile uint16_t cpu2Read[MAX_LENGTH];
extern volatile uint16_t cpu2Write[MAX_LENGTH];
extern volatile bool masterFlag;
extern volatile bool Slave1Flag;
extern volatile bool Slave2Flag;

extern volatile signed int BaseLUT_A[LUT_SIZE];
extern volatile signed int BaseLUT_B[LUT_SIZE];
extern volatile signed int BaseLUT_C[LUT_SIZE];
extern volatile float32_t HarmonicA[50][3];
extern volatile float32_t HarmonicB[50][3];
extern volatile float32_t HarmonicC[50][3];


extern volatile float32_t Angle_Step;
extern volatile uint16_t transmitHeader;
extern volatile uint16_t receiveHeader_setVal;
extern volatile uint16_t receiveHeader_MeasVal;

//extern uint16_t SendBuffer[256];
extern uint16_t transmitBuff[MAX_LENGTH];

extern uint16_t Start_Address;
extern uint16_t DataSize;

extern volatile uint16_t crcCheck;

extern int check1;
extern int check1_prev;
extern uint16_t tempArr[MAX_LENGTH];

#endif /* CONFIG_H_ */
