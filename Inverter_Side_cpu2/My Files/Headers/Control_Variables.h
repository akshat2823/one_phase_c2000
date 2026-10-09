/*
 * Control_Variables.h
 *
 *  Created on: Jul 18, 2025
 *      Author: Anamitra Sarkar
 */

#ifndef CONTROL_VARIABLES_H_
#define CONTROL_VARIABLES_H_

#include <stdio.h>
#include <stdint.h>
#include "device.h"
#include "driverlib.h"
#include "Config.h"

#if CONVERTER_TYPE == SINGLE_PHASE

// ========================================================================
// COMMUNICATION-SIDE VARIABLES (Received from / Sent to Display)
// ========================================================================
// --- Measurements (Read-Only, sent out) ---
extern float32_t MeasureVoltage1P;
extern float32_t ReadCurrent1P;
extern float32_t MeasureFrequency1P;
extern float32_t MeasureRealPower1P;
extern float32_t MeasurePfactor1P;

extern float32_t MeasureVdc1P;
extern float32_t MeasureIdc1P;
extern float32_t MeasureVpkPos1P;
extern float32_t MeasureVpkNeg1P;
extern float32_t MeasureIpkPos1P;
extern float32_t MeasureIpkNeg1P;

extern float32_t MeasVoltageCF;
extern float32_t MeasCurrentCF;


extern uint32_t OutputState;
extern uint32_t SelMode;
extern uint32_t CV_CC_mode;

extern uint32_t LoadSourceMode;

// --- Source Setpoints (1 phase) ---
extern float32_t SetSourceVoltage1P;
extern float32_t SetSourceCurrent1P;
extern float32_t SetSourceFrequency1P;

extern float32_t SetSourcePhaseAB;
extern float32_t SetSourcePhaseAC;
extern float32_t SetSourcePhaseRADIAN;

// --- Limits ---
extern float32_t SetLimVac;
extern float32_t SetLimIac;
extern float32_t SetLimPow;
extern float32_t SetLimFreq;

extern  float32_t SetLimVdcPlus;
extern  float32_t SetLimVdcMinus;
extern  float32_t SetVdc;
extern float32_t SetPhaseAngle_CC;
extern float32_t SetR_CR;
extern float32_t SetP_CP;
extern float32_t SetPF_CP;


extern volatile int32_t DSP_boot;
extern float32_t Vac_fundamental;
extern float32_t V_DC;
extern float32_t AC_Freq_Ref;
extern float32_t slope_VacRef;


extern float32_t Iset;
extern float32_t Rset;
extern float32_t Pkva_set;
extern float32_t PhaseAngleSet_CC;
extern float32_t PFSet_CP;

extern float32_t Coeff_B0;
extern float32_t Coeff_B1;
extern float32_t Coeff_B2;
extern float32_t Coeff_A1;
extern float32_t Coeff_A2;
extern float32_t P_top;
extern float32_t QL_top;
extern float32_t QC_top;


extern float32_t V_DC_slope;
extern float32_t slope_FreqRef;

extern float32_t ON_degree;
extern float32_t OFF_degree;
extern volatile uint32_t CouplingMode;      // For Source Mode -
                                            //  1)AC+DC
                                            //  2)AC
                                            //  3)DC

extern volatile uint32_t StartPowerStage;
extern volatile uint32_t StartPowerStage_prev;
extern volatile uint32_t StartPowerStage_Harm;
extern volatile uint32_t StartPowerStage_Harm_prev;

extern volatile uint32_t LoadSource_mode;
extern volatile uint32_t Load_mode;
extern volatile uint32_t Selected_Topology;

extern float32_t Limit_VAC;
extern float32_t Limit_VDC_max;
extern float32_t Limit_VDC_min;
extern float32_t Limit_AC_Freq_Ref;
extern float32_t Limit_OPP;
extern float32_t Limit_OCP;
extern float32_t Limit_OCP_Delay;

