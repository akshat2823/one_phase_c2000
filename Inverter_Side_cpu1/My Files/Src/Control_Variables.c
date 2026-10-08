/*
 * Control_Variables.c
 *
 *  Created on: Jul 21, 2025
 *      Author: Anamitra Sarkar
 */

#include "Control_Variables.h"

#if CONVERTER_TYPE == SINGLE_PHASE

// ========================================================================
// COMMUNICATION-SIDE VARIABLES
// ========================================================================
float32_t MeasureVoltage1P    = 0.0f;
float32_t ReadCurrent1P       = 0.0f;
float32_t MeasureFrequency1P  = 0.0f;
float32_t MeasureRealPower1P  = 0.0f;
float32_t MeasurePfactor1P    = 0.0f;

float32_t MeasureVdc1P          = 0.0f;
float32_t MeasureIdc1P          = 0.0f;
float32_t MeasureVpkPos1P          = 0.0f;
float32_t MeasureVpkNeg1P       = 0.0f;
float32_t MeasureIpkPos1P       = 0.0f;
float32_t MeasureIpkNeg1P    = 0.0f;

float32_t MeasVoltageCF        = 0.0f;
float32_t MeasCurrentCF        = 0.0f;



uint32_t SelMode;
uint32_t LoadSourceMode;

float32_t SetSourceVoltage1P  = 0.0f;
float32_t SetSourceCurrent1P  = 0.0f;
float32_t SetSourceFrequency1P = 0.0f;
float32_t SetSourcePhaseRADIAN = 0.0f;

float32_t SetSourcePhaseAB = 0.0f;
float32_t SetSourcePhaseAC = 0.0f;

float32_t SetLimVac = 0.0f;
float32_t SetLimIac = 0.0f;
float32_t SetLimPow = 0.0f;
float32_t SetLimFreq = 0.0f;
float32_t SetPhaseAngle = 0.0f;

float32_t SetLimVdcPlus = 0.0f;
float32_t SetLimVdcMinus = 0.0f;
float32_t SetVdc   = 0.0f;

uint32_t SetMonMode = 1;        // Analog Monitoring Mode
                                // SetMonMode = 0  --> 5V range
                                // SetMonMode = 1  --> 10V range

uint32_t CV_CC_mode = 0;
uint32_t OutputState = 0;
uint32_t DCbus_OVP = 0;
uint32_t DCbus_UVP = 0;
uint32_t outOCP = 0;
uint32_t outOVP = 0;
uint32_t ACfail = 0;

volatile int32_t DSP_boot       = 0;
float32_t Vac_fundamental       = 0.0f;
float32_t V_DC                  = 0.0f;
float32_t AC_Freq_Ref           = 0.0f;

float32_t AC_Freq_Ref_active    = 50.0f;
float32_t AC_Freq_Ref_pending   = 50.0f;
uint32_t freqChange             = 0;

float32_t slope_VacRef          = 0.0f;


float32_t Iset                  = 0.0f;
float32_t SetPF_CC              = 0.0f;
float32_t SetR_CR               = 0.0f;
float32_t SetPF_CP              = 0.0f;
float32_t SetP_CP               = 0.0f;

float32_t Rset                  = 0.0f;
float32_t Pkva_set              = 0.0f;
float32_t PFset                 = 0.0f;
float32_t PFSet_CP               = 0.0f;

float32_t R_top                 = 0.0f;
float32_t L_top                 = 0.0f;
float32_t C_top                 = 0.0f;
float32_t RL_top                = 0.0f;
float32_t RC_top                = 0.0f;
float32_t RS_top                = 0.0f;
float32_t P_top                 = 0.0f;
float32_t QL_top                = 0.0f;
float32_t QC_top                = 0.0f;
float32_t IL_top                = 0.0f;
float32_t VC_top                = 0.0f;

float32_t V_DC_slope            = 0.0f;
float32_t slope_FreqRef         = 0.0f;

