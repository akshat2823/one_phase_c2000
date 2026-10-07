/*
 * Common_Memmap.c
 *
 *  Created on: Jul 22, 2025
 *      Author: Anamitra Sarkar
 */


#include "Common_Memmap.h"


uint8_t data[4];

uint16_t addr_prev;
float32_t val_prev_float;
int32_t val_prev_int;

FloatToUint16 floatConv;
IntToUint16 intConv;

uint32_t StatusRegA;
uint32_t Prot_StatusResetFlag;


static const DataMapEntry Source_Limit_dataMap[] = {

#if CONVERTER_TYPE == SINGLE_PHASE
//                                                    //Source Subsystem
//                                                    {BUFF_ADR_SET_VAC, &Vac_fundamental, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_VDC, &V_DC, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_FREQ, &AC_Freq_Ref, TYPE_FLOAT32},
//                                                    {BUFF_ADR_VAC_SLEW, &slope_VacRef, TYPE_FLOAT32},
//
//
//                                                    {BUFF_ADR_SET_I, &Iset, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_RES, &Rset, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_PKVA, &Pkva_set, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_PF, &PFset, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_I_PF, &I_PFset, TYPE_FLOAT32},
//
//                                                    {BUFF_ADR_SET_R_TOP, &R_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_L_TOP, &L_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_C_TOP, &C_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_RL_TOP, &RL_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_RC_TOP, &RC_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_RS_TOP, &RS_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_P_TOP, &P_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_QL_TOP, &QL_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_QC_TOP, &QC_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_IL_TOP, &IL_top, TYPE_FLOAT32},
//                                                    {BUFF_ADR_SET_VC_TOP, &VC_top, TYPE_FLOAT32},
//
//
//                                                    {BUFF_ADR_VDC_SLEW, &V_DC_slope, TYPE_FLOAT32},
//                                                    {BUFF_ADR_FREQ_SLEW, &slope_FreqRef, TYPE_FLOAT32},
//
//                                                    {BUFF_ADR_ON_DEGREE, &ON_degree, TYPE_FLOAT32},
//                                                    {BUFF_ADR_OFF_DEGREE, &OFF_degree, TYPE_FLOAT32},
//                                                    {BUFF_ADR_COUPLE, &CouplingMode, TYPE_UINT32},
//
//                                                    {BUFF_ADR_OUT_STATE, &StartPowerStage, TYPE_UINT32},
//                                                    {BUFF_ADR_HARM_TAB_OUT_STATE, &StartPowerStage_Harm, TYPE_UINT32},
//
//
//                                                    {BUFF_ADR_LOAD_SOURCE_MODE, &LoadSource_mode, TYPE_UINT32},
//                                                    {BUFF_ADR_LOAD__MODE, &Load_mode, TYPE_UINT32},
//                                                    {BUFF_ADR_SELECTED_TOPOLOGY, &Selected_Topology, TYPE_UINT32},
//
//
//                                                    //Limit SubSystem
//
//                                                    {BUFF_ADR_LIM_VAC, &Limit_VAC, TYPE_FLOAT32},
//                                                    {BUFF_ADR_LIM_VDC_P, &Limit_VDC_max, TYPE_FLOAT32},
//                                                    {BUFF_ADR_LIM_VDC_M, &Limit_VDC_min, TYPE_FLOAT32},
//                                                    {BUFF_ADR_LIM_FREQ, &Limit_AC_Freq_Ref, TYPE_FLOAT32},
//                                                    {BUFF_ADR_LIM_OPP, &Limit_OPP, TYPE_FLOAT32},
//                                                    {BUFF_ADR_LIM_OCP, &Limit_OCP, TYPE_FLOAT32},
//                                                    {BUFF_ADR_LIM_OCP_DLY, &Limit_OCP_Delay, TYPE_FLOAT32},

#elif CONVERTER_TYPE == THREE_PHASE
                                                     //Source Subsystem
                                                     {BUFF_ADR_SRC_VA, &VA_fundamental, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VB, &VB_fundamental, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VC, &VC_fundamental, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VAC, &Vac_fundamental, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_VA_SLW, &slope_VaRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VB_SLW, &slope_VbRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VC_SLW, &slope_VcRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VAC_SLW, &slope_VacRef, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_IA, &IA_fundamental, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IB, &IB_fundamental, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IC, &IC_fundamental, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IAC, &Iac_fundamental, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_IA_SLW, &slope_IaRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IB_SLW, &slope_IbRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IC_SLW, &slope_IcRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IAC_SLW, &slope_IacRef, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_FREQ_A, &AC_Freq_Ref_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_FREQ_B, &AC_Freq_Ref_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_FREQ_C, &AC_Freq_Ref_C, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_FREQ, &AC_Freq_Ref, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_FREQ_SLW, &slope_FreqRef, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_FREQ_A_SLW, &slope_FreqRefA, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_FREQ_B_SLW, &slope_FreqRefB, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_FREQ_C_SLW, &slope_FreqRefC, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_ANGLE_AB, &Phase_angle_AB, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_ANGLE_AC, &Phase_angle_AC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_ANGLE_BC, &Phase_angle_BC, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_SEQ_ABC, &Phase_seq_ABC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_SEQ_ACB, &Phase_seq_ACB, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_VA_DC, &VA_DC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VB_DC, &VB_DC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VC_DC, &VC_DC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_V_DC, &V_DC, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_VA_DC_SLW, &VA_DC_slope, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VB_DC_SLW, &VB_DC_slope, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_VC_DC_SLW, &VC_DC_slope, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_V_DC_SLW, &V_DC_slope, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_IA_DC, &IA_DC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IB_DC, &IB_DC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IC_DC, &IC_DC, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_I_DC, &I_DC, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_IA_DC_SLW, &IA_DC_slope, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IB_DC_SLW, &IB_DC_slope, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_IC_DC_SLW, &IC_DC_slope, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_I_DC_SLW, &I_DC_slope, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_ON_DEG_A, &ON_degree_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_ON_DEG_B, &ON_degree_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_ON_DEG_C, &ON_degree_C, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_ON_DEG_ABC, &ON_degree_ABC, TYPE_FLOAT32},

                                                     {BUFF_ADR_SRC_OFF_DEG_A, &OFF_degree_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_OFF_DEG_B, &OFF_degree_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_OFF_DEG_C, &OFF_degree_C, TYPE_FLOAT32},
                                                     {BUFF_ADR_SRC_OFF_DEG_ABC, &OFF_degree_ABC, TYPE_FLOAT32},

                                                     {BUFF_ADR_START_PWR_STAGE, &StartPowerStage, TYPE_UINT32},
                                                     {BUFF_ADR_RLY_CTRL, &Relay_Ctrl, TYPE_UINT32},
                                                     {BUFF_OUTPUT_MODE, &OutputMode, TYPE_UINT32},

                                                     //Limit SubSystem

                                                     {BUFF_ADR_LIM_VA_MAX, &VA_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VA_MIN, &VA_fundamental_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VB_MAX, &VB_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VB_MIN, &VB_fundamental_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VC_MAX, &VC_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VC_MIN, &VC_fundamental_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_V_MAX, &V_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_V_MIN, &V_fundamental_min, TYPE_FLOAT32},

                                                     {BUFF_ADR_LIM_IA_MAX, &IA_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IA_MIN, &IA_fundamental_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IB_MAX, &IB_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IB_MIN, &IB_fundamental_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IC_MAX, &IC_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IC_MIN, &IC_fundamental_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_I_MAX, &I_fundamental_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_I_MIN, &I_fundamental_min, TYPE_FLOAT32},

                                                     {BUFF_ADR_LIM_IA_MAX_DLY, &IA_fundamental_max_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IA_MIN_DLY, &IA_fundamental_min_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IB_MAX_DLY, &IB_fundamental_max_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IB_MIN_DLY, &IB_fundamental_min_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IC_MAX_DLY, &IC_fundamental_max_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IC_MIN_DLY, &IC_fundamental_min_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_I_MAX_DLY, &I_fundamental_max_delay, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_I_MIN_DLY, &I_fundamental_min_delay, TYPE_FLOAT32},

                                                     {BUFF_ADR_LIM_VA_DC_MAX, &VA_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VA_DC_MIN, &VA_DC_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VB_DC_MAX, &VB_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VB_DC_MIN, &VB_DC_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VC_DC_MAX, &VC_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_VC_DC_MIN, &VC_DC_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_V_DC_MAX, &V_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_V_DC_MIN, &V_DC_min, TYPE_FLOAT32},

                                                     {BUFF_ADR_LIM_IA_DC_MAX, &IA_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IA_DC_MIN, &IA_DC_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IB_DC_MAX, &IB_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IB_DC_MIN, &IB_DC_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IC_DC_MAX, &IC_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_IC_DC_MIN, &IC_DC_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_I_DC_MAX, &I_DC_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_I_DC_MIN, &I_DC_min, TYPE_FLOAT32},

                                                     {BUFF_ADR_LIM_FREQ_A_MAX, &AC_Freq_Ref_A_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_A_MIN, &AC_Freq_Ref_A_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_B_MAX, &AC_Freq_Ref_B_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_B_MIN, &AC_Freq_Ref_B_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_C_MAX, &AC_Freq_Ref_C_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_C_MIN, &AC_Freq_Ref_C_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_MAX, &AC_Freq_Ref_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_FREQ_MIN, &AC_Freq_Ref_min, TYPE_FLOAT32},

                                                     {BUFF_ADR_LIM_PWR_A_MAX, &powerRms_A_Watts_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_A_MIN, &powerRms_A_Watts_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_B_MAX, &powerRms_B_Watts_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_B_MIN, &powerRms_B_Watts_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_C_MAX, &powerRms_C_Watts_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_C_MIN, &powerRms_C_Watts_min, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_TOT_MAX, &powerRmsTotal_Watts_max, TYPE_FLOAT32},
                                                     {BUFF_ADR_LIM_PWR_TOT_MIN, &powerRmsTotal_Watts_min, TYPE_FLOAT32},
#endif
};