extern uint32_t harmonic_select;
extern uint32_t tableUpdateVariable;

extern float32_t harm1_no;
extern float32_t harm1_amp;
extern float32_t harm1_pha;

extern float32_t harm2_no;
extern float32_t harm2_amp;
extern float32_t harm2_pha;

extern float32_t harm3_no;
extern float32_t harm3_amp;
extern float32_t harm3_pha;

extern float32_t harm4_no;
extern float32_t harm4_amp;
extern float32_t harm4_pha;

extern float32_t harm5_no;
extern float32_t harm5_amp;
extern float32_t harm5_pha;

extern float32_t harm6_no;
extern float32_t harm6_amp;
extern float32_t harm6_pha;

extern float32_t harm7_no;
extern float32_t harm7_amp;
extern float32_t harm7_pha;

extern float32_t harm8_no;
extern float32_t harm8_amp;
extern float32_t harm8_pha;

extern float32_t harm9_no;
extern float32_t harm9_amp;
extern float32_t harm9_pha;

extern float32_t harm10_no;
extern float32_t harm10_amp;
extern float32_t harm10_pha;

extern float32_t harm11_no;
extern float32_t harm11_amp;
extern float32_t harm11_pha;

extern float32_t harm12_no;
extern float32_t harm12_amp;
extern float32_t harm12_pha;

extern float32_t harm13_no;
extern float32_t harm13_amp;
extern float32_t harm13_pha;

extern float32_t harm14_no;
extern float32_t harm14_amp;
extern float32_t harm14_pha;

extern float32_t harm15_no;
extern float32_t harm15_amp;
extern float32_t harm15_pha;

extern float32_t harm16_no;
extern float32_t harm16_amp;
extern float32_t harm16_pha;

extern float32_t harm17_no;
extern float32_t harm17_amp;
extern float32_t harm17_pha;

extern float32_t harm18_no;
extern float32_t harm18_amp;
extern float32_t harm18_pha;

extern float32_t harm19_no;
extern float32_t harm19_amp;
extern float32_t harm19_pha;

extern float32_t harm20_no;
extern float32_t harm20_amp;
extern float32_t harm20_pha;

extern float32_t harm21_no;
extern float32_t harm21_amp;
extern float32_t harm21_pha;

extern float32_t harm22_no;
extern float32_t harm22_amp;
extern float32_t harm22_pha;

extern float32_t harm23_no;
extern float32_t harm23_amp;
extern float32_t harm23_pha;

extern float32_t harm24_no;
extern float32_t harm24_amp;
extern float32_t harm24_pha;

extern float32_t harm25_no;
extern float32_t harm25_amp;
extern float32_t harm25_pha;

extern float32_t harm26_no;
extern float32_t harm26_amp;
extern float32_t harm26_pha;

extern float32_t harm27_no;
extern float32_t harm27_amp;
extern float32_t harm27_pha;

extern float32_t harm28_no;
extern float32_t harm28_amp;
extern float32_t harm28_pha;

extern float32_t harm29_no;
extern float32_t harm29_amp;
extern float32_t harm29_pha;

extern float32_t harm30_no;
extern float32_t harm30_amp;
extern float32_t harm30_pha;

extern float32_t harm31_no;
extern float32_t harm31_amp;
extern float32_t harm31_pha;

extern float32_t harm32_no;
extern float32_t harm32_amp;
extern float32_t harm32_pha;

extern float32_t harm33_no;
extern float32_t harm33_amp;
extern float32_t harm33_pha;

extern float32_t harm34_no;
extern float32_t harm34_amp;
extern float32_t harm34_pha;

extern float32_t harm35_no;
extern float32_t harm35_amp;
extern float32_t harm35_pha;

extern float32_t harm36_no;
extern float32_t harm36_amp;
extern float32_t harm36_pha;

extern float32_t harm37_no;
extern float32_t harm37_amp;
extern float32_t harm37_pha;

extern float32_t harm38_no;
extern float32_t harm38_amp;
extern float32_t harm38_pha;