float32_t ON_degree             = 0.0f;
float32_t OFF_degree            = 0.0f;
volatile uint32_t CouplingMode   = 0;               // For Source Mode -
                                                    //  1)AC+DC
                                                    //  2)AC
                                                    //  3)DC
volatile uint32_t StartPowerStage = 0;
volatile uint32_t StartPowerStage_prev = 0;
volatile uint32_t StartPowerStage_Harm = 0;
volatile uint32_t StartPowerStage_Harm_prev = 0;

volatile uint32_t LoadSource_mode = 0;
volatile uint32_t Load_mode      = 0;
volatile uint32_t Selected_Topology = 0;

float32_t Limit_VAC             = 0.0f;
float32_t Limit_VDC_max         = 0.0f;
float32_t Limit_VDC_min         = 0.0f;
float32_t Limit_AC_Freq_Ref     = 0.0f;
float32_t Limit_OPP             = 0.0f;
float32_t Limit_IAC             = 0.0f;
float32_t Limit_OCP_Delay       = 0.0f;

/* MEASUREMENT VARIABLES */
float32_t Meas_Vrms             = 0.0f;         // RMS Voltage
float32_t Meas_Vdc              = 0.0f;         // DC Voltage component
float32_t Meas_Vac              = 0.0f;         // AC Voltage component
float32_t Meas_Idc              = 0.0f;         // DC Current component
float32_t Meas_Irms             = 0.0f;         // RMS Current
float32_t Meas_Iac              = 0.0f;         // AC Current component
float32_t Meas_Freq             = 0.0f;         // Measured Frequency

float32_t Meas_Vpk_P            = 0.0f;         // Peak Voltage
float32_t Meas_Ipk_P            = 0.0f;         // Peak Current

float32_t Meas_Vpk_N            = 0.0f;         // Peak Voltage
float32_t Meas_Ipk_N            = 0.0f;         // Peak Current

float32_t Meas_V_CF             = 0.0f;         // Crest Factor
float32_t Meas_I_CF             = 0.0f;         // Crest Factor

float32_t Meas_Is               = 0.0f;         // Surge Current / Inrush Current

float32_t Meas_Preal            = 0.0f;         // Real Power (Watts)
float32_t Meas_Preactive        = 0.0f;         // Reactive Power (VAR)
float32_t Meas_Papparent        = 0.0f;         // Apparent Power (VA)
float32_t Meas_PF               = 0.0f;         // Power Factor

/*Input Side Measurement Variables*/
float32_t Meas_Vin_rms          = 0.0f;         // Input RMS Voltage
float32_t Meas_Iin_rms          = 0.0f;         // Input RMS Current
float32_t Meas_Vdc_bus          = 0.0f;         // PFC DC bus voltage
float32_t Meas_Freq_in          = 0.0f;         // Input Measured Frequency
float32_t Meas_Preal_in         = 0.0f;         // Input Real Power (Watts)
float32_t Meas_Preactive_in     = 0.0f;         // Input Reactive Power (VAR)
float32_t Meas_Papparent_in     = 0.0f;         // Input Apparent Power (VA)
float32_t Meas_PF_in            = 0.0f;         // Input Power Factor
volatile uint32_t PFC_state      = 0;            // PFC operating state


#elif CONVERTER_TYPE == THREE_PHASE

//***********Source Subsystem***********//
float32_t VA_fundamental;//done
float32_t VB_fundamental;//done
float32_t VC_fundamental;//done
float32_t Vac_fundamental;//done

float32_t slope_VaRef;//done
float32_t slope_VbRef;//done
float32_t slope_VcRef;//done
float32_t slope_VacRef;//done

float32_t IA_fundamental;//done
float32_t IB_fundamental;//done
float32_t IC_fundamental;//done
float32_t Iac_fundamental;//done

float32_t slope_IaRef;//done
float32_t slope_IbRef;//done
float32_t slope_IcRef;//done
float32_t slope_IacRef;//done

float32_t AC_Freq_Ref_A;//done
float32_t AC_Freq_Ref_B;//done
float32_t AC_Freq_Ref_C;//done
float32_t AC_Freq_Ref;//done