const DataMapEntry Harmonic_dataMap[] = {

//                                         //Harmonics
//
//                                         {BUFF_ADR_HARM_WAVEFORM_NUM, &harmonic_select, TYPE_UINT32},
//
//                                         {BUFF_ADR_HARM1_NO, &harm1_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM1_AMP, &harm1_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM1_PHASE, &harm1_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM2_NO, &harm2_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM2_AMP, &harm2_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM2_PHASE, &harm2_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM3_NO, &harm3_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM3_AMP, &harm3_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM3_PHASE, &harm3_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM4_NO, &harm4_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM4_AMP, &harm4_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM4_PHASE, &harm4_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM5_NO, &harm5_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM5_AMP, &harm5_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM5_PHASE, &harm5_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM6_NO, &harm6_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM6_AMP, &harm6_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM6_PHASE, &harm6_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM7_NO, &harm7_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM7_AMP, &harm7_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM7_PHASE, &harm7_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM8_NO, &harm8_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM8_AMP, &harm8_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM8_PHASE, &harm8_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM9_NO, &harm9_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM9_AMP, &harm9_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM9_PHASE, &harm9_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM10_NO, &harm10_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM10_AMP, &harm10_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM10_PHASE, &harm10_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM11_NO, &harm11_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM11_AMP, &harm11_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM11_PHASE, &harm11_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM12_NO, &harm12_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM12_AMP, &harm12_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM12_PHASE, &harm12_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM13_NO, &harm13_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM13_AMP, &harm13_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM13_PHASE, &harm13_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM14_NO, &harm14_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM14_AMP, &harm14_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM14_PHASE, &harm14_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM15_NO, &harm15_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM15_AMP, &harm15_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM15_PHASE, &harm15_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM16_NO, &harm16_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM16_AMP, &harm16_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM16_PHASE, &harm16_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM17_NO, &harm17_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM17_AMP, &harm17_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM17_PHASE, &harm17_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM18_NO, &harm18_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM18_AMP, &harm18_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM18_PHASE, &harm18_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM19_NO, &harm19_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM19_AMP, &harm19_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM19_PHASE, &harm19_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM20_NO, &harm20_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM20_AMP, &harm20_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM20_PHASE, &harm20_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM21_NO, &harm21_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM21_AMP, &harm21_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM21_PHASE, &harm21_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM22_NO, &harm22_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM22_AMP, &harm22_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM22_PHASE, &harm22_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM23_NO, &harm23_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM23_AMP, &harm23_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM23_PHASE, &harm23_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM24_NO, &harm24_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM24_AMP, &harm24_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM24_PHASE, &harm24_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM25_NO, &harm25_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM25_AMP, &harm25_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM25_PHASE, &harm25_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM26_NO, &harm26_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM26_AMP, &harm26_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM26_PHASE, &harm26_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM27_NO, &harm27_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM27_AMP, &harm27_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM27_PHASE, &harm27_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM28_NO, &harm28_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM28_AMP, &harm28_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM28_PHASE, &harm28_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM29_NO, &harm29_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM29_AMP, &harm29_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM29_PHASE, &harm29_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM30_NO, &harm30_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM30_AMP, &harm30_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM30_PHASE, &harm30_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM31_NO, &harm31_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM31_AMP, &harm31_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM31_PHASE, &harm31_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM32_NO, &harm32_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM32_AMP, &harm32_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM32_PHASE, &harm32_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM33_NO, &harm33_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM33_AMP, &harm33_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM33_PHASE, &harm33_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM34_NO, &harm34_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM34_AMP, &harm34_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM34_PHASE, &harm34_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM35_NO, &harm35_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM35_AMP, &harm35_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM35_PHASE, &harm35_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM36_NO, &harm36_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM36_AMP, &harm36_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM36_PHASE, &harm36_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM37_NO, &harm37_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM37_AMP, &harm37_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM37_PHASE, &harm37_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM38_NO, &harm38_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM38_AMP, &harm38_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM38_PHASE, &harm38_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM39_NO, &harm39_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM39_AMP, &harm39_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM39_PHASE, &harm39_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM40_NO, &harm40_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM40_AMP, &harm40_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM40_PHASE, &harm40_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM41_NO, &harm41_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM41_AMP, &harm41_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM41_PHASE, &harm41_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM42_NO, &harm42_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM42_AMP, &harm42_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM42_PHASE, &harm42_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM43_NO, &harm43_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM43_AMP, &harm43_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM43_PHASE, &harm43_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM44_NO, &harm44_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM44_AMP, &harm44_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM44_PHASE, &harm44_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM45_NO, &harm45_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM45_AMP, &harm45_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM45_PHASE, &harm45_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM46_NO, &harm46_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM46_AMP, &harm46_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM46_PHASE, &harm46_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM47_NO, &harm47_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM47_AMP, &harm47_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM47_PHASE, &harm47_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM48_NO, &harm48_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM48_AMP, &harm48_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM48_PHASE, &harm48_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM49_NO, &harm49_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM49_AMP, &harm49_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM49_PHASE, &harm49_pha, TYPE_FLOAT32},
//
//                                         {BUFF_ADR_HARM50_NO, &harm50_no, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM50_AMP, &harm50_amp, TYPE_FLOAT32},
//                                         {BUFF_ADR_HARM50_PHASE, &harm50_pha, TYPE_FLOAT32},

};


