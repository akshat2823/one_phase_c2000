/*
 * Common_Memmap.h
 *
 *  Created on: Jul 22, 2025
 *      Author: Anamitra Sarkar
 */

#ifndef COMMON_MEMMAP_H_
#define COMMON_MEMMAP_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "device.h"
#include "driverlib.h"
#include "Config.h"
#include "Control_Variables.h"

#define SIZE_FLOAT              4
#define SIZE_U32                4
#define SIZE_U8                 1

#define READ_HARMONIC_FROM_MAIN(n)                                      \
    do                                                                  \
    {                                                                   \
        harm##n##_no  = ReadFloatFromMainBuff(DSP_HARM_NUM(n##U));      \
        harm##n##_amp = ReadFloatFromMainBuff(DSP_HARM_PERCENT(n##U));      \
        harm##n##_pha = ReadFloatFromMainBuff(DSP_HARM_PHASE(n##U));    \
    } while(0)

typedef enum{
    TYPE_FLOAT32,
    TYPE_UINT32
} DataType;

typedef struct{
    uint16_t BUF_ADR;
    volatile void *variable_ptr;
    DataType type;
} DataMapEntry;

#if CONVERTER_TYPE == SINGLE_PHASE

//------------DSP Addresses------------------------
// ========================================================================
// 1. MEASUREMENTS (DSP Phase X -> MCU)
// ========================================================================

#define DSP_MEAS_START_ADDR                     (1U)

#define DSP_MEAS_VAC                            (DSP_MEAS_START_ADDR)
#define DSP_MEAS_IAC                            (DSP_MEAS_VAC + SIZE_FLOAT)
#define DSP_MEAS_FREQ                           (DSP_MEAS_IAC + SIZE_FLOAT)
#define DSP_MEAS_PREAL                          (DSP_MEAS_FREQ + SIZE_FLOAT)
#define DSP_MEAS_PF                             (DSP_MEAS_PREAL + SIZE_FLOAT)

#define DSP_MEAS_VDC                            (DSP_MEAS_PF + SIZE_FLOAT)
#define DSP_MEAS_IDC                            (DSP_MEAS_VDC + SIZE_FLOAT)
#define DSP_MEAS_VPEAK_POS                      (DSP_MEAS_IDC + SIZE_FLOAT)
#define DSP_MEAS_VPEAK_NEG                      (DSP_MEAS_VPEAK_POS + SIZE_FLOAT)
#define DSP_MEAS_IPEAK_POS                      (DSP_MEAS_VPEAK_NEG + SIZE_FLOAT)
#define DSP_MEAS_IPEAK_NEG                      (DSP_MEAS_IPEAK_POS + SIZE_FLOAT)

#define DSP_MEAS_VCREST_FACTOR                  (DSP_MEAS_IPEAK_NEG + SIZE_FLOAT)
#define DSP_MEAS_ICREST_FACTOR                  (DSP_MEAS_VCREST_FACTOR + SIZE_FLOAT)

#define DSP_STATUS_A                            (DSP_MEAS_ICREST_FACTOR + SIZE_FLOAT)
#define DSP_STATUS_B                            (DSP_STATUS_A + SIZE_U32)

#define DSP_MEAS_END_ADDR                       (DSP_STATUS_B + SIZE_U32)


// ========================================================================
// 2. SETPOINTS & LIMITS (MCU -> DSP Phase X)
// ========================================================================

#define DSP_SET_START_ADDR                      (DSP_MEAS_END_ADDR)

#define DSP_ACPS_MODE                           (DSP_SET_START_ADDR)
#define DSP_LOAD_SOURCE_MODE                    (DSP_ACPS_MODE + SIZE_U8)
#define DSP_LOAD_MODE                           (DSP_LOAD_SOURCE_MODE + SIZE_U8)
#define DSP_TOPOLOGY_SELECT                     (DSP_LOAD_MODE + SIZE_U8)
#define DSP_SET_FREQ                            (DSP_TOPOLOGY_SELECT + SIZE_U8)

#define DSP_SET_VAC                             (DSP_SET_FREQ + SIZE_FLOAT)
#define DSP_SET_IAC                             (DSP_SET_VAC + SIZE_FLOAT)
#define DSP_SET_VDC                             (DSP_SET_IAC + SIZE_FLOAT)

#define DSP_LOAD_CR_R                           (DSP_SET_VDC + SIZE_FLOAT)
#define DSP_LOAD_CP_P                           (DSP_LOAD_CR_R + SIZE_FLOAT)
#define DSP_LOAD_CP_PF                          (DSP_LOAD_CP_P + SIZE_FLOAT)
#define DSP_LOAD_CC_I_PF                        (DSP_LOAD_CP_PF + SIZE_FLOAT)


#define DSP_ADR_SET_R_TOP                       (DSP_LOAD_CC_I_PF + SIZE_FLOAT)
#define DSP_ADR_SET_L_TOP                       (DSP_ADR_SET_R_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_C_TOP                       (DSP_ADR_SET_L_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_RL_TOP                      (DSP_ADR_SET_C_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_RC_TOP                      (DSP_ADR_SET_RL_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_RS_TOP                      (DSP_ADR_SET_RC_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_P_TOP                       (DSP_ADR_SET_RS_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_QL_TOP                      (DSP_ADR_SET_P_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_QC_TOP                      (DSP_ADR_SET_QL_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_IL_TOP                      (DSP_ADR_SET_QC_TOP + SIZE_FLOAT)
#define DSP_ADR_SET_VC_TOP                      (DSP_ADR_SET_IL_TOP + SIZE_FLOAT)

#define DSP_LIM_VAC                             (DSP_ADR_SET_VC_TOP + SIZE_FLOAT)
#define DSP_LIM_IAC                             (DSP_LIM_VAC + SIZE_FLOAT)
#define DSP_LIM_FREQ                            (DSP_LIM_IAC + SIZE_FLOAT)
#define DSP_LIM_POW                             (DSP_LIM_FREQ + SIZE_FLOAT)
#define DSP_LIM_VDC_PLUS                        (DSP_LIM_POW + SIZE_FLOAT)
#define DSP_LIM_VDC_MINUS                       (DSP_LIM_VDC_PLUS + SIZE_FLOAT)

// ========================================================================
// 3. HARMONIC SETTINGS (MCU -> DSP Phase X)
// ========================================================================


#define DSP_HARM_WAVEFORM_NUM                   (DSP_LIM_VDC_MINUS + SIZE_FLOAT)

// ========================================================================
// HARMONIC SETTINGS
// ========================================================================

#define DSP_HARM_START_ADDR         (DSP_HARM_WAVEFORM_NUM + SIZE_U8)


// ========================================================================
// HARMONIC 1
// ========================================================================

#define DSP_HARM1_NUM               (DSP_HARM_START_ADDR)
#define DSP_HARM1_PERCENT           (DSP_HARM1_NUM + SIZE_FLOAT)
#define DSP_HARM1_PHASE             (DSP_HARM1_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 2
// ========================================================================

#define DSP_HARM2_NUM               (DSP_HARM1_PHASE + SIZE_FLOAT)
#define DSP_HARM2_PERCENT           (DSP_HARM2_NUM + SIZE_FLOAT)
#define DSP_HARM2_PHASE             (DSP_HARM2_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 3
// ========================================================================

#define DSP_HARM3_NUM               (DSP_HARM2_PHASE + SIZE_FLOAT)
#define DSP_HARM3_PERCENT           (DSP_HARM3_NUM + SIZE_FLOAT)
#define DSP_HARM3_PHASE             (DSP_HARM3_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 4
// ========================================================================

#define DSP_HARM4_NUM               (DSP_HARM3_PHASE + SIZE_FLOAT)
#define DSP_HARM4_PERCENT           (DSP_HARM4_NUM + SIZE_FLOAT)
#define DSP_HARM4_PHASE             (DSP_HARM4_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 5
// ========================================================================

#define DSP_HARM5_NUM               (DSP_HARM4_PHASE + SIZE_FLOAT)
#define DSP_HARM5_PERCENT           (DSP_HARM5_NUM + SIZE_FLOAT)
#define DSP_HARM5_PHASE             (DSP_HARM5_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 6
// ========================================================================

#define DSP_HARM6_NUM               (DSP_HARM5_PHASE + SIZE_FLOAT)
#define DSP_HARM6_PERCENT           (DSP_HARM6_NUM + SIZE_FLOAT)
#define DSP_HARM6_PHASE             (DSP_HARM6_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 7
// ========================================================================

#define DSP_HARM7_NUM               (DSP_HARM6_PHASE + SIZE_FLOAT)
#define DSP_HARM7_PERCENT           (DSP_HARM7_NUM + SIZE_FLOAT)
#define DSP_HARM7_PHASE             (DSP_HARM7_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 8
// ========================================================================

#define DSP_HARM8_NUM               (DSP_HARM7_PHASE + SIZE_FLOAT)
#define DSP_HARM8_PERCENT           (DSP_HARM8_NUM + SIZE_FLOAT)
#define DSP_HARM8_PHASE             (DSP_HARM8_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 9
// ========================================================================