float32_t slope_FreqRef;//done
float32_t slope_FreqRefA;//done
float32_t slope_FreqRefB;//done
float32_t slope_FreqRefC;//done

float32_t Phase_angle_AB;//to be checked later with original variables
float32_t Phase_angle_AC;//to be checked later with original variables
float32_t Phase_angle_BC;//to be checked later with original variables

float32_t Phase_seq_ABC;//new variables
float32_t Phase_seq_ACB;//new variables

float32_t VA_DC;//new variables
float32_t VB_DC;//new variables
float32_t VC_DC;//new variables
float32_t V_DC;//new variables

float32_t VA_DC_slope;//new variables
float32_t VB_DC_slope;//new variables
float32_t VC_DC_slope;//new variables
float32_t V_DC_slope;//new variables

float32_t IA_DC;//new variables
float32_t IB_DC;//new variables
float32_t IC_DC;//new variables
float32_t I_DC;//new variables

float32_t IA_DC_slope;//new variables
float32_t IB_DC_slope;//new variables
float32_t IC_DC_slope;//new variables
float32_t I_DC_slope;//new variables

float32_t ON_degree_A;//new variables
float32_t ON_degree_B;//new variables
float32_t ON_degree_C;//new variables
float32_t ON_degree_ABC;//new variables

float32_t OFF_degree_A;//new variables
float32_t OFF_degree_B;//new variables
float32_t OFF_degree_C;//new variables
float32_t OFF_degree_ABC;//new variables

volatile uint32_t CouplingMode   = 0;               // For Source Mode -
                                                    //  1)AC+DC
                                                    //  2)AC
                                                    //  3)DC
volatile uint32_t StartPowerStage = 0;
volatile uint32_t StartPowerStage_prev = 0;
volatile uint32_t StartPowerStage_Harm = 0;
volatile uint32_t StartPowerStage_Harm_prev = 0;

volatile uint32_t LoadSource_mode = 0;
volatile uint32_t Load_mode      = 0;
volatile uint32_t Selected_Topology = 0;

volatile  int32_t Relay_Ctrl;
volatile int32_t OutputMode;

//***********Limit Subsystem**********//


float32_t VA_fundamental_max;//new variables
float32_t VA_fundamental_min;//new variables
float32_t VB_fundamental_max;//new variables
float32_t VB_fundamental_min;//new variables
float32_t VC_fundamental_max;//new variables
float32_t VC_fundamental_min;//new variables
float32_t V_fundamental_max;//new variables
float32_t V_fundamental_min;//new variables

float32_t IA_fundamental_max;//new variables
float32_t IA_fundamental_min;//new variables
float32_t IB_fundamental_max;//new variables
float32_t IB_fundamental_min;//new variables
float32_t IC_fundamental_max;//new variables
float32_t IC_fundamental_min;//new variables
float32_t I_fundamental_max;//new variables
float32_t I_fundamental_min;//new variables

float32_t IA_fundamental_max_delay;//new variables
float32_t IA_fundamental_min_delay;//new variables
float32_t IB_fundamental_max_delay;//new variables
float32_t IB_fundamental_min_delay;//new variables
float32_t IC_fundamental_max_delay;//new variables
float32_t IC_fundamental_min_delay;//new variables
float32_t I_fundamental_max_delay;//new variables
float32_t I_fundamental_min_delay;//new variables

float32_t VA_DC_max;//new variables
float32_t VA_DC_min;//new variables
float32_t VB_DC_max;//new variables
float32_t VB_DC_min;//new variables
float32_t VC_DC_max;//new variables
float32_t VC_DC_min;//new variables
float32_t V_DC_max;//new variables
float32_t V_DC_min;//new variables

float32_t IA_DC_max;//new variables
float32_t IA_DC_min;//new variables
float32_t IB_DC_max;//new variables
float32_t IB_DC_min;//new variables
float32_t IC_DC_max;//new variables
float32_t IC_DC_min;//new variables
float32_t I_DC_max;//new variables
float32_t I_DC_min;//new variables