extern float32_t harm39_no;
extern float32_t harm39_amp;
extern float32_t harm39_pha;

extern float32_t harm40_no;
extern float32_t harm40_amp;
extern float32_t harm40_pha;

extern float32_t harm41_no;
extern float32_t harm41_amp;
extern float32_t harm41_pha;

extern float32_t harm42_no;
extern float32_t harm42_amp;
extern float32_t harm42_pha;

extern float32_t harm43_no;
extern float32_t harm43_amp;
extern float32_t harm43_pha;

extern float32_t harm44_no;
extern float32_t harm44_amp;
extern float32_t harm44_pha;

extern float32_t harm45_no;
extern float32_t harm45_amp;
extern float32_t harm45_pha;

extern float32_t harm46_no;
extern float32_t harm46_amp;
extern float32_t harm46_pha;

extern float32_t harm47_no;
extern float32_t harm47_amp;
extern float32_t harm47_pha;

extern float32_t harm48_no;
extern float32_t harm48_amp;
extern float32_t harm48_pha;

extern float32_t harm49_no;
extern float32_t harm49_amp;
extern float32_t harm49_pha;

extern float32_t harm50_no;
extern float32_t harm50_amp;
extern float32_t harm50_pha;

/* MEASUREMENT VARIABLES */
extern float32_t Meas_Vrms;            // RMS Voltage
extern float32_t Meas_Vdc;             // DC Voltage component
extern float32_t Meas_Vac;             // AC Voltage component
extern float32_t Meas_Idc;             // DC Current component
extern float32_t Meas_Irms;            // RMS Current
extern float32_t Meas_Iac;             // AC Current component
extern float32_t Meas_Freq;            // Measured Frequency

extern float32_t Meas_Vpk_P;           // Peak Voltage
extern float32_t Meas_Ipk_P;           // Peak Current

extern float32_t Meas_Vpk_N;           // Peak Voltage
extern float32_t Meas_Ipk_N;           // Peak Current

extern float32_t Meas_V_CF;            // Crest Factor
extern float32_t Meas_I_CF;            // Crest Factor

extern float32_t Meas_Is;              // Surge Current / Inrush Current

extern float32_t Meas_Preal;           // Real Power (Watts)
extern float32_t Meas_Preactive;       // Reactive Power (VAR)
extern float32_t Meas_Papparent;       // Apparent Power (VA)
extern float32_t Meas_PF;              // Power Factor



/*Input Side Measurement Variables*/
extern float32_t Meas_Vin_rms;                // Input RMS Voltage
extern float32_t Meas_Iin_rms;                // Input RMS Current
extern float32_t Meas_Vdc_bus;                // PFC DC bus voltage
extern float32_t Meas_Freq_in;                // Input Measured Frequency
extern float32_t Meas_Preal_in;               // Input Real Power (Watts)
extern float32_t Meas_Preactive_in;           // Input Reactive Power (VAR)
extern float32_t Meas_Papparent_in;           // Input Apparent Power (VA)
extern float32_t Meas_PF_in;                  // Input Power Factor
extern volatile uint32_t PFC_state;            // PFC operating state

#elif CONVERTER_TYPE == THREE_PHASE

//***********Source Subsystem***********//

extern float32_t VA_fundamental;
extern float32_t VB_fundamental;
extern float32_t VC_fundamental;
extern float32_t Vac_fundamental;

extern float32_t slope_VaRef;
extern float32_t slope_VbRef;
extern float32_t slope_VcRef;
extern float32_t slope_VacRef;

extern float32_t IA_fundamental;
extern float32_t IB_fundamental;
extern float32_t IC_fundamental;
extern float32_t Iac_fundamental;

extern float32_t slope_IaRef;
extern float32_t slope_IbRef;
extern float32_t slope_IcRef;
extern float32_t slope_IacRef;