#define DSP_HARM9_NUM               (DSP_HARM8_PHASE + SIZE_FLOAT)
#define DSP_HARM9_PERCENT           (DSP_HARM9_NUM + SIZE_FLOAT)
#define DSP_HARM9_PHASE             (DSP_HARM9_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 10
// ========================================================================

#define DSP_HARM10_NUM              (DSP_HARM9_PHASE + SIZE_FLOAT)
#define DSP_HARM10_PERCENT          (DSP_HARM10_NUM + SIZE_FLOAT)
#define DSP_HARM10_PHASE            (DSP_HARM10_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 11
// ========================================================================

#define DSP_HARM11_NUM              (DSP_HARM10_PHASE + SIZE_FLOAT)
#define DSP_HARM11_PERCENT          (DSP_HARM11_NUM + SIZE_FLOAT)
#define DSP_HARM11_PHASE            (DSP_HARM11_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 12
// ========================================================================

#define DSP_HARM12_NUM              (DSP_HARM11_PHASE + SIZE_FLOAT)
#define DSP_HARM12_PERCENT          (DSP_HARM12_NUM + SIZE_FLOAT)
#define DSP_HARM12_PHASE            (DSP_HARM12_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 13
// ========================================================================

#define DSP_HARM13_NUM              (DSP_HARM12_PHASE + SIZE_FLOAT)
#define DSP_HARM13_PERCENT          (DSP_HARM13_NUM + SIZE_FLOAT)
#define DSP_HARM13_PHASE            (DSP_HARM13_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 14
// ========================================================================

#define DSP_HARM14_NUM              (DSP_HARM13_PHASE + SIZE_FLOAT)
#define DSP_HARM14_PERCENT          (DSP_HARM14_NUM + SIZE_FLOAT)
#define DSP_HARM14_PHASE            (DSP_HARM14_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 15
// ========================================================================

#define DSP_HARM15_NUM              (DSP_HARM14_PHASE + SIZE_FLOAT)
#define DSP_HARM15_PERCENT          (DSP_HARM15_NUM + SIZE_FLOAT)
#define DSP_HARM15_PHASE            (DSP_HARM15_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 16
// ========================================================================

#define DSP_HARM16_NUM              (DSP_HARM15_PHASE + SIZE_FLOAT)
#define DSP_HARM16_PERCENT          (DSP_HARM16_NUM + SIZE_FLOAT)
#define DSP_HARM16_PHASE            (DSP_HARM16_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 17
// ========================================================================

#define DSP_HARM17_NUM              (DSP_HARM16_PHASE + SIZE_FLOAT)
#define DSP_HARM17_PERCENT          (DSP_HARM17_NUM + SIZE_FLOAT)
#define DSP_HARM17_PHASE            (DSP_HARM17_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 18
// ========================================================================

#define DSP_HARM18_NUM              (DSP_HARM17_PHASE + SIZE_FLOAT)
#define DSP_HARM18_PERCENT          (DSP_HARM18_NUM + SIZE_FLOAT)
#define DSP_HARM18_PHASE            (DSP_HARM18_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 19
// ========================================================================

#define DSP_HARM19_NUM              (DSP_HARM18_PHASE + SIZE_FLOAT)
#define DSP_HARM19_PERCENT          (DSP_HARM19_NUM + SIZE_FLOAT)
#define DSP_HARM19_PHASE            (DSP_HARM19_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 20
// ========================================================================

#define DSP_HARM20_NUM              (DSP_HARM19_PHASE + SIZE_FLOAT)
#define DSP_HARM20_PERCENT          (DSP_HARM20_NUM + SIZE_FLOAT)
#define DSP_HARM20_PHASE            (DSP_HARM20_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 21
// ========================================================================

#define DSP_HARM21_NUM              (DSP_HARM20_PHASE + SIZE_FLOAT)
#define DSP_HARM21_PERCENT          (DSP_HARM21_NUM + SIZE_FLOAT)
#define DSP_HARM21_PHASE            (DSP_HARM21_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 22
// ========================================================================

#define DSP_HARM22_NUM              (DSP_HARM21_PHASE + SIZE_FLOAT)
#define DSP_HARM22_PERCENT          (DSP_HARM22_NUM + SIZE_FLOAT)
#define DSP_HARM22_PHASE            (DSP_HARM22_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 23
// ========================================================================

#define DSP_HARM23_NUM              (DSP_HARM22_PHASE + SIZE_FLOAT)
#define DSP_HARM23_PERCENT          (DSP_HARM23_NUM + SIZE_FLOAT)
#define DSP_HARM23_PHASE            (DSP_HARM23_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 24
// ========================================================================

#define DSP_HARM24_NUM              (DSP_HARM23_PHASE + SIZE_FLOAT)
#define DSP_HARM24_PERCENT          (DSP_HARM24_NUM + SIZE_FLOAT)
#define DSP_HARM24_PHASE            (DSP_HARM24_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 25
// ========================================================================

#define DSP_HARM25_NUM              (DSP_HARM24_PHASE + SIZE_FLOAT)
#define DSP_HARM25_PERCENT          (DSP_HARM25_NUM + SIZE_FLOAT)
#define DSP_HARM25_PHASE            (DSP_HARM25_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 26
// ========================================================================

#define DSP_HARM26_NUM              (DSP_HARM25_PHASE + SIZE_FLOAT)
#define DSP_HARM26_PERCENT          (DSP_HARM26_NUM + SIZE_FLOAT)
#define DSP_HARM26_PHASE            (DSP_HARM26_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 27
// ========================================================================

#define DSP_HARM27_NUM              (DSP_HARM26_PHASE + SIZE_FLOAT)
#define DSP_HARM27_PERCENT          (DSP_HARM27_NUM + SIZE_FLOAT)
#define DSP_HARM27_PHASE            (DSP_HARM27_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 28
// ========================================================================

#define DSP_HARM28_NUM              (DSP_HARM27_PHASE + SIZE_FLOAT)
#define DSP_HARM28_PERCENT          (DSP_HARM28_NUM + SIZE_FLOAT)
#define DSP_HARM28_PHASE            (DSP_HARM28_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 29
// ========================================================================

#define DSP_HARM29_NUM              (DSP_HARM28_PHASE + SIZE_FLOAT)
#define DSP_HARM29_PERCENT          (DSP_HARM29_NUM + SIZE_FLOAT)
#define DSP_HARM29_PHASE            (DSP_HARM29_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 30
// ========================================================================

#define DSP_HARM30_NUM              (DSP_HARM29_PHASE + SIZE_FLOAT)
#define DSP_HARM30_PERCENT          (DSP_HARM30_NUM + SIZE_FLOAT)
#define DSP_HARM30_PHASE            (DSP_HARM30_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 31
// ========================================================================

#define DSP_HARM31_NUM              (DSP_HARM30_PHASE + SIZE_FLOAT)
#define DSP_HARM31_PERCENT          (DSP_HARM31_NUM + SIZE_FLOAT)
#define DSP_HARM31_PHASE            (DSP_HARM31_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 32
// ========================================================================

#define DSP_HARM32_NUM              (DSP_HARM31_PHASE + SIZE_FLOAT)
#define DSP_HARM32_PERCENT          (DSP_HARM32_NUM + SIZE_FLOAT)
#define DSP_HARM32_PHASE            (DSP_HARM32_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 33
// ========================================================================

#define DSP_HARM33_NUM              (DSP_HARM32_PHASE + SIZE_FLOAT)
#define DSP_HARM33_PERCENT          (DSP_HARM33_NUM + SIZE_FLOAT)
#define DSP_HARM33_PHASE            (DSP_HARM33_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 34
// ========================================================================

#define DSP_HARM34_NUM              (DSP_HARM33_PHASE + SIZE_FLOAT)
#define DSP_HARM34_PERCENT          (DSP_HARM34_NUM + SIZE_FLOAT)
#define DSP_HARM34_PHASE            (DSP_HARM34_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 35
// ========================================================================

#define DSP_HARM35_NUM              (DSP_HARM34_PHASE + SIZE_FLOAT)
#define DSP_HARM35_PERCENT          (DSP_HARM35_NUM + SIZE_FLOAT)
#define DSP_HARM35_PHASE            (DSP_HARM35_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 36
// ========================================================================

#define DSP_HARM36_NUM              (DSP_HARM35_PHASE + SIZE_FLOAT)
#define DSP_HARM36_PERCENT          (DSP_HARM36_NUM + SIZE_FLOAT)
#define DSP_HARM36_PHASE            (DSP_HARM36_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 37
// ========================================================================

#define DSP_HARM37_NUM              (DSP_HARM36_PHASE + SIZE_FLOAT)
#define DSP_HARM37_PERCENT          (DSP_HARM37_NUM + SIZE_FLOAT)
#define DSP_HARM37_PHASE            (DSP_HARM37_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 38
// ========================================================================

#define DSP_HARM38_NUM              (DSP_HARM37_PHASE + SIZE_FLOAT)
#define DSP_HARM38_PERCENT          (DSP_HARM38_NUM + SIZE_FLOAT)
#define DSP_HARM38_PHASE            (DSP_HARM38_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 39
// ========================================================================