float32_t AC_Freq_Ref_A_max;//new variables
float32_t AC_Freq_Ref_A_min;//new variables
float32_t AC_Freq_Ref_B_max;//new variables
float32_t AC_Freq_Ref_B_min;//new variables
float32_t AC_Freq_Ref_C_max;//new variables
float32_t AC_Freq_Ref_C_min;//new variables
float32_t AC_Freq_Ref_max;//new variables
float32_t AC_Freq_Ref_min;//new variables

float32_t powerRms_A_Watts_max;//new variables
float32_t powerRms_A_Watts_min;//new variables
float32_t powerRms_B_Watts_max;//new variables
float32_t powerRms_B_Watts_min;//new variables
float32_t powerRms_C_Watts_max;//new variables
float32_t powerRms_C_Watts_min;//new variables
float32_t powerRmsTotal_Watts_max;//new variables
float32_t powerRmsTotal_Watts_min;//new variables

//************Measure Subsytem************//

float32_t VA_RMS_meas;//old variables with new name
float32_t VB_RMS_meas;//old variables with new name
float32_t VC_RMS_meas;//old variables with new name
float32_t VAB_RMS_meas;//new variables
float32_t VBC_RMS_meas;//new variables
float32_t VCA_RMS_meas;//new variables
float32_t IA_RMS_meas;//old variables with new name
float32_t IB_RMS_meas;//old variables with new name
float32_t IC_RMS_meas;//old variables with new name
float32_t IAB_RMS_meas;//new variables
float32_t IBC_RMS_meas;//new variables
float32_t ICA_RMS_meas;//new variables

float32_t VA_PEAK_meas;//new variables
float32_t VB_PEAK_meas;//new variables
float32_t VC_PEAK_meas;//new variables

float32_t IA_PEAK_meas;//old variables with new name
float32_t IB_PEAK_meas;//old variables with new name
float32_t IC_PEAK_meas;//old variables with new name


float32_t VA_DC_meas;//new variables
float32_t VB_DC_meas;//new variables
float32_t VC_DC_meas;//new variables
float32_t IA_DC_meas;//new variables
float32_t IB_DC_meas;//new variables
float32_t IC_DC_meas;//new variables

float32_t Freq_Meas_A;//new variable with 3 individual frequency
float32_t Freq_Meas_B;//new variable with 3 individual frequency
float32_t Freq_Meas_C;//new variable with 3 individual frequency

float32_t powerRms_A_Watts;//done
float32_t powerRms_B_Watts;//done
float32_t powerRms_C_Watts;//done
float32_t powerRmsTotal_Watts;//done

float32_t powerRms_A_VARS;//new variable
float32_t powerRms_B_VARS;//new variable
float32_t powerRms_C_VARS;//new variable
float32_t powerRmsTotal_VARS;//new variable

float32_t powerRms_A_VA;//new variable
float32_t powerRms_B_VA;//new variable
float32_t powerRms_C_VA;//new variable
float32_t powerRmsTotal_VA;//new variable

float32_t powerFactor_A;//done
float32_t powerFactor_B;//done
float32_t powerFactor_C;//done

//************Measure Subsystem INPUT ************//

float32_t VA_RMS_INPUT_meas;//new variables
float32_t VB_RMS_INPUT_meas;//new variables
float32_t VC_RMS_INPUT_meas;//new variables
float32_t VAB_RMS_INPUT_meas;//new variables
float32_t VBC_RMS_INPUT_meas;//new variables
float32_t VCA_RMS_INPUT_meas;//new variables
float32_t IA_RMS_INPUT_meas;//new variables
float32_t IB_RMS_INPUT_meas;//new variables
float32_t IC_RMS_INPUT_meas;//new variables
float32_t IAB_RMS_INPUT_meas;//new variables
float32_t IBC_RMS_INPUT_meas;//new variables
float32_t ICA_RMS_INPUT_meas;//new variables

float32_t Freq_INPUT_Meas_A;//new variables
float32_t Freq_INPUT_Meas_B;//new variables
float32_t Freq_INPUT_Meas_C;//new variables