static const DataMapEntry Measure_Input_dataMap[] = {

#if CONVERTER_TYPE == SINGLE_PHASE

                                                     //Measure Subsystem
//                                                     {BUFF_ADR_MEAS_VOLT, &Meas_Vrms, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_VDC, &Meas_Vdc, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_VAC, &Meas_Vac, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_IDC, &Meas_Idc, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_I, &Meas_Irms, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_IAC, &Meas_Iac, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_FREQ, &Meas_Freq, TYPE_FLOAT32},
//
//                                                     {BUFF_ADR_MEAS_VPK_P, &Meas_Vpk_P, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_IPK_P, &Meas_Ipk_P, TYPE_FLOAT32},
//
//                                                     {BUFF_ADR_MEAS_VPK_N, &Meas_Vpk_N, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_IPK_N, &Meas_Ipk_N, TYPE_FLOAT32},
//
//                                                     {BUFF_ADR_MEAS_V_CF, &Meas_V_CF, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_I_CF, &Meas_I_CF, TYPE_FLOAT32},
//
//                                                     {BUFF_ADR_MEAS_IS, &Meas_Is, TYPE_FLOAT32},
//
//                                                     {BUFF_ADR_MEAS_POWER, &Meas_Preal, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_VAR, &Meas_Preactive, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_VA, &Meas_Papparent, TYPE_FLOAT32},
//                                                     {BUFF_ADR_MEAS_PF, &Meas_PF, TYPE_FLOAT32},
#elif CONVERTER_TYPE == THREE_PHASE
                                                     //Measure Subsystem
                                                     {BUFF_ADR_MEAS_VA_RMS, &VA_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VB_RMS, &VB_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VC_RMS, &VC_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VAB_RMS, &VAB_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VBC_RMS, &VBC_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VCA_RMS, &VCA_RMS_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_IA_RMS, &IA_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IB_RMS, &IB_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IC_RMS, &IC_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IAB_RMS, &IAB_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IBC_RMS, &IBC_RMS_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_ICA_RMS, &ICA_RMS_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_VA_PEAK, &VA_PEAK_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VB_PEAK, &VB_PEAK_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VC_PEAK, &VC_PEAK_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_IA_PEAK, &IA_PEAK_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IB_PEAK, &IB_PEAK_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IC_PEAK, &IC_PEAK_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_VA_DC, &VA_DC_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VB_DC, &VB_DC_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_VC_DC, &VC_DC_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_IA_DC, &IA_DC_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IB_DC, &IB_DC_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_IC_DC, &IC_DC_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_FREQ_A, &Freq_Meas_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_FREQ_B, &Freq_Meas_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_FREQ_C, &Freq_Meas_C, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_PWR_A_W, &powerRms_A_Watts, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_B_W, &powerRms_B_Watts, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_C_W, &powerRms_C_Watts, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_TOT_W, &powerRmsTotal_Watts, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_PWR_A_VAR, &powerRms_A_VARS, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_B_VAR, &powerRms_B_VARS, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_C_VAR, &powerRms_C_VARS, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_TOT_VAR, &powerRmsTotal_VARS, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_PWR_A_VA, &powerRms_A_VA, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_B_VA, &powerRms_B_VA, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_C_VA, &powerRms_C_VA, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PWR_TOT_VA, &powerRmsTotal_VA, TYPE_FLOAT32},

                                                     {BUFF_ADR_MEAS_PF_A, &powerFactor_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PF_B, &powerFactor_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_MEAS_PF_C, &powerFactor_C, TYPE_FLOAT32},

                                                     //Measure Input Subsystem

                                                     {BUFF_ADR_INPUT_VA_RMS, &VA_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_VB_RMS, &VB_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_VC_RMS, &VC_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_VAB_RMS, &VAB_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_VBC_RMS, &VBC_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_VCA_RMS, &VCA_RMS_INPUT_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_IA_RMS, &IA_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_IB_RMS, &IB_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_IC_RMS, &IC_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_IAB_RMS, &IAB_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_IBC_RMS, &IBC_RMS_INPUT_meas, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_ICA_RMS, &ICA_RMS_INPUT_meas, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_FREQ_A, &Freq_INPUT_Meas_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_FREQ_B, &Freq_INPUT_Meas_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_FREQ_C, &Freq_INPUT_Meas_C, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_PWR_A_W, &powerRms_A_Input_Watts, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_B_W, &powerRms_B_Input_Watts, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_C_W, &powerRms_C_Input_Watts, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_TOT_W, &powerRmsTotal_Input_Watts, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_PWR_A_VAR, &powerRms_A_Input_VARS, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_B_VAR, &powerRms_B_Input_VARS, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_C_VAR, &powerRms_C_Input_VARS, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_TOT_VAR, &powerRmsTotal_Input_VARS, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_PWR_A_VA, &powerRms_A_Input_VA, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_B_VA, &powerRms_B_Input_VA, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_C_VA, &powerRms_C_Input_VA, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PWR_TOT_VA, &powerRmsTotal_Input_VA, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_PF_A, &powerFactor_INPUT_A, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PF_B, &powerFactor_INPUT_B, TYPE_FLOAT32},
                                                     {BUFF_ADR_INPUT_PF_C, &powerFactor_INPUT_C, TYPE_FLOAT32},

                                                     {BUFF_ADR_INPUT_VDC_FB, &Vdc_fb, TYPE_FLOAT32},
                                                     {BUFF_ADR_EFFECIENCY, &efficiency, TYPE_FLOAT32},
#endif
};