#define DSP_HARM39_NUM              (DSP_HARM38_PHASE + SIZE_FLOAT)
#define DSP_HARM39_PERCENT          (DSP_HARM39_NUM + SIZE_FLOAT)
#define DSP_HARM39_PHASE            (DSP_HARM39_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 40
// ========================================================================

#define DSP_HARM40_NUM              (DSP_HARM39_PHASE + SIZE_FLOAT)
#define DSP_HARM40_PERCENT          (DSP_HARM40_NUM + SIZE_FLOAT)
#define DSP_HARM40_PHASE            (DSP_HARM40_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 41
// ========================================================================

#define DSP_HARM41_NUM              (DSP_HARM40_PHASE + SIZE_FLOAT)
#define DSP_HARM41_PERCENT          (DSP_HARM41_NUM + SIZE_FLOAT)
#define DSP_HARM41_PHASE            (DSP_HARM41_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 42
// ========================================================================

#define DSP_HARM42_NUM              (DSP_HARM41_PHASE + SIZE_FLOAT)
#define DSP_HARM42_PERCENT          (DSP_HARM42_NUM + SIZE_FLOAT)
#define DSP_HARM42_PHASE            (DSP_HARM42_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 43
// ========================================================================

#define DSP_HARM43_NUM              (DSP_HARM42_PHASE + SIZE_FLOAT)
#define DSP_HARM43_PERCENT          (DSP_HARM43_NUM + SIZE_FLOAT)
#define DSP_HARM43_PHASE            (DSP_HARM43_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 44
// ========================================================================

#define DSP_HARM44_NUM              (DSP_HARM43_PHASE + SIZE_FLOAT)
#define DSP_HARM44_PERCENT          (DSP_HARM44_NUM + SIZE_FLOAT)
#define DSP_HARM44_PHASE            (DSP_HARM44_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 45
// ========================================================================

#define DSP_HARM45_NUM              (DSP_HARM44_PHASE + SIZE_FLOAT)
#define DSP_HARM45_PERCENT          (DSP_HARM45_NUM + SIZE_FLOAT)
#define DSP_HARM45_PHASE            (DSP_HARM45_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 46
// ========================================================================

#define DSP_HARM46_NUM              (DSP_HARM45_PHASE + SIZE_FLOAT)
#define DSP_HARM46_PERCENT          (DSP_HARM46_NUM + SIZE_FLOAT)
#define DSP_HARM46_PHASE            (DSP_HARM46_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 47
// ========================================================================

#define DSP_HARM47_NUM              (DSP_HARM46_PHASE + SIZE_FLOAT)
#define DSP_HARM47_PERCENT          (DSP_HARM47_NUM + SIZE_FLOAT)
#define DSP_HARM47_PHASE            (DSP_HARM47_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 48
// ========================================================================

#define DSP_HARM48_NUM              (DSP_HARM47_PHASE + SIZE_FLOAT)
#define DSP_HARM48_PERCENT          (DSP_HARM48_NUM + SIZE_FLOAT)
#define DSP_HARM48_PHASE            (DSP_HARM48_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 49
// ========================================================================

#define DSP_HARM49_NUM              (DSP_HARM48_PHASE + SIZE_FLOAT)
#define DSP_HARM49_PERCENT          (DSP_HARM49_NUM + SIZE_FLOAT)
#define DSP_HARM49_PHASE            (DSP_HARM49_PERCENT + SIZE_FLOAT)


// ========================================================================
// HARMONIC 50
// ========================================================================

#define DSP_HARM50_NUM              (DSP_HARM49_PHASE + SIZE_FLOAT)
#define DSP_HARM50_PERCENT          (DSP_HARM50_NUM + SIZE_FLOAT)
#define DSP_HARM50_PHASE            (DSP_HARM50_PERCENT + SIZE_FLOAT)


// ========================================================================
// END OF HARMONIC DATA
// ========================================================================

#define DSP_HARM_END_ADDR           (DSP_HARM50_PHASE + SIZE_FLOAT)

// ========================================================================
// 4. SLEW / PHASE / CONTROL SETTINGS (MCU -> DSP Phase X)
// ========================================================================

#define DSP_VACSLEW                             (DSP_HARM_END_ADDR)
#define DSP_VDCSLEW                             (DSP_VACSLEW + SIZE_FLOAT)
#define DSP_OUT_FREQSLEW                        (DSP_VDCSLEW + SIZE_FLOAT)

#define DSP_PHASE_ANGLE                         (DSP_OUT_FREQSLEW + SIZE_FLOAT)

#define DSP_STATUS_CLEAR_A                      (DSP_PHASE_ANGLE + SIZE_FLOAT)
#define DSP_STATUS_CLEAR_B                      (DSP_STATUS_CLEAR_A + SIZE_U32)

#define DSP_SET_END_ADDR                        (DSP_STATUS_CLEAR_B + SIZE_U32)

//----------- END OF DSP Addresses-----------------