float32_t powerRms_A_Input_Watts;//new variables
float32_t powerRms_B_Input_Watts;//new variables
float32_t powerRms_C_Input_Watts;//new variables
float32_t powerRmsTotal_Input_Watts;//new variables

float32_t powerRms_A_Input_VARS;//new variables
float32_t powerRms_B_Input_VARS;//new variables
float32_t powerRms_C_Input_VARS;//new variables
float32_t powerRmsTotal_Input_VARS;//new variables

float32_t powerRms_A_Input_VA;//new variables
float32_t powerRms_B_Input_VA;//new variables
float32_t powerRms_C_Input_VA;//new variables
float32_t powerRmsTotal_Input_VA;//new variables

float32_t powerFactor_INPUT_A;//new variables
float32_t powerFactor_INPUT_B;//new variables
float32_t powerFactor_INPUT_C;//new variables

float32_t Vdc_fb;//done
float32_t efficiency;

#endif


// Common Variables

uint32_t harmonic_select         = 0;

float32_t harm1_no              = 0.0f;
float32_t harm1_amp             = 0.0f;
float32_t harm1_pha             = 0.0f;

float32_t harm2_no              = 0.0f;
float32_t harm2_amp             = 0.0f;
float32_t harm2_pha             = 0.0f;

float32_t harm3_no              = 0.0f;
float32_t harm3_amp             = 0.0f;
float32_t harm3_pha             = 0.0f;

float32_t harm4_no              = 0.0f;
float32_t harm4_amp             = 0.0f;
float32_t harm4_pha             = 0.0f;

float32_t harm5_no              = 0.0f;
float32_t harm5_amp             = 0.0f;
float32_t harm5_pha             = 0.0f;

float32_t harm6_no              = 0.0f;
float32_t harm6_amp             = 0.0f;
float32_t harm6_pha             = 0.0f;

float32_t harm7_no              = 0.0f;
float32_t harm7_amp             = 0.0f;
float32_t harm7_pha             = 0.0f;

float32_t harm8_no              = 0.0f;
float32_t harm8_amp             = 0.0f;
float32_t harm8_pha             = 0.0f;

float32_t harm9_no              = 0.0f;
float32_t harm9_amp             = 0.0f;
float32_t harm9_pha             = 0.0f;

float32_t harm10_no             = 0.0f;
float32_t harm10_amp            = 0.0f;
float32_t harm10_pha            = 0.0f;

float32_t harm11_no             = 0.0f;
float32_t harm11_amp            = 0.0f;
float32_t harm11_pha            = 0.0f;

float32_t harm12_no             = 0.0f;
float32_t harm12_amp            = 0.0f;
float32_t harm12_pha            = 0.0f;

float32_t harm13_no             = 0.0f;
float32_t harm13_amp            = 0.0f;
float32_t harm13_pha            = 0.0f;

float32_t harm14_no             = 0.0f;
float32_t harm14_amp            = 0.0f;
float32_t harm14_pha            = 0.0f;

float32_t harm15_no             = 0.0f;
float32_t harm15_amp            = 0.0f;
float32_t harm15_pha            = 0.0f;

float32_t harm16_no             = 0.0f;
float32_t harm16_amp            = 0.0f;
float32_t harm16_pha            = 0.0f;

float32_t harm17_no             = 0.0f;
float32_t harm17_amp            = 0.0f;
float32_t harm17_pha            = 0.0f;

float32_t harm18_no             = 0.0f;
float32_t harm18_amp            = 0.0f;
float32_t harm18_pha            = 0.0f;

float32_t harm19_no             = 0.0f;
float32_t harm19_amp            = 0.0f;
float32_t harm19_pha            = 0.0f;

float32_t harm20_no             = 0.0f;
float32_t harm20_amp            = 0.0f;
float32_t harm20_pha            = 0.0f;

float32_t harm21_no             = 0.0f;
float32_t harm21_amp            = 0.0f;
float32_t harm21_pha            = 0.0f;

float32_t harm22_no             = 0.0f;
float32_t harm22_amp            = 0.0f;
float32_t harm22_pha            = 0.0f;