extern float32_t AC_Freq_Ref_A;
extern float32_t AC_Freq_Ref_B;
extern float32_t AC_Freq_Ref_C;
extern float32_t AC_Freq_Ref;

extern float32_t slope_FreqRef;
extern float32_t slope_FreqRefA;
extern float32_t slope_FreqRefB;
extern float32_t slope_FreqRefC;

extern float32_t Phase_angle_AB;
extern float32_t Phase_angle_AC;
extern float32_t Phase_angle_BC;

extern float32_t Phase_seq_ABC;
extern float32_t Phase_seq_ACB;

extern float32_t VA_DC;
extern float32_t VB_DC;
extern float32_t VC_DC;
extern float32_t V_DC;

extern float32_t VA_DC_slope;
extern float32_t VB_DC_slope;
extern float32_t VC_DC_slope;
extern float32_t V_DC_slope;

extern float32_t IA_DC;
extern float32_t IB_DC;
extern float32_t IC_DC;
extern float32_t I_DC;

extern float32_t IA_DC_slope;
extern float32_t IB_DC_slope;
extern float32_t IC_DC_slope;
extern float32_t I_DC_slope;

extern float32_t ON_degree_A;
extern float32_t ON_degree_B;
extern float32_t ON_degree_C;
extern float32_t ON_degree_ABC;

extern float32_t OFF_degree_A;
extern float32_t OFF_degree_B;
extern float32_t OFF_degree_C;
extern float32_t OFF_degree_ABC;

extern volatile int32_t StartPowerStage;
extern volatile int32_t Relay_Ctrl;
extern volatile int32_t OutputMode;

//***********Limit Subsystem**********//


extern float32_t VA_fundamental_max;
extern float32_t VA_fundamental_min;
extern float32_t VB_fundamental_max;
extern float32_t VB_fundamental_min;
extern float32_t VC_fundamental_max;
extern float32_t VC_fundamental_min;
extern float32_t V_fundamental_max;
extern float32_t V_fundamental_min;

extern float32_t IA_fundamental_max;
extern float32_t IA_fundamental_min;
extern float32_t IB_fundamental_max;
extern float32_t IB_fundamental_min;
extern float32_t IC_fundamental_max;
extern float32_t IC_fundamental_min;
extern float32_t I_fundamental_max;
extern float32_t I_fundamental_min;

extern float32_t IA_fundamental_max_delay;
extern float32_t IA_fundamental_min_delay;
extern float32_t IB_fundamental_max_delay;
extern float32_t IB_fundamental_min_delay;
extern float32_t IC_fundamental_max_delay;
extern float32_t IC_fundamental_min_delay;
extern float32_t I_fundamental_max_delay;
extern float32_t I_fundamental_min_delay;

extern float32_t VA_DC_max;
extern float32_t VA_DC_min;
extern float32_t VB_DC_max;
extern float32_t VB_DC_min;
extern float32_t VC_DC_max;
extern float32_t VC_DC_min;
extern float32_t V_DC_max;
extern float32_t V_DC_min;

extern float32_t IA_DC_max;
extern float32_t IA_DC_min;
extern float32_t IB_DC_max;
extern float32_t IB_DC_min;
extern float32_t IC_DC_max;
extern float32_t IC_DC_min;
extern float32_t I_DC_max;
extern float32_t I_DC_min;

extern float32_t AC_Freq_Ref_A_max;
extern float32_t AC_Freq_Ref_A_min;
extern float32_t AC_Freq_Ref_B_max;
extern float32_t AC_Freq_Ref_B_min;
extern float32_t AC_Freq_Ref_C_max;
extern float32_t AC_Freq_Ref_C_min;
extern float32_t AC_Freq_Ref_max;
extern float32_t AC_Freq_Ref_min;

extern float32_t powerRms_A_Watts_max;
extern float32_t powerRms_A_Watts_min;
extern float32_t powerRms_B_Watts_max;
extern float32_t powerRms_B_Watts_min;
extern float32_t powerRms_C_Watts_max;
extern float32_t powerRms_C_Watts_min;
extern float32_t powerRmsTotal_Watts_max;
extern float32_t powerRmsTotal_Watts_min;