#define NUM_ENTRIES (sizeof(Source_Limit_dataMap)/sizeof(DataMapEntry))


static uint8_t dirtyFlags[NUM_ENTRIES];

//void InitSource_dataMappping(void)
//{
//    int i = 0;
//    for(i = 0; i < NUM_ENTRIES; i++)
//    {
//        dirtyFlags[i] = 0;
//    }
//}
//
//void MarkDirty(uint16_t address)
//{
//    int i = 0;
//    for(i = 0; i < NUM_ENTRIES; i++)
//    {
//        if(Source_Limit_dataMap[i].BUF_ADR == address)
//        {
//            dirtyFlags[i] = 1;
//            break;
//        }
//    }
//}


//void ReadingDataFromSharedMemory(void)
//{
//    uint16_t addr;
//    float32_t val_float;
//    int32_t val_int;
//#if CONVERTER_TYPE == SINGLE_PHASE
//    uint16_t startIdx = (uint16_t)BUFF_ADR_SET_VAC;
//#else
//    uint16_t startIdx = (uint16_t)BUFF_ADR_SRC_VA;
//#endif
//    uint16_t EndIdx = (uint16_t)BUFF_ADR_HARM_WAVEFORM_NUM;
//
//    uint16_t length = (uint16_t)((EndIdx - startIdx)/4u);
//
//    uint16_t i = 0;
//    for(i = 0; i < length;i++)
//    {
//        addr = Source_Limit_dataMap[i].BUF_ADR;
//
//        data[0] = cpu1Read[addr];
//        data[1] = cpu1Read[addr + 1];
//        data[2] = cpu1Read[addr + 2];
//        data[3] = cpu1Read[addr + 3];
//
//        switch(Source_Limit_dataMap[i].type)
//        {
//        case TYPE_FLOAT32:
//            val_float = hex2float();
//            *(volatile float32_t *)(Source_Limit_dataMap[i].variable_ptr) = val_float;
//            break;
//        case TYPE_UINT32:
//            val_int = hex2int();
//            *(volatile int32_t *)(Source_Limit_dataMap[i].variable_ptr) = val_int;
//            break;
//        }
//    }
//}