float32_t harm23_no             = 0.0f;
float32_t harm23_amp            = 0.0f;
float32_t harm23_pha            = 0.0f;

float32_t harm24_no             = 0.0f;
float32_t harm24_amp            = 0.0f;
float32_t harm24_pha            = 0.0f;

float32_t harm25_no             = 0.0f;
float32_t harm25_amp            = 0.0f;
float32_t harm25_pha            = 0.0f;

float32_t harm26_no             = 0.0f;
float32_t harm26_amp            = 0.0f;
float32_t harm26_pha            = 0.0f;

float32_t harm27_no             = 0.0f;
float32_t harm27_amp            = 0.0f;
float32_t harm27_pha            = 0.0f;

float32_t harm28_no             = 0.0f;
float32_t harm28_amp            = 0.0f;
float32_t harm28_pha            = 0.0f;

float32_t harm29_no             = 0.0f;
float32_t harm29_amp            = 0.0f;
float32_t harm29_pha            = 0.0f;

float32_t harm30_no             = 0.0f;
float32_t harm30_amp            = 0.0f;
float32_t harm30_pha            = 0.0f;

float32_t harm31_no             = 0.0f;
float32_t harm31_amp            = 0.0f;
float32_t harm31_pha            = 0.0f;

float32_t harm32_no             = 0.0f;
float32_t harm32_amp            = 0.0f;
float32_t harm32_pha            = 0.0f;

float32_t harm33_no             = 0.0f;
float32_t harm33_amp            = 0.0f;
float32_t harm33_pha            = 0.0f;

float32_t harm34_no             = 0.0f;
float32_t harm34_amp            = 0.0f;
float32_t harm34_pha            = 0.0f;

float32_t harm35_no             = 0.0f;
float32_t harm35_amp            = 0.0f;
float32_t harm35_pha            = 0.0f;

float32_t harm36_no             = 0.0f;
float32_t harm36_amp            = 0.0f;
float32_t harm36_pha            = 0.0f;

float32_t harm37_no             = 0.0f;
float32_t harm37_amp            = 0.0f;
float32_t harm37_pha            = 0.0f;

float32_t harm38_no             = 0.0f;
float32_t harm38_amp            = 0.0f;
float32_t harm38_pha            = 0.0f;

float32_t harm39_no             = 0.0f;
float32_t harm39_amp            = 0.0f;
float32_t harm39_pha            = 0.0f;

float32_t harm40_no             = 0.0f;
float32_t harm40_amp            = 0.0f;
float32_t harm40_pha            = 0.0f;

float32_t harm41_no             = 0.0f;
float32_t harm41_amp            = 0.0f;
float32_t harm41_pha            = 0.0f;

float32_t harm42_no             = 0.0f;
float32_t harm42_amp            = 0.0f;
float32_t harm42_pha            = 0.0f;

float32_t harm43_no             = 0.0f;
float32_t harm43_amp            = 0.0f;
float32_t harm43_pha            = 0.0f;

float32_t harm44_no             = 0.0f;
float32_t harm44_amp            = 0.0f;
float32_t harm44_pha            = 0.0f;

float32_t harm45_no             = 0.0f;
float32_t harm45_amp            = 0.0f;
float32_t harm45_pha            = 0.0f;

float32_t harm46_no             = 0.0f;
float32_t harm46_amp            = 0.0f;
float32_t harm46_pha            = 0.0f;

float32_t harm47_no             = 0.0f;
float32_t harm47_amp            = 0.0f;
float32_t harm47_pha            = 0.0f;

float32_t harm48_no             = 0.0f;
float32_t harm48_amp            = 0.0f;
float32_t harm48_pha            = 0.0f;

float32_t harm49_no             = 0.0f;
float32_t harm49_amp            = 0.0f;
float32_t harm49_pha            = 0.0f;

float32_t harm50_no             = 0.0f;
float32_t harm50_amp            = 0.0f;
float32_t harm50_pha            = 0.0f;


bool seq_start;
float32_t seq_table[100][3];



















