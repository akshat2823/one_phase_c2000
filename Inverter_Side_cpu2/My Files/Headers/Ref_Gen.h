/*
 * Ref_Gen.h
 *
 *  Created on: Dec 11, 2025
 *      Author: admin
 */

#ifndef MY_FILES_HEADERS_REF_GEN_H_
#define MY_FILES_HEADERS_REF_GEN_H_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "math.h"
#include "hw_types.h"
#include "Config.h"


extern uint16_t i;
extern uint16_t j;

extern float32_t thetaBase;
extern float32_t harmonicAngle;
extern float32_t resultA;
extern float32_t outA;

extern void Harmonic_Array_clear(void);
extern void Harmonic_Array_Init(void);
extern void updateBaseLookUpTable(void);
extern void Load_Received_Harmonics_To_Array(void);


#endif /* MY_FILES_HEADERS_REF_GEN_H_ */