//#define    BUFF_ADR_SET_VAC                          1
//#define    BUFF_ADR_SET_VDC                          BUFF_ADR_SET_VAC + 4
//#define    BUFF_ADR_SET_FREQ                         BUFF_ADR_SET_VDC + 4
//#define    BUFF_ADR_VAC_SLEW                         BUFF_ADR_SET_FREQ + 4
//
//#define    BUFF_ADR_SET_I                            BUFF_ADR_VAC_SLEW + 4
//#define    BUFF_ADR_SET_RES                          BUFF_ADR_SET_I + 4
//#define    BUFF_ADR_SET_PKVA                         BUFF_ADR_SET_RES + 4
//#define    BUFF_ADR_SET_PF                           BUFF_ADR_SET_PKVA + 4
//#define    BUFF_ADR_SET_I_PF                         BUFF_ADR_SET_PF + 4
//
//
//#define    BUFF_ADR_SET_R_TOP                           BUFF_ADR_SET_I_PF + 4
//#define    BUFF_ADR_SET_L_TOP                           BUFF_ADR_SET_R_TOP + 4
//#define    BUFF_ADR_SET_C_TOP                           BUFF_ADR_SET_L_TOP + 4
//#define    BUFF_ADR_SET_RL_TOP                          BUFF_ADR_SET_C_TOP + 4
//#define    BUFF_ADR_SET_RC_TOP                          BUFF_ADR_SET_RL_TOP + 4
//#define    BUFF_ADR_SET_RS_TOP                          BUFF_ADR_SET_RC_TOP + 4
//#define    BUFF_ADR_SET_P_TOP                           BUFF_ADR_SET_RS_TOP + 4
//#define    BUFF_ADR_SET_QL_TOP                          BUFF_ADR_SET_P_TOP + 4
//#define    BUFF_ADR_SET_QC_TOP                          BUFF_ADR_SET_QL_TOP + 4
//#define    BUFF_ADR_SET_IL_TOP                          BUFF_ADR_SET_QC_TOP + 4
//#define    BUFF_ADR_SET_VC_TOP                          BUFF_ADR_SET_IL_TOP + 4
//
//
//#define    BUFF_ADR_VDC_SLEW                         BUFF_ADR_SET_VC_TOP + 4
//#define    BUFF_ADR_FREQ_SLEW                        BUFF_ADR_VDC_SLEW + 4
//
//#define    BUFF_ADR_ON_DEGREE                        BUFF_ADR_FREQ_SLEW + 4
//#define    BUFF_ADR_OFF_DEGREE                       BUFF_ADR_ON_DEGREE + 4
//#define    BUFF_ADR_COUPLE                           BUFF_ADR_OFF_DEGREE + 4
//
//
//#define    BUFF_ADR_OUT_STATE                        BUFF_ADR_COUPLE + 1
//#define    BUFF_ADR_HARM_TAB_OUT_STATE               BUFF_ADR_OUT_STATE + 1
//#define    BUFF_ADR_LOAD_SOURCE_MODE                 BUFF_ADR_HARM_TAB_OUT_STATE + 1
//#define    BUFF_ADR_LOAD__MODE                       BUFF_ADR_LOAD_SOURCE_MODE + 1
//#define    BUFF_ADR_SELECTED_TOPOLOGY                BUFF_ADR_LOAD__MODE + 1
//
//#define    BUFF_ADR_LIM_VAC                         (BUFF_ADR_SELECTED_TOPOLOGY + 1)
//#define    BUFF_ADR_LIM_VDC_P                       (BUFF_ADR_LIM_VAC + 4)
//#define    BUFF_ADR_LIM_VDC_M                       (BUFF_ADR_LIM_VDC_P + 4)
//#define    BUFF_ADR_LIM_FREQ                        (BUFF_ADR_LIM_VDC_M + 4)
//#define    BUFF_ADR_LIM_OPP                         (BUFF_ADR_LIM_FREQ + 4)
//#define    BUFF_ADR_LIM_OCP                         (BUFF_ADR_LIM_OPP + 4)
//#define    BUFF_ADR_LIM_OCP_DLY                     (BUFF_ADR_LIM_OCP + 4)
//
//#define    BUFF_ADR_HARM_WAVEFORM_NUM               (BUFF_ADR_LIM_OCP_DLY + 4)              //63
//
//#define    BUFF_ADR_HARM1_NO                        (BUFF_ADR_HARM_WAVEFORM_NUM + 1)        //64
//#define    BUFF_ADR_HARM1_AMP                       (BUFF_ADR_HARM1_NO + 4)                 //68
//#define    BUFF_ADR_HARM1_PHASE                     (BUFF_ADR_HARM1_AMP + 4)                //72
//
//#define    BUFF_ADR_HARM_BASE                       (BUFF_ADR_HARM1_NO)
//#define    BUFF_ADR_HARM_NUM(n)                     (BUFF_ADR_HARM_BASE + ((n-1) * 12))
//#define    BUFF_ADR_HARM_AMP(n)                     (BUFF_ADR_HARM_BASE + ((n-1) * 12) + 4)
//#define    BUFF_ADR_HARM_PHASE(n)                   (BUFF_ADR_HARM_BASE + ((n-1) * 12) + 8)
//
//#define    BUFF_ADR_HARM2_NO                        (BUFF_ADR_HARM1_PHASE + 4)              //76
//#define    BUFF_ADR_HARM2_AMP                       (BUFF_ADR_HARM2_NO + 4)                 //80
//#define    BUFF_ADR_HARM2_PHASE                     (BUFF_ADR_HARM2_AMP + 4)
//
//#define    BUFF_ADR_HARM3_NO                        (BUFF_ADR_HARM2_PHASE + 4)
//#define    BUFF_ADR_HARM3_AMP                       (BUFF_ADR_HARM3_NO + 4)
//#define    BUFF_ADR_HARM3_PHASE                     (BUFF_ADR_HARM3_AMP + 4)
//
//#define    BUFF_ADR_HARM4_NO                        (BUFF_ADR_HARM3_PHASE + 4)
//#define    BUFF_ADR_HARM4_AMP                       (BUFF_ADR_HARM4_NO + 4)
//#define    BUFF_ADR_HARM4_PHASE                     (BUFF_ADR_HARM4_AMP + 4)
//
//#define    BUFF_ADR_HARM5_NO                        (BUFF_ADR_HARM4_PHASE + 4)
//#define    BUFF_ADR_HARM5_AMP                       (BUFF_ADR_HARM5_NO + 4)
//#define    BUFF_ADR_HARM5_PHASE                     (BUFF_ADR_HARM5_AMP + 4)
//
//#define    BUFF_ADR_HARM6_NO                        (BUFF_ADR_HARM5_PHASE + 4)
//#define    BUFF_ADR_HARM6_AMP                       (BUFF_ADR_HARM6_NO + 4)
//#define    BUFF_ADR_HARM6_PHASE                     (BUFF_ADR_HARM6_AMP + 4)
//
//#define    BUFF_ADR_HARM7_NO                        (BUFF_ADR_HARM6_PHASE + 4)
//#define    BUFF_ADR_HARM7_AMP                       (BUFF_ADR_HARM7_NO + 4)
//#define    BUFF_ADR_HARM7_PHASE                     (BUFF_ADR_HARM7_AMP + 4)
//
//#define    BUFF_ADR_HARM8_NO                        (BUFF_ADR_HARM7_PHASE + 4)
//#define    BUFF_ADR_HARM8_AMP                       (BUFF_ADR_HARM8_NO + 4)
//#define    BUFF_ADR_HARM8_PHASE                     (BUFF_ADR_HARM8_AMP + 4)
//
//#define    BUFF_ADR_HARM9_NO                        (BUFF_ADR_HARM8_PHASE + 4)
//#define    BUFF_ADR_HARM9_AMP                       (BUFF_ADR_HARM9_NO + 4)
//#define    BUFF_ADR_HARM9_PHASE                     (BUFF_ADR_HARM9_AMP + 4)
//
//#define    BUFF_ADR_HARM10_NO                       (BUFF_ADR_HARM9_PHASE + 4)
//#define    BUFF_ADR_HARM10_AMP                      (BUFF_ADR_HARM10_NO + 4)
//#define    BUFF_ADR_HARM10_PHASE                    (BUFF_ADR_HARM10_AMP + 4)
//
//#define    BUFF_ADR_HARM11_NO                       (BUFF_ADR_HARM10_PHASE + 4)
//#define    BUFF_ADR_HARM11_AMP                      (BUFF_ADR_HARM11_NO + 4)
//#define    BUFF_ADR_HARM11_PHASE                    (BUFF_ADR_HARM11_AMP + 4)
//
//#define    BUFF_ADR_HARM12_NO                       (BUFF_ADR_HARM11_PHASE + 4)
//#define    BUFF_ADR_HARM12_AMP                      (BUFF_ADR_HARM12_NO + 4)
//#define    BUFF_ADR_HARM12_PHASE                    (BUFF_ADR_HARM12_AMP + 4)
//
//#define    BUFF_ADR_HARM13_NO                       (BUFF_ADR_HARM12_PHASE + 4)
//#define    BUFF_ADR_HARM13_AMP                      (BUFF_ADR_HARM13_NO + 4)
//#define    BUFF_ADR_HARM13_PHASE                    (BUFF_ADR_HARM13_AMP + 4)
//
//#define    BUFF_ADR_HARM14_NO                       (BUFF_ADR_HARM13_PHASE + 4)
//#define    BUFF_ADR_HARM14_AMP                      (BUFF_ADR_HARM14_NO + 4)
//#define    BUFF_ADR_HARM14_PHASE                    (BUFF_ADR_HARM14_AMP + 4)
//
//#define    BUFF_ADR_HARM15_NO                       (BUFF_ADR_HARM14_PHASE + 4)
//#define    BUFF_ADR_HARM15_AMP                      (BUFF_ADR_HARM15_NO + 4)
//#define    BUFF_ADR_HARM15_PHASE                    (BUFF_ADR_HARM15_AMP + 4)
//
//#define    BUFF_ADR_HARM16_NO                       (BUFF_ADR_HARM15_PHASE + 4)
//#define    BUFF_ADR_HARM16_AMP                      (BUFF_ADR_HARM16_NO + 4)
//#define    BUFF_ADR_HARM16_PHASE                    (BUFF_ADR_HARM16_AMP + 4)
//
//#define    BUFF_ADR_HARM17_NO                       (BUFF_ADR_HARM16_PHASE + 4)
//#define    BUFF_ADR_HARM17_AMP                      (BUFF_ADR_HARM17_NO + 4)
//#define    BUFF_ADR_HARM17_PHASE                    (BUFF_ADR_HARM17_AMP + 4)
//
//#define    BUFF_ADR_HARM18_NO                       (BUFF_ADR_HARM17_PHASE + 4)
//#define    BUFF_ADR_HARM18_AMP                      (BUFF_ADR_HARM18_NO + 4)
//#define    BUFF_ADR_HARM18_PHASE                    (BUFF_ADR_HARM18_AMP + 4)
//
//#define    BUFF_ADR_HARM19_NO                       (BUFF_ADR_HARM18_PHASE + 4)
//#define    BUFF_ADR_HARM19_AMP                      (BUFF_ADR_HARM19_NO + 4)
//#define    BUFF_ADR_HARM19_PHASE                    (BUFF_ADR_HARM19_AMP + 4)
//
//#define    BUFF_ADR_HARM20_NO                       (BUFF_ADR_HARM19_PHASE + 4)
//#define    BUFF_ADR_HARM20_AMP                      (BUFF_ADR_HARM20_NO + 4)
//#define    BUFF_ADR_HARM20_PHASE                    (BUFF_ADR_HARM20_AMP + 4)
//
//#define    BUFF_ADR_HARM21_NO                       (BUFF_ADR_HARM20_PHASE + 4)
//#define    BUFF_ADR_HARM21_AMP                      (BUFF_ADR_HARM21_NO + 4)
//#define    BUFF_ADR_HARM21_PHASE                    (BUFF_ADR_HARM21_AMP + 4)
//
//#define    BUFF_ADR_HARM22_NO                       (BUFF_ADR_HARM21_PHASE + 4)
//#define    BUFF_ADR_HARM22_AMP                      (BUFF_ADR_HARM22_NO + 4)
//#define    BUFF_ADR_HARM22_PHASE                    (BUFF_ADR_HARM22_AMP + 4)
//
//#define    BUFF_ADR_HARM23_NO                       (BUFF_ADR_HARM22_PHASE + 4)
//#define    BUFF_ADR_HARM23_AMP                      (BUFF_ADR_HARM23_NO + 4)
//#define    BUFF_ADR_HARM23_PHASE                    (BUFF_ADR_HARM23_AMP + 4)
//
//#define    BUFF_ADR_HARM24_NO                       (BUFF_ADR_HARM23_PHASE + 4)
//#define    BUFF_ADR_HARM24_AMP                      (BUFF_ADR_HARM24_NO + 4)
//#define    BUFF_ADR_HARM24_PHASE                    (BUFF_ADR_HARM24_AMP + 4)
//
//#define    BUFF_ADR_HARM25_NO                       (BUFF_ADR_HARM24_PHASE + 4)
//#define    BUFF_ADR_HARM25_AMP                      (BUFF_ADR_HARM25_NO + 4)
//#define    BUFF_ADR_HARM25_PHASE                    (BUFF_ADR_HARM25_AMP + 4)
//
//#define    BUFF_ADR_HARM26_NO                       (BUFF_ADR_HARM25_PHASE + 4)
//#define    BUFF_ADR_HARM26_AMP                      (BUFF_ADR_HARM26_NO + 4)
//#define    BUFF_ADR_HARM26_PHASE                    (BUFF_ADR_HARM26_AMP + 4)
//
//#define    BUFF_ADR_HARM27_NO                       (BUFF_ADR_HARM26_PHASE + 4)
//#define    BUFF_ADR_HARM27_AMP                      (BUFF_ADR_HARM27_NO + 4)
//#define    BUFF_ADR_HARM27_PHASE                    (BUFF_ADR_HARM27_AMP + 4)
//
//#define    BUFF_ADR_HARM28_NO                       (BUFF_ADR_HARM27_PHASE + 4)
//#define    BUFF_ADR_HARM28_AMP                      (BUFF_ADR_HARM28_NO + 4)
//#define    BUFF_ADR_HARM28_PHASE                    (BUFF_ADR_HARM28_AMP + 4)
//
//#define    BUFF_ADR_HARM29_NO                       (BUFF_ADR_HARM28_PHASE + 4)
//#define    BUFF_ADR_HARM29_AMP                      (BUFF_ADR_HARM29_NO + 4)
//#define    BUFF_ADR_HARM29_PHASE                    (BUFF_ADR_HARM29_AMP + 4)
//
//#define    BUFF_ADR_HARM30_NO                       (BUFF_ADR_HARM29_PHASE + 4)
//#define    BUFF_ADR_HARM30_AMP                      (BUFF_ADR_HARM30_NO + 4)
//#define    BUFF_ADR_HARM30_PHASE                    (BUFF_ADR_HARM30_AMP + 4)
//
//#define    BUFF_ADR_HARM31_NO                       (BUFF_ADR_HARM30_PHASE + 4)
//#define    BUFF_ADR_HARM31_AMP                      (BUFF_ADR_HARM31_NO + 4)
//#define    BUFF_ADR_HARM31_PHASE                    (BUFF_ADR_HARM31_AMP + 4)
//
//#define    BUFF_ADR_HARM32_NO                       (BUFF_ADR_HARM31_PHASE + 4)
//#define    BUFF_ADR_HARM32_AMP                      (BUFF_ADR_HARM32_NO + 4)
//#define    BUFF_ADR_HARM32_PHASE                    (BUFF_ADR_HARM32_AMP + 4)
//
//#define    BUFF_ADR_HARM33_NO                       (BUFF_ADR_HARM32_PHASE + 4)
//#define    BUFF_ADR_HARM33_AMP                      (BUFF_ADR_HARM33_NO + 4)
//#define    BUFF_ADR_HARM33_PHASE                    (BUFF_ADR_HARM33_AMP + 4)
//
//#define    BUFF_ADR_HARM34_NO                       (BUFF_ADR_HARM33_PHASE + 4)
//#define    BUFF_ADR_HARM34_AMP                      (BUFF_ADR_HARM34_NO + 4)
//#define    BUFF_ADR_HARM34_PHASE                    (BUFF_ADR_HARM34_AMP + 4)
//
//#define    BUFF_ADR_HARM35_NO                       (BUFF_ADR_HARM34_PHASE + 4)
//#define    BUFF_ADR_HARM35_AMP                      (BUFF_ADR_HARM35_NO + 4)
//#define    BUFF_ADR_HARM35_PHASE                    (BUFF_ADR_HARM35_AMP + 4)
//
//#define    BUFF_ADR_HARM36_NO                       (BUFF_ADR_HARM35_PHASE + 4)
//#define    BUFF_ADR_HARM36_AMP                      (BUFF_ADR_HARM36_NO + 4)
//#define    BUFF_ADR_HARM36_PHASE                    (BUFF_ADR_HARM36_AMP + 4)
//
//#define    BUFF_ADR_HARM37_NO                       (BUFF_ADR_HARM36_PHASE + 4)
//#define    BUFF_ADR_HARM37_AMP                      (BUFF_ADR_HARM37_NO + 4)
//#define    BUFF_ADR_HARM37_PHASE                    (BUFF_ADR_HARM37_AMP + 4)
//
//#define    BUFF_ADR_HARM38_NO                       (BUFF_ADR_HARM37_PHASE + 4)
//#define    BUFF_ADR_HARM38_AMP                      (BUFF_ADR_HARM38_NO + 4)
//#define    BUFF_ADR_HARM38_PHASE                    (BUFF_ADR_HARM38_AMP + 4)
//
//#define    BUFF_ADR_HARM39_NO                       (BUFF_ADR_HARM38_PHASE + 4)
//#define    BUFF_ADR_HARM39_AMP                      (BUFF_ADR_HARM39_NO + 4)
//#define    BUFF_ADR_HARM39_PHASE                    (BUFF_ADR_HARM39_AMP + 4)
//
//#define    BUFF_ADR_HARM40_NO                       (BUFF_ADR_HARM39_PHASE + 4)
//#define    BUFF_ADR_HARM40_AMP                      (BUFF_ADR_HARM40_NO + 4)
//#define    BUFF_ADR_HARM40_PHASE                    (BUFF_ADR_HARM40_AMP + 4)
//
//#define    BUFF_ADR_HARM41_NO                       (BUFF_ADR_HARM40_PHASE + 4)
//#define    BUFF_ADR_HARM41_AMP                      (BUFF_ADR_HARM41_NO + 4)
//#define    BUFF_ADR_HARM41_PHASE                    (BUFF_ADR_HARM41_AMP + 4)
//
//#define    BUFF_ADR_HARM42_NO                       (BUFF_ADR_HARM41_PHASE + 4)
//#define    BUFF_ADR_HARM42_AMP                      (BUFF_ADR_HARM42_NO + 4)
//#define    BUFF_ADR_HARM42_PHASE                    (BUFF_ADR_HARM42_AMP + 4)
//
//#define    BUFF_ADR_HARM43_NO                       (BUFF_ADR_HARM42_PHASE + 4)
//#define    BUFF_ADR_HARM43_AMP                      (BUFF_ADR_HARM43_NO + 4)
//#define    BUFF_ADR_HARM43_PHASE                    (BUFF_ADR_HARM43_AMP + 4)
//
//#define    BUFF_ADR_HARM44_NO                       (BUFF_ADR_HARM43_PHASE + 4)
//#define    BUFF_ADR_HARM44_AMP                      (BUFF_ADR_HARM44_NO + 4)
//#define    BUFF_ADR_HARM44_PHASE                    (BUFF_ADR_HARM44_AMP + 4)
//
//#define    BUFF_ADR_HARM45_NO                       (BUFF_ADR_HARM44_PHASE + 4)
//#define    BUFF_ADR_HARM45_AMP                      (BUFF_ADR_HARM45_NO + 4)
//#define    BUFF_ADR_HARM45_PHASE                    (BUFF_ADR_HARM45_AMP + 4)
//
//#define    BUFF_ADR_HARM46_NO                       (BUFF_ADR_HARM45_PHASE + 4)
//#define    BUFF_ADR_HARM46_AMP                      (BUFF_ADR_HARM46_NO + 4)
//#define    BUFF_ADR_HARM46_PHASE                    (BUFF_ADR_HARM46_AMP + 4)
//
//#define    BUFF_ADR_HARM47_NO                       (BUFF_ADR_HARM46_PHASE + 4)
//#define    BUFF_ADR_HARM47_AMP                      (BUFF_ADR_HARM47_NO + 4)
//#define    BUFF_ADR_HARM47_PHASE                    (BUFF_ADR_HARM47_AMP + 4)
//
//#define    BUFF_ADR_HARM48_NO                       (BUFF_ADR_HARM47_PHASE + 4)
//#define    BUFF_ADR_HARM48_AMP                      (BUFF_ADR_HARM48_NO + 4)
//#define    BUFF_ADR_HARM48_PHASE                    (BUFF_ADR_HARM48_AMP + 4)
//
//#define    BUFF_ADR_HARM49_NO                       (BUFF_ADR_HARM48_PHASE + 4)
//#define    BUFF_ADR_HARM49_AMP                      (BUFF_ADR_HARM49_NO + 4)
//#define    BUFF_ADR_HARM49_PHASE                    (BUFF_ADR_HARM49_AMP + 4)
//
//#define    BUFF_ADR_HARM50_NO                       (BUFF_ADR_HARM49_PHASE + 4)
//#define    BUFF_ADR_HARM50_AMP                      (BUFF_ADR_HARM50_NO + 4)
//#define    BUFF_ADR_HARM50_PHASE                    (BUFF_ADR_HARM50_AMP + 4)
//
//#define    BUFF_SET_HARMNO                          (BUFF_ADR_HARM50_PHASE + 4)
//#define    BUFF_SET_HARMAMP                         (BUFF_SET_HARMNO + 4)
//#define    BUFF_SET_HARMPHASE                       (BUFF_SET_HARMAMP + 4)
//#define    BUFF_SET_HARMSRNUM                       (BUFF_SET_HARMPHASE + 4)
//
//#define    BUFF_ADR_MEAS_VOLT                       (BUFF_SET_HARMSRNUM + 4)
//#define    BUFF_ADR_MEAS_VDC                        (BUFF_ADR_MEAS_VOLT + 4)
//#define    BUFF_ADR_MEAS_VAC                        (BUFF_ADR_MEAS_VDC + 4)
//#define    BUFF_ADR_MEAS_IDC                        (BUFF_ADR_MEAS_VAC + 4)
//#define    BUFF_ADR_MEAS_I                          (BUFF_ADR_MEAS_IDC + 4)
//#define    BUFF_ADR_MEAS_IAC                        (BUFF_ADR_MEAS_I + 4)
//#define    BUFF_ADR_MEAS_FREQ                       (BUFF_ADR_MEAS_IAC + 4)
//
//#define    BUFF_ADR_MEAS_VPK_P                      (BUFF_ADR_MEAS_FREQ + 4)
//#define    BUFF_ADR_MEAS_IPK_P                      (BUFF_ADR_MEAS_VPK_P + 4)
//
//#define    BUFF_ADR_MEAS_VPK_N                      (BUFF_ADR_MEAS_IPK_P + 4)
//#define    BUFF_ADR_MEAS_IPK_N                      (BUFF_ADR_MEAS_VPK_N + 4)
//
//#define    BUFF_ADR_MEAS_V_CF                       (BUFF_ADR_MEAS_IPK_N + 4)
//#define    BUFF_ADR_MEAS_I_CF                       (BUFF_ADR_MEAS_V_CF + 4)
//
//#define    BUFF_ADR_MEAS_IS                         (BUFF_ADR_MEAS_I_CF + 4)
//
//#define    BUFF_ADR_MEAS_POWER                      (BUFF_ADR_MEAS_IS + 4)
//#define    BUFF_ADR_MEAS_VAR                        (BUFF_ADR_MEAS_POWER + 4)
//#define    BUFF_ADR_MEAS_VA                         (BUFF_ADR_MEAS_VAR + 4)
//#define    BUFF_ADR_MEAS_PF                         (BUFF_ADR_MEAS_VA + 4)
//
//#define    BUFF_ADR_MEAS_V_IN                       (BUFF_ADR_MEAS_PF + 4)
//#define    BUFF_ADR_MEAS_I_IN                       (BUFF_ADR_MEAS_V_IN + 4)
//#define    BUFF_ADR_MEAS_VDC_IN                     (BUFF_ADR_MEAS_I_IN + 4)
//#define    BUFF_ADR_MEAS_FREQ_IN                    (BUFF_ADR_MEAS_VDC_IN + 4)
//#define    BUFF_ADR_MEAS_POWER_IN                   (BUFF_ADR_MEAS_FREQ_IN + 4)
//#define    BUFF_ADR_MEAS_VAR_IN                     (BUFF_ADR_MEAS_POWER_IN + 4)
//#define    BUFF_ADR_MEAS_VA_IN                      (BUFF_ADR_MEAS_VAR_IN + 4)
//#define    BUFF_ADR_MEAS_PF_IN                      (BUFF_ADR_MEAS_VA_IN + 4)
//#define    BUFF_ADR_PFC_STATE                       (BUFF_ADR_MEAS_PF_IN + 4)
//
//#define    BUFF_END_ADDR                            (BUFF_ADR_PFC_STATE + 4)