void ReadingDataFromSharedMemory(void)
{

    SelMode = ReadByteFromMainBuff(DSP_ACPS_MODE);
    LoadSourceMode = ReadByteFromMainBuff(DSP_LOAD_SOURCE_MODE);
    Load_mode = ReadByteFromMainBuff(DSP_LOAD_MODE);
    Selected_Topology = ReadByteFromMainBuff(DSP_TOPOLOGY_SELECT);

    R_top  = ReadFloatFromMainBuff(DSP_ADR_SET_R_TOP);
    L_top = ReadFloatFromMainBuff(DSP_ADR_SET_L_TOP);
    C_top = ReadFloatFromMainBuff(DSP_ADR_SET_C_TOP);
    RL_top = ReadFloatFromMainBuff(DSP_ADR_SET_RL_TOP);
    RC_top = ReadFloatFromMainBuff(DSP_ADR_SET_RC_TOP);
    RS_top = ReadFloatFromMainBuff(DSP_ADR_SET_RS_TOP);
    P_top = ReadFloatFromMainBuff(DSP_ADR_SET_P_TOP);
    QL_top = ReadFloatFromMainBuff(DSP_ADR_SET_QL_TOP);
    QC_top  = ReadFloatFromMainBuff(DSP_ADR_SET_QC_TOP);
    IL_top = ReadFloatFromMainBuff(DSP_ADR_SET_IL_TOP);
    VC_top = ReadFloatFromMainBuff(DSP_ADR_SET_VC_TOP);

    // ========================================================================
    // 1. SOURCE SETPOINTS (FLOAT AREA)
    // ========================================================================
    SetSourceVoltage1P   = ReadFloatFromMainBuff(DSP_SET_VAC);
    SetSourceCurrent1P   = ReadFloatFromMainBuff(DSP_SET_IAC);
    SetSourceFrequency1P = ReadFloatFromMainBuff(DSP_SET_FREQ);
    SetVdc = ReadFloatFromMainBuff(DSP_SET_VDC);
    if(Slave1Flag)
    {
        SetSourcePhaseAB = ReadFloatFromMainBuff(DSP_PHASE_ANGLE);
        SetSourcePhaseRADIAN = ((SetSourcePhaseAB * 3.14159265f) / 180.0f);
    }
    else if(Slave2Flag)
    {
        SetSourcePhaseAC = ReadFloatFromMainBuff(DSP_PHASE_ANGLE);
        SetSourcePhaseRADIAN = ((SetSourcePhaseAC * 3.14159265f) / 180.0f);
    }
    else SetSourcePhaseRADIAN = 0.0f;

    // ========================================================================
    // 2. SAFETY LIMITS (FLOAT AREA)
    // ========================================================================
    SetLimVac  = ReadFloatFromMainBuff(DSP_LIM_VAC);
    SetLimIac  = ReadFloatFromMainBuff(DSP_LIM_IAC);
    SetLimFreq = ReadFloatFromMainBuff(DSP_LIM_FREQ);
    SetLimPow  = ReadFloatFromMainBuff(DSP_LIM_POW);
    SetLimVdcPlus = ReadFloatFromMainBuff(DSP_LIM_VDC_PLUS);
    SetLimVdcMinus = ReadFloatFromMainBuff(DSP_LIM_VDC_MINUS);


    // ========================================================================
    // 3. STATUS FLAGS (BYTE AREA)
    // ========================================================================
//    OutputState = ReadByteFromMainBuff(DSP_ADR_OUT_STATE);
//    CV_CC_mode  = ReadByteFromMainBuff(DSP_ADR_CV_CC);

}