extern float32_t OldVA_RMS_meas;
extern float32_t OldIA_RMS_meas;

//************Measure Subsystem************//


extern float32_t VA_RMS_meas;
extern float32_t VB_RMS_meas;
extern float32_t VC_RMS_meas;
extern float32_t VAB_RMS_meas;
extern float32_t VBC_RMS_meas;
extern float32_t VCA_RMS_meas;
extern float32_t IA_RMS_meas;
extern float32_t IB_RMS_meas;
extern float32_t IC_RMS_meas;
extern float32_t IAB_RMS_meas;
extern float32_t IBC_RMS_meas;
extern float32_t ICA_RMS_meas;

extern float32_t VA_PEAK_meas;
extern float32_t VB_PEAK_meas;
extern float32_t VC_PEAK_meas;

extern float32_t IA_PEAK_meas;
extern float32_t IB_PEAK_meas;
extern float32_t IC_PEAK_meas;

extern float32_t VA_DC_meas;
extern float32_t VB_DC_meas;
extern float32_t VC_DC_meas;
extern float32_t IA_DC_meas;
extern float32_t IB_DC_meas;
extern float32_t IC_DC_meas;

extern float32_t Freq_Meas_A;
extern float32_t Freq_Meas_B;
extern float32_t Freq_Meas_C;

extern float32_t powerRms_A_Watts;
extern float32_t powerRms_B_Watts;
extern float32_t powerRms_C_Watts;
extern float32_t powerRmsTotal_Watts;

extern float32_t powerRms_A_VARS;
extern float32_t powerRms_B_VARS;
extern float32_t powerRms_C_VARS;
extern float32_t powerRmsTotal_VARS;

extern float32_t powerRms_A_VA;
extern float32_t powerRms_B_VA;
extern float32_t powerRms_C_VA;
extern float32_t powerRmsTotal_VA;

extern float32_t powerFactor_A;
extern float32_t powerFactor_B;
extern float32_t powerFactor_C;

//************Measure Subsystem INPUT ************//

extern float32_t VA_RMS_INPUT_meas;
extern float32_t VB_RMS_INPUT_meas;
extern float32_t VC_RMS_INPUT_meas;
extern float32_t VAB_RMS_INPUT_meas;
extern float32_t VBC_RMS_INPUT_meas;
extern float32_t VCA_RMS_INPUT_meas;
extern float32_t IA_RMS_INPUT_meas;
extern float32_t IB_RMS_INPUT_meas;
extern float32_t IC_RMS_INPUT_meas;
extern float32_t IAB_RMS_INPUT_meas;
extern float32_t IBC_RMS_INPUT_meas;
extern float32_t ICA_RMS_INPUT_meas;

extern float32_t Freq_INPUT_Meas_A;
extern float32_t Freq_INPUT_Meas_B;
extern float32_t Freq_INPUT_Meas_C;

extern float32_t powerRms_A_Input_Watts;
extern float32_t powerRms_B_Input_Watts;
extern float32_t powerRms_C_Input_Watts;
extern float32_t powerRmsTotal_Input_Watts;

extern float32_t powerRms_A_Input_VARS;
extern float32_t powerRms_B_Input_VARS;
extern float32_t powerRms_C_Input_VARS;
extern float32_t powerRmsTotal_Input_VARS;

extern float32_t powerRms_A_Input_VA;
extern float32_t powerRms_B_Input_VA;
extern float32_t powerRms_C_Input_VA;
extern float32_t powerRmsTotal_Input_VA;

extern float32_t powerFactor_INPUT_A;
extern float32_t powerFactor_INPUT_B;
extern float32_t powerFactor_INPUT_C;

extern float32_t Vdc_fb;
extern float32_t efficiency;

#endif


#endif /* CONTROL_VARIABLES_H_ */