#elif CONVERTER_TYPE == THREE_PHASE
//***************************Source Subsystem************************************//
#define BUFF_ADR_SRC_VA                             1
#define BUFF_ADR_SRC_VB                             BUFF_ADR_SRC_VA + 4
#define BUFF_ADR_SRC_VC                             BUFF_ADR_SRC_VB + 4
#define BUFF_ADR_SRC_VAC                            BUFF_ADR_SRC_VC + 4

#define BUFF_ADR_SRC_VA_SLW                         BUFF_ADR_SRC_VAC + 4
#define BUFF_ADR_SRC_VB_SLW                         BUFF_ADR_SRC_VA_SLW + 4
#define BUFF_ADR_SRC_VC_SLW                         BUFF_ADR_SRC_VB_SLW + 4
#define BUFF_ADR_SRC_VAC_SLW                        BUFF_ADR_SRC_VC_SLW + 4

#define BUFF_ADR_SRC_IA                             BUFF_ADR_SRC_VAC_SLW + 4
#define BUFF_ADR_SRC_IB                             BUFF_ADR_SRC_IA + 4
#define BUFF_ADR_SRC_IC                             BUFF_ADR_SRC_IB + 4
#define BUFF_ADR_SRC_IAC                            BUFF_ADR_SRC_IC + 4