// ============================================================================
// Reads 4 bytes (stored across 2 x 16-bit slots) from MainBuff at the given
// address and returns as float32_t
// ============================================================================
float32_t ReadFloatFromMainBuff(uint32_t address)
{
    union {
        uint16_t u16[2];
        float32_t f32;
    } converter;

    uint16_t low_word  = ((cpu1Read[address]     & 0x00FF))
                       | ((cpu1Read[address + 1] & 0x00FF) << 8);

    uint16_t high_word = ((cpu1Read[address + 2] & 0x00FF))
                       | ((cpu1Read[address + 3] & 0x00FF) << 8);

    converter.u16[0] = low_word;
    converter.u16[1] = high_word;

    return converter.f32;
}

// ============================================================================
// Reads 1 byte (stored in a 16-bit slot) from MainBuff at the given address
// ============================================================================
uint32_t ReadByteFromMainBuff(uint32_t address)
{
    return (uint32_t)(cpu1Read[address] & 0x00FF);
}

void SyncCommToControl(void)
{
    // ---------- Setpoints: Comm -> Control ----------
    Vac_fundamental    = SetSourceVoltage1P;
    Iset               = SetSourceCurrent1P;
    AC_Freq_Ref        = SetSourceFrequency1P;
    V_DC               = SetVdc;
    LoadSource_mode    = LoadSourceMode;

    // ---------- Limits: Comm -> Control ----------
    Limit_VAC          = SetLimVac;
    Limit_IAC          = SetLimIac;
    Limit_AC_Freq_Ref  = SetLimFreq;
    Limit_OPP          = SetLimPow;
    Limit_VDC_max      = SetLimVdcPlus;
    Limit_VDC_min      = SetLimVdcMinus;

    // ---------- Measurements: Control -> Comm ----------
    MeasureVoltage1P    = Meas_Vrms;
    ReadCurrent1P       = Meas_Irms;
    MeasureFrequency1P  = Meas_Freq;
    MeasureRealPower1P  = Meas_Preal;
    MeasurePfactor1P    = Meas_PF;
    MeasureVdc1P        = Meas_Vdc;
    MeasureIdc1P        = Meas_Idc;
    MeasureVpkPos1P     = Meas_Vpk_P;
    MeasureVpkNeg1P     = Meas_Vpk_N;
    MeasureIpkPos1P     = Meas_Ipk_P;
    MeasureIpkNeg1P     = Meas_Ipk_N;

    MeasVoltageCF       = Meas_V_CF;
    MeasCurrentCF       = Meas_I_CF;
}