#define BUFF_ADR_SRC_IA_SLW                         BUFF_ADR_SRC_IAC + 4
#define BUFF_ADR_SRC_IB_SLW                         BUFF_ADR_SRC_IA_SLW + 4
#define BUFF_ADR_SRC_IC_SLW                         BUFF_ADR_SRC_IB_SLW + 4
#define BUFF_ADR_SRC_IAC_SLW                        BUFF_ADR_SRC_IC_SLW + 4

#define BUFF_ADR_SRC_FREQ_A                         BUFF_ADR_SRC_IAC_SLW + 4
#define BUFF_ADR_SRC_FREQ_B                         BUFF_ADR_SRC_FREQ_A + 4
#define BUFF_ADR_SRC_FREQ_C                         BUFF_ADR_SRC_FREQ_B + 4
#define BUFF_ADR_SRC_FREQ                           BUFF_ADR_SRC_FREQ_C + 4

#define BUFF_ADR_SRC_FREQ_SLW                       BUFF_ADR_SRC_FREQ + 4
#define BUFF_ADR_SRC_FREQ_A_SLW                     BUFF_ADR_SRC_FREQ_SLW + 4
#define BUFF_ADR_SRC_FREQ_B_SLW                     BUFF_ADR_SRC_FREQ_A_SLW + 4
#define BUFF_ADR_SRC_FREQ_C_SLW                     BUFF_ADR_SRC_FREQ_B_SLW + 4

#define BUFF_ADR_SRC_ANGLE_AB                       BUFF_ADR_SRC_FREQ_C_SLW + 4
#define BUFF_ADR_SRC_ANGLE_AC                       BUFF_ADR_SRC_ANGLE_AB + 4
#define BUFF_ADR_SRC_ANGLE_BC                       BUFF_ADR_SRC_ANGLE_AC + 4

#define BUFF_ADR_SRC_SEQ_ABC                        BUFF_ADR_SRC_ANGLE_BC + 4
#define BUFF_ADR_SRC_SEQ_ACB                        BUFF_ADR_SRC_SEQ_ABC + 4

#define BUFF_ADR_SRC_VA_DC                          BUFF_ADR_SRC_SEQ_ACB + 4
#define BUFF_ADR_SRC_VB_DC                          BUFF_ADR_SRC_VA_DC + 4
#define BUFF_ADR_SRC_VC_DC                          BUFF_ADR_SRC_VB_DC + 4
#define BUFF_ADR_SRC_V_DC                           BUFF_ADR_SRC_VC_DC + 4

#define BUFF_ADR_SRC_VA_DC_SLW                      BUFF_ADR_SRC_V_DC + 4
#define BUFF_ADR_SRC_VB_DC_SLW                      BUFF_ADR_SRC_VA_DC_SLW + 4
#define BUFF_ADR_SRC_VC_DC_SLW                      BUFF_ADR_SRC_VB_DC_SLW + 4
#define BUFF_ADR_SRC_V_DC_SLW                       BUFF_ADR_SRC_VC_DC_SLW + 4

#define BUFF_ADR_SRC_IA_DC                          BUFF_ADR_SRC_V_DC_SLW + 4
#define BUFF_ADR_SRC_IB_DC                          BUFF_ADR_SRC_IA_DC + 4
#define BUFF_ADR_SRC_IC_DC                          BUFF_ADR_SRC_IB_DC + 4
#define BUFF_ADR_SRC_I_DC                           BUFF_ADR_SRC_IC_DC + 4

#define BUFF_ADR_SRC_IA_DC_SLW                      BUFF_ADR_SRC_I_DC + 4
#define BUFF_ADR_SRC_IB_DC_SLW                      BUFF_ADR_SRC_IA_DC_SLW + 4
#define BUFF_ADR_SRC_IC_DC_SLW                      BUFF_ADR_SRC_IB_DC_SLW + 4
#define BUFF_ADR_SRC_I_DC_SLW                       BUFF_ADR_SRC_IC_DC_SLW + 4

#define BUFF_ADR_SRC_ON_DEG_A                       BUFF_ADR_SRC_I_DC_SLW + 4
#define BUFF_ADR_SRC_ON_DEG_B                       BUFF_ADR_SRC_ON_DEG_A + 4
#define BUFF_ADR_SRC_ON_DEG_C                       BUFF_ADR_SRC_ON_DEG_B + 4
#define BUFF_ADR_SRC_ON_DEG_ABC                     BUFF_ADR_SRC_ON_DEG_C + 4

#define BUFF_ADR_SRC_OFF_DEG_A                      BUFF_ADR_SRC_ON_DEG_ABC + 4
#define BUFF_ADR_SRC_OFF_DEG_B                      BUFF_ADR_SRC_OFF_DEG_A + 4
#define BUFF_ADR_SRC_OFF_DEG_C                      BUFF_ADR_SRC_OFF_DEG_B + 4
#define BUFF_ADR_SRC_OFF_DEG_ABC                    BUFF_ADR_SRC_OFF_DEG_C + 4

#define BUFF_ADR_START_PWR_STAGE                    BUFF_ADR_SRC_OFF_DEG_ABC + 4
#define BUFF_ADR_RLY_CTRL                           BUFF_ADR_START_PWR_STAGE + 1

#define BUFF_OUTPUT_MODE                            BUFF_ADR_RLY_CTRL   + 4

//***************************Limit Subsystem************************************//
#define BUFF_ADR_LIM_VA_MAX                         BUFF_OUTPUT_MODE + 1
#define BUFF_ADR_LIM_VA_MIN                         BUFF_ADR_LIM_VA_MAX + 4
#define BUFF_ADR_LIM_VB_MAX                         BUFF_ADR_LIM_VA_MIN + 4
#define BUFF_ADR_LIM_VB_MIN                         BUFF_ADR_LIM_VB_MAX + 4
#define BUFF_ADR_LIM_VC_MAX                         BUFF_ADR_LIM_VB_MIN + 4
#define BUFF_ADR_LIM_VC_MIN                         BUFF_ADR_LIM_VC_MAX + 4
#define BUFF_ADR_LIM_V_MAX                          BUFF_ADR_LIM_VC_MIN + 4
#define BUFF_ADR_LIM_V_MIN                          BUFF_ADR_LIM_V_MAX + 4

#define BUFF_ADR_LIM_IA_MAX                         BUFF_ADR_LIM_V_MIN + 4
#define BUFF_ADR_LIM_IA_MIN                         BUFF_ADR_LIM_IA_MAX + 4
#define BUFF_ADR_LIM_IB_MAX                         BUFF_ADR_LIM_IA_MIN + 4
#define BUFF_ADR_LIM_IB_MIN                         BUFF_ADR_LIM_IB_MAX + 4
#define BUFF_ADR_LIM_IC_MAX                         BUFF_ADR_LIM_IB_MIN + 4
#define BUFF_ADR_LIM_IC_MIN                         BUFF_ADR_LIM_IC_MAX + 4
#define BUFF_ADR_LIM_I_MAX                          BUFF_ADR_LIM_IC_MIN + 4
#define BUFF_ADR_LIM_I_MIN                          BUFF_ADR_LIM_I_MAX + 4

#define BUFF_ADR_LIM_IA_MAX_DLY                     BUFF_ADR_LIM_I_MIN + 4
#define BUFF_ADR_LIM_IA_MIN_DLY                     BUFF_ADR_LIM_IA_MAX_DLY + 4
#define BUFF_ADR_LIM_IB_MAX_DLY                     BUFF_ADR_LIM_IA_MIN_DLY + 4
#define BUFF_ADR_LIM_IB_MIN_DLY                     BUFF_ADR_LIM_IB_MAX_DLY + 4
#define BUFF_ADR_LIM_IC_MAX_DLY                     BUFF_ADR_LIM_IB_MIN_DLY + 4
#define BUFF_ADR_LIM_IC_MIN_DLY                     BUFF_ADR_LIM_IC_MAX_DLY + 4
#define BUFF_ADR_LIM_I_MAX_DLY                      BUFF_ADR_LIM_IC_MIN_DLY + 4
#define BUFF_ADR_LIM_I_MIN_DLY                      BUFF_ADR_LIM_I_MAX_DLY + 4

#define BUFF_ADR_LIM_VA_DC_MAX                      BUFF_ADR_LIM_I_MIN_DLY + 4
#define BUFF_ADR_LIM_VA_DC_MIN                      BUFF_ADR_LIM_VA_DC_MAX + 4
#define BUFF_ADR_LIM_VB_DC_MAX                      BUFF_ADR_LIM_VA_DC_MIN + 4
#define BUFF_ADR_LIM_VB_DC_MIN                      BUFF_ADR_LIM_VB_DC_MAX + 4
#define BUFF_ADR_LIM_VC_DC_MAX                      BUFF_ADR_LIM_VB_DC_MIN + 4
#define BUFF_ADR_LIM_VC_DC_MIN                      BUFF_ADR_LIM_VC_DC_MAX + 4
#define BUFF_ADR_LIM_V_DC_MAX                       BUFF_ADR_LIM_VC_DC_MIN + 4
#define BUFF_ADR_LIM_V_DC_MIN                       BUFF_ADR_LIM_V_DC_MAX + 4

#define BUFF_ADR_LIM_IA_DC_MAX                      BUFF_ADR_LIM_V_DC_MIN + 4
#define BUFF_ADR_LIM_IA_DC_MIN                      BUFF_ADR_LIM_IA_DC_MAX + 4
#define BUFF_ADR_LIM_IB_DC_MAX                      BUFF_ADR_LIM_IA_DC_MIN + 4
#define BUFF_ADR_LIM_IB_DC_MIN                      BUFF_ADR_LIM_IB_DC_MAX + 4
#define BUFF_ADR_LIM_IC_DC_MAX                      BUFF_ADR_LIM_IB_DC_MIN + 4
#define BUFF_ADR_LIM_IC_DC_MIN                      BUFF_ADR_LIM_IC_DC_MAX + 4
#define BUFF_ADR_LIM_I_DC_MAX                       BUFF_ADR_LIM_IC_DC_MIN + 4
#define BUFF_ADR_LIM_I_DC_MIN                       BUFF_ADR_LIM_I_DC_MAX + 4

#define BUFF_ADR_LIM_FREQ_A_MAX                     BUFF_ADR_LIM_I_DC_MIN + 4
#define BUFF_ADR_LIM_FREQ_A_MIN                     BUFF_ADR_LIM_FREQ_A_MAX + 4
#define BUFF_ADR_LIM_FREQ_B_MAX                     BUFF_ADR_LIM_FREQ_A_MIN + 4
#define BUFF_ADR_LIM_FREQ_B_MIN                     BUFF_ADR_LIM_FREQ_B_MAX + 4
#define BUFF_ADR_LIM_FREQ_C_MAX                     BUFF_ADR_LIM_FREQ_B_MIN + 4
#define BUFF_ADR_LIM_FREQ_C_MIN                     BUFF_ADR_LIM_FREQ_C_MAX + 4
#define BUFF_ADR_LIM_FREQ_MAX                       BUFF_ADR_LIM_FREQ_C_MIN + 4
#define BUFF_ADR_LIM_FREQ_MIN                       BUFF_ADR_LIM_FREQ_MAX + 4

#define BUFF_ADR_LIM_PWR_A_MAX                      BUFF_ADR_LIM_FREQ_MIN + 4
#define BUFF_ADR_LIM_PWR_A_MIN                      BUFF_ADR_LIM_PWR_A_MAX + 4
#define BUFF_ADR_LIM_PWR_B_MAX                      BUFF_ADR_LIM_PWR_A_MIN + 4
#define BUFF_ADR_LIM_PWR_B_MIN                      BUFF_ADR_LIM_PWR_B_MAX + 4
#define BUFF_ADR_LIM_PWR_C_MAX                      BUFF_ADR_LIM_PWR_B_MIN + 4
#define BUFF_ADR_LIM_PWR_C_MIN                      BUFF_ADR_LIM_PWR_C_MAX + 4
#define BUFF_ADR_LIM_PWR_TOT_MAX                    BUFF_ADR_LIM_PWR_C_MIN + 4
#define BUFF_ADR_LIM_PWR_TOT_MIN                    BUFF_ADR_LIM_PWR_TOT_MAX + 4

//***************************Measure Subsystem************************************//
#define BUFF_ADR_MEAS_VA_RMS                        BUFF_ADR_LIM_PWR_TOT_MIN + 4
#define BUFF_ADR_MEAS_VB_RMS                        BUFF_ADR_MEAS_VA_RMS + 4
#define BUFF_ADR_MEAS_VC_RMS                        BUFF_ADR_MEAS_VB_RMS + 4
#define BUFF_ADR_MEAS_VAB_RMS                       BUFF_ADR_MEAS_VC_RMS + 4
#define BUFF_ADR_MEAS_VBC_RMS                       BUFF_ADR_MEAS_VAB_RMS + 4
#define BUFF_ADR_MEAS_VCA_RMS                       BUFF_ADR_MEAS_VBC_RMS + 4