//void MemDataUpdate()
//{
//    uint16_t addr;
//    int i = 0;
//    for(i = 0; i < NUM_ENTRIES; i ++)
//    {
//        addr = Source_Limit_dataMap[i].BUF_ADR;
//
//        data[0] = cpu1Read[addr];
//        data[1] = cpu1Read[addr + 1];
//        data[2] = cpu1Read[addr + 2];
//        data[3] = cpu1Read[addr + 3];
//
//        switch(Source_Limit_dataMap[i].type)
//        {
//        case TYPE_FLOAT32:
//            *(volatile float32_t *)(Source_Limit_dataMap[i].variable_ptr) = hex2float();
//            break;
//        case TYPE_UINT32:
//            *(volatile int32_t *)(Source_Limit_dataMap[i].variable_ptr) = hex2int();
//        }
//    }
//}
//
//float32_t hex2float(void)
//{
//    float32_t datareturn;
//
//    floatConv.int16data[0] = (data[1] * 256) +data[0];
//    floatConv.int16data[1] = (data[3] * 256) + data[2];
//
//    datareturn = floatConv.floatVal;
//
//    return datareturn;
//}
//
//int32_t hex2int(void)
//{
//    int32_t datareturn;
//
//    intConv.int16data[0] = (data[1] * 256) +data[0];
//    intConv.int16data[0] = (data[1] * 256) +data[0];
//
//    datareturn = intConv.intVal;
//
//    return datareturn;
//}


//void WriteMeasureDataToSharedMemory(void)
//{
//    union{
//        float32_t f;
//        int32_t i;
//        uint8_t u[4];
//    }DataConv;
//
//    uint16_t i = 0;
//
//    for(i = 0; i < (sizeof(Measure_Input_dataMap)/sizeof(DataMapEntry)); i++)
//    {
//        const DataMapEntry *entry = &Measure_Input_dataMap[i];
//
//        switch(entry->type)
//        {
//        case TYPE_FLOAT32:
//            DataConv.f = *(volatile float32_t *)(entry->variable_ptr);
//            break;
//        case TYPE_UINT32:
//            DataConv.i = *(volatile int32_t *)(entry->variable_ptr);
//            break;
//        }
//
////        cpu1Write[entry->BUF_ADR] = DataConv.u[0];
////        cpu1Write[entry->BUF_ADR + 1] = DataConv.u[1];
////        cpu1Write[entry->BUF_ADR + 2] = DataConv.u[2];
////        cpu1Write[entry->BUF_ADR + 3] = DataConv.u[3];
//
//        cpu1Write[entry->BUF_ADR] = (DataConv.u[0] & 0x00FF);
//        cpu1Write[entry->BUF_ADR + 1] = ((DataConv.u[0] >> 8) & 0x00FF);
//        cpu1Write[entry->BUF_ADR + 2] = (DataConv.u[1] & 0x00FF);
//        cpu1Write[entry->BUF_ADR + 3] = ((DataConv.u[1] >> 8) & 0x00FF);
//    }
//}

void WriteMeasureDataToSharedMemory(void)
{
    convertFloatToByte(MeasureVoltage1P, DSP_MEAS_VAC);
    convertFloatToByte(ReadCurrent1P, DSP_MEAS_IAC);
    convertFloatToByte(MeasureFrequency1P, DSP_MEAS_FREQ);
    convertFloatToByte(MeasureRealPower1P, DSP_MEAS_PREAL);
    convertFloatToByte(MeasurePfactor1P, DSP_MEAS_PF);

    convertFloatToByte(MeasureVdc1P, DSP_MEAS_VDC);
    convertFloatToByte(MeasureIdc1P, DSP_MEAS_IDC);
    convertFloatToByte(MeasureVpkPos1P, DSP_MEAS_VPEAK_POS);
    convertFloatToByte(MeasureVpkNeg1P, DSP_MEAS_VPEAK_NEG);
    convertFloatToByte(MeasureIpkPos1P, DSP_MEAS_IPEAK_POS);
    convertFloatToByte(MeasureIpkNeg1P, DSP_MEAS_IPEAK_NEG);

    convertFloatToByte(MeasVoltageCF, DSP_MEAS_VCREST_FACTOR);
    convertFloatToByte(MeasCurrentCF, DSP_MEAS_ICREST_FACTOR);

}

void convertFloatToByte(float32_t variable, uint32_t address)
{
    union{
        float32_t f;
        int32_t i;
        uint8_t u[4];
    }DataConv;

    DataConv.f = variable;

    cpu1Write[address] = (DataConv.u[0] & 0x00FF);
    cpu1Write[address + 1] = ((DataConv.u[0] >> 8) & 0x00FF);
    cpu1Write[address + 2] = (DataConv.u[1] & 0x00FF);
    cpu1Write[address + 3] = ((DataConv.u[1] >> 8) & 0x00FF);
}

void convertIntToByte(uint32_t variable, uint32_t address)
{
    union{
        int32_t i;
        uint8_t u[4];
    }DataConv;

    DataConv.i = variable;

    cpu1Write[address] = (DataConv.u[0] & 0x00FF);
    cpu1Write[address + 1] = ((DataConv.u[0] >> 8) & 0x00FF);
    cpu1Write[address + 2] = (DataConv.u[1] & 0x00FF);
    cpu1Write[address + 3] = ((DataConv.u[1] >> 8) & 0x00FF);
}

void updateStatusRegister(void)
{
    uint32_t statusTemp = 0U;

    /*
     * StatusRegA bit mapping:
     *
     * bit 0  -> CV_CC_mode
     * bit 1  -> OutputState
     * bit 2  -> DCbus_OVP
     * bit 3  -> DCbus_UVP
     * bit 4  -> outOCP
     * bit 5  -> outOVP
     * bit 6  -> ACfail
     * bit 7  -> reserved
     *
     * bit 8  to bit 31 -> reserved for future flags
     */

    statusTemp |= (((uint32_t)CV_CC_mode  & 0x01UL) << STATUS_A_CV_CC_MODE_BIT);
    statusTemp |= (((uint32_t)OutputState & 0x01UL) << STATUS_A_OUTPUT_STATE_BIT);
    statusTemp |= (((uint32_t)DCbus_OVP   & 0x01UL) << STATUS_A_DCBUS_OVP_BIT);
    statusTemp |= (((uint32_t)DCbus_UVP   & 0x01UL) << STATUS_A_DCBUS_UVP_BIT);
    statusTemp |= (((uint32_t)outOCP      & 0x01UL) << STATUS_A_OUT_OCP_BIT);
    statusTemp |= (((uint32_t)outOVP      & 0x01UL) << STATUS_A_OUT_OVP_BIT);
    statusTemp |= (((uint32_t)ACfail      & 0x01UL) << STATUS_A_AC_FAIL_BIT);

    StatusRegA = statusTemp;

    /*
     * Now divide 32-bit StatusRegA into four 8-bit parts.
     *
     * cpu1Write[] is uint16_t, but we are using only lower 8 bits
     * of each location here.
     */

    cpu1Write[DSP_STATUS_A + 0U] = (uint16_t)((StatusRegA >> 0U)  & 0x00FFUL);
    cpu1Write[DSP_STATUS_A + 1U] = (uint16_t)((StatusRegA >> 8U)  & 0x00FFUL);
    cpu1Write[DSP_STATUS_A + 2U] = (uint16_t)((StatusRegA >> 16U) & 0x00FFUL);
    cpu1Write[DSP_STATUS_A + 3U] = (uint16_t)((StatusRegA >> 24U) & 0x00FFUL);

    if(DCbus_OVP == 1U ||
       DCbus_UVP == 1U ||
          outOCP == 1U ||
          outOVP == 1U ||
          ACfail == 1U)
    {
        Prot_StatusResetFlag = 1U;
    }
    else
    {
        Prot_StatusResetFlag = 0U;
    }
}

void clearStatusRegister(void)
{
    uint32_t receivedStatusRegA = 0U;

    receivedStatusRegA  = ((uint32_t)(cpu1Read[DSP_STATUS_CLEAR_A + 0U] & 0x00FFU));
    receivedStatusRegA |= ((uint32_t)(cpu1Read[DSP_STATUS_CLEAR_A + 1U] & 0x00FFU) << 8U);
    receivedStatusRegA |= ((uint32_t)(cpu1Read[DSP_STATUS_CLEAR_A + 2U] & 0x00FFU) << 16U);
    receivedStatusRegA |= ((uint32_t)(cpu1Read[DSP_STATUS_CLEAR_A + 3U] & 0x00FFU) << 24U);

    if(Prot_StatusResetFlag == 1U)
    {
        if(((receivedStatusRegA >> STATUS_A_DCBUS_OVP_BIT) & 0x01UL) == 1UL)
        {
            DCbus_OVP = 0U;
        }

        if(((receivedStatusRegA >> STATUS_A_DCBUS_UVP_BIT) & 0x01UL) == 1UL)
        {
            DCbus_UVP = 0U;
        }

        if(((receivedStatusRegA >> STATUS_A_OUT_OCP_BIT) & 0x01UL) == 1UL)
        {
            outOCP = 0U;
        }

        if(((receivedStatusRegA >> STATUS_A_OUT_OVP_BIT) & 0x01UL) == 1UL)
        {
            outOVP = 0U;
        }

        if(((receivedStatusRegA >> STATUS_A_AC_FAIL_BIT) & 0x01UL) == 1UL)
        {
            ACfail = 0U;
        }

        Prot_StatusResetFlag = 0U;

        updateStatusRegister();
    }
    else
    {

    }

}