#define BUFF_ADR_MEAS_IA_RMS                        BUFF_ADR_MEAS_VCA_RMS + 4
#define BUFF_ADR_MEAS_IB_RMS                        BUFF_ADR_MEAS_IA_RMS + 4
#define BUFF_ADR_MEAS_IC_RMS                        BUFF_ADR_MEAS_IB_RMS + 4
#define BUFF_ADR_MEAS_IAB_RMS                       BUFF_ADR_MEAS_IC_RMS + 4
#define BUFF_ADR_MEAS_IBC_RMS                       BUFF_ADR_MEAS_IAB_RMS + 4
#define BUFF_ADR_MEAS_ICA_RMS                       BUFF_ADR_MEAS_IBC_RMS + 4

#define BUFF_ADR_MEAS_VA_PEAK                       BUFF_ADR_MEAS_ICA_RMS + 4
#define BUFF_ADR_MEAS_VB_PEAK                       BUFF_ADR_MEAS_VA_PEAK + 4
#define BUFF_ADR_MEAS_VC_PEAK                       BUFF_ADR_MEAS_VB_PEAK + 4

#define BUFF_ADR_MEAS_IA_PEAK                       BUFF_ADR_MEAS_VC_PEAK + 4
#define BUFF_ADR_MEAS_IB_PEAK                       BUFF_ADR_MEAS_IA_PEAK + 4
#define BUFF_ADR_MEAS_IC_PEAK                       BUFF_ADR_MEAS_IB_PEAK + 4

#define BUFF_ADR_MEAS_VA_DC                         BUFF_ADR_MEAS_IC_PEAK + 4
#define BUFF_ADR_MEAS_VB_DC                         BUFF_ADR_MEAS_VA_DC + 4
#define BUFF_ADR_MEAS_VC_DC                         BUFF_ADR_MEAS_VB_DC + 4

#define BUFF_ADR_MEAS_IA_DC                         BUFF_ADR_MEAS_VC_DC + 4
#define BUFF_ADR_MEAS_IB_DC                         BUFF_ADR_MEAS_IA_DC + 4
#define BUFF_ADR_MEAS_IC_DC                         BUFF_ADR_MEAS_IB_DC + 4

#define BUFF_ADR_MEAS_FREQ_A                        BUFF_ADR_MEAS_IC_DC + 4
#define BUFF_ADR_MEAS_FREQ_B                        BUFF_ADR_MEAS_FREQ_A + 4
#define BUFF_ADR_MEAS_FREQ_C                        BUFF_ADR_MEAS_FREQ_B + 4

#define BUFF_ADR_MEAS_PWR_A_W                       BUFF_ADR_MEAS_FREQ_C + 4
#define BUFF_ADR_MEAS_PWR_B_W                       BUFF_ADR_MEAS_PWR_A_W + 4
#define BUFF_ADR_MEAS_PWR_C_W                       BUFF_ADR_MEAS_PWR_B_W + 4
#define BUFF_ADR_MEAS_PWR_TOT_W                     BUFF_ADR_MEAS_PWR_C_W + 4

#define BUFF_ADR_MEAS_PWR_A_VAR                     BUFF_ADR_MEAS_PWR_TOT_W + 4
#define BUFF_ADR_MEAS_PWR_B_VAR                     BUFF_ADR_MEAS_PWR_A_VAR + 4
#define BUFF_ADR_MEAS_PWR_C_VAR                     BUFF_ADR_MEAS_PWR_B_VAR + 4
#define BUFF_ADR_MEAS_PWR_TOT_VAR                   BUFF_ADR_MEAS_PWR_C_VAR + 4

#define BUFF_ADR_MEAS_PWR_A_VA                      BUFF_ADR_MEAS_PWR_TOT_VAR + 4
#define BUFF_ADR_MEAS_PWR_B_VA                      BUFF_ADR_MEAS_PWR_A_VA + 4
#define BUFF_ADR_MEAS_PWR_C_VA                      BUFF_ADR_MEAS_PWR_B_VA + 4
#define BUFF_ADR_MEAS_PWR_TOT_VA                    BUFF_ADR_MEAS_PWR_C_VA + 4

#define BUFF_ADR_MEAS_PF_A                          BUFF_ADR_MEAS_PWR_TOT_VA + 4
#define BUFF_ADR_MEAS_PF_B                          BUFF_ADR_MEAS_PF_A + 4
#define BUFF_ADR_MEAS_PF_C                          BUFF_ADR_MEAS_PF_B + 4

//***************************Measure Subsystem INPUT ****************************//
#define BUFF_ADR_INPUT_VA_RMS                       BUFF_ADR_MEAS_PF_C + 4
#define BUFF_ADR_INPUT_VB_RMS                       BUFF_ADR_INPUT_VA_RMS + 4
#define BUFF_ADR_INPUT_VC_RMS                       BUFF_ADR_INPUT_VB_RMS + 4
#define BUFF_ADR_INPUT_VAB_RMS                      BUFF_ADR_INPUT_VC_RMS + 4
#define BUFF_ADR_INPUT_VBC_RMS                      BUFF_ADR_INPUT_VAB_RMS + 4
#define BUFF_ADR_INPUT_VCA_RMS                      BUFF_ADR_INPUT_VBC_RMS + 4

#define BUFF_ADR_INPUT_IA_RMS                       BUFF_ADR_INPUT_VCA_RMS + 4
#define BUFF_ADR_INPUT_IB_RMS                       BUFF_ADR_INPUT_IA_RMS + 4
#define BUFF_ADR_INPUT_IC_RMS                       BUFF_ADR_INPUT_IB_RMS + 4
#define BUFF_ADR_INPUT_IAB_RMS                      BUFF_ADR_INPUT_IC_RMS + 4
#define BUFF_ADR_INPUT_IBC_RMS                      BUFF_ADR_INPUT_IAB_RMS + 4
#define BUFF_ADR_INPUT_ICA_RMS                      BUFF_ADR_INPUT_IBC_RMS + 4

#define BUFF_ADR_INPUT_FREQ_A                       BUFF_ADR_INPUT_ICA_RMS + 4
#define BUFF_ADR_INPUT_FREQ_B                       BUFF_ADR_INPUT_FREQ_A + 4
#define BUFF_ADR_INPUT_FREQ_C                       BUFF_ADR_INPUT_FREQ_B + 4

#define BUFF_ADR_INPUT_PWR_A_W                      BUFF_ADR_INPUT_FREQ_C + 4
#define BUFF_ADR_INPUT_PWR_B_W                      BUFF_ADR_INPUT_PWR_A_W + 4
#define BUFF_ADR_INPUT_PWR_C_W                      BUFF_ADR_INPUT_PWR_B_W + 4
#define BUFF_ADR_INPUT_PWR_TOT_W                    BUFF_ADR_INPUT_PWR_C_W + 4

#define BUFF_ADR_INPUT_PWR_A_VAR                    BUFF_ADR_INPUT_PWR_TOT_W + 4
#define BUFF_ADR_INPUT_PWR_B_VAR                    BUFF_ADR_INPUT_PWR_A_VAR + 4
#define BUFF_ADR_INPUT_PWR_C_VAR                    BUFF_ADR_INPUT_PWR_B_VAR + 4
#define BUFF_ADR_INPUT_PWR_TOT_VAR                  BUFF_ADR_INPUT_PWR_C_VAR + 4

#define BUFF_ADR_INPUT_PWR_A_VA                     BUFF_ADR_INPUT_PWR_TOT_VAR + 4
#define BUFF_ADR_INPUT_PWR_B_VA                     BUFF_ADR_INPUT_PWR_A_VA + 4
#define BUFF_ADR_INPUT_PWR_C_VA                     BUFF_ADR_INPUT_PWR_B_VA + 4
#define BUFF_ADR_INPUT_PWR_TOT_VA                   BUFF_ADR_INPUT_PWR_C_VA + 4

#define BUFF_ADR_INPUT_PF_A                         BUFF_ADR_INPUT_PWR_TOT_VA + 4
#define BUFF_ADR_INPUT_PF_B                         BUFF_ADR_INPUT_PF_A + 4
#define BUFF_ADR_INPUT_PF_C                         BUFF_ADR_INPUT_PF_B + 4

#define BUFF_ADR_INPUT_VDC_FB                       BUFF_ADR_INPUT_PF_C + 4
#define BUFF_ADR_EFFECIENCY                         BUFF_ADR_INPUT_VDC_FB + 4

#define BUFF_END_ADDR                               BUFF_ADR_EFFECIENCY + 4

#endif


//extern void InitDataMappping(void);
//extern void MarkDirty(uint16_t address);
//extern void ProcessData(void);
float32_t hex2float(void);
int32_t hex2int(void);
extern void ReadMeasureDataFromSharedMemory(void);
extern void SetDataUpdate(void);
extern void HarmonicTableUpdate(uint16_t startIdx, uint16_t length);
extern void ReadMeasureDataFromPFC(void);
extern void ProcessData(void);

extern float32_t ReadFloatFromMainBuff(uint32_t address);
extern uint32_t ReadByteFromMainBuff(uint32_t address);

extern float32_t ReadFloatFromShared(uint32_t addr);

extern const DataMapEntry Measure_Input_dataMap[];
extern const size_t NUM_ENTRIES_MEAS_IN;

#endif /* COMMON_MEMMAP_H_ */
