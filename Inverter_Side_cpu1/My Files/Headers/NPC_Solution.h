/*
 * NPC_Solution.h
 *
 *  Created on: 20-Mar-2026
 *      Author: Anamitra Sarkar
 */


#ifndef NPC_SOLUTION_H_
#define NPC_SOLUTION_H_



//
// Included Files
//

#include <power_meas_sine_analyzer.h>
#include "NPC_Hardware_Setup.h"
#include "Config.h"

#include "IQmathLib.h"
#include "DCLF32.h"
#include "spll_1ph_sogi.h"
#include "abc_dq0_pos.h"
#include "abc_dq0_neg.h"
#include "dq0_abc.h"
#include "rampgen.h"
#include "Ref_slew.h"
#include "Control_Variables.h"
#include "emavg.h"
#include <stdint.h>

//#include "REF_GEN_FUNC.h"

extern volatile Uint16 epwm8_tbprd;

extern volatile uint16_t syncIN;
extern volatile uint16_t oldSyncIN;

extern volatile float32_t TempV;
extern volatile float32_t TempI;
extern volatile float32_t TempPF;
extern volatile float32_t TempFreq;
extern volatile float32_t TempPreal;

extern volatile float32_t dividingFactor;
extern volatile float32_t dacScalingFactor;
extern volatile float32_t dacOffset;
extern volatile float32_t openLoopGain;
extern volatile uint16_t dbRampCounter_DAB;
extern volatile uint16_t dbRampCounter_INV;
extern volatile float32_t gainSlew;

extern volatile float32_t Vmon_DAC_float;
extern volatile uint16_t Vmon_DAC_count;

extern volatile uint32_t invStart;
// Testing variables
extern float32_t Vsens_grid;
extern float32_t Vsens_grid1;
extern int check2;
extern float y[2];
extern float alpha;

extern float32_t Imon;

//#define BaseLUT_SIZE    720
extern uint16_t LUT_Size;
extern uint16_t Vmon_dac_count;
extern uint16_t Imon_dac_count;
extern volatile float x1,x2,y1,y2,m,c;
extern volatile float calculated_sin_value;
extern volatile float32_t Angle_Step;
extern volatile float calculated_sin_value;

typedef enum
{
    DB_STATE_OFF = 0,
    DB_STATE_GATE_DRIVE_ON,
    DB_STATE_DAB_RAMP,
    DB_STATE_WAIT_INV_ON,
    DB_STATE_RUN1,
    DB_STATE_RUN2,
    DB_STATE_DAB_OFF,
    DB_STATE_WAIT_INV_OFF,
    DB_STATE_INV_OFF,
    DB_STATE_GATE_DRIVE_OFF
} DeadBandSeqState;
extern DeadBandSeqState DeadBandSeqState_t;
extern uint16_t InvStartDelayCounter;
extern uint16_t InvStopDelayCounter;
extern bool systemOff_Flag;

typedef union
{
    float32_t f32;
    uint16_t u16;
}f32_to_u16;


extern volatile POWER_MEAS_SINE_ANALYZER PPA_phaseA;
extern f32_to_u16 PLL_angle_DAC;

//*********************************//
//******Lode Mode variables********//
//*********************************//

//CC mode
extern float32_t phase_angle;
extern SPLL_1PH_SOGI V_line_pll;
extern SPLL_1PH_SOGI sogi_Ia;
extern float32_t Id_ref, Iq_ref;
extern float32_t i_alpha, i_beta;
extern float32_t Id_fb, Iq_fb;
extern float32_t ud_inv, uq_inv;
extern float32_t alpha_ref;
extern float32_t kpI_test, kiI_test, woI_test, wrcI_test;
extern float32_t Iset_dc;

/***********************************************
 ******Analog Prgramming & Monitoring Variables
 ***********************************************
 */

extern float32_t Vmon_5, Vmon_10, Imon_5, Imon_10;
extern float32_t Vpgm_sns, Ipgm_sns;
extern float32_t Vpgm_10, Ipgm_10;

//
// Global Variables
//
//extern float32_t Vac_fundamental;
//extern float32_t Iac_fundamental;
//extern float32_t VA_fundamental;
//extern float32_t VB_fundamental;
//extern float32_t VC_fundamental;
//extern float32_t IA_fundamental;
//extern float32_t IB_fundamental;
//extern float32_t IC_fundamental;
extern float32_t V_flicker;

extern float32_t uk_kp;
extern float32_t uk_ki;
extern float32_t Mff;

extern float32_t uk_Va;
extern float32_t uk_Vb;
extern float32_t uk_Vb1;
extern float32_t uk_Vb2;
extern float32_t uk_Vc;
extern float32_t uk_Va1,uk_Va2,uk_Va3,uk_Va4,uk_Va5,uk_Va6;
extern float32_t uk_Vb1,uk_Vb2,uk_Vb3,uk_Vb4,uk_Vb5,uk_Vb6;
extern float32_t uk_Vc1,uk_Vc2,uk_Vc3,uk_Vc4,uk_Vc5,uk_Vc6;
extern float32_t uk_Ia;
extern float32_t uk_Ib;
extern float32_t uk_Ic;
extern float32_t uk_Ia1,uk_Ia2,uk_Ia3,uk_Ia4,uk_Ia5;
extern float32_t uk_Ib1,uk_Ib2,uk_Ib3,uk_Ib4,uk_Ib5;
extern float32_t uk_Ic1,uk_Ic2,uk_Ic3,uk_Ic4,uk_Ic5;

extern float32_t sine;
extern float32_t cosine;
extern float32_t sine_A_pll;
extern float32_t sine_B_pll;
extern float32_t sine_C_pll;
extern float32_t sine_AB_pll;
extern float32_t cosine_A;
extern float32_t cosine_B;
extern float32_t cosine_C;
extern float32_t sine_A[51];
extern float32_t sine_B[51];
extern float32_t sine_C[51];
extern float32_t sine_Ref_A;
extern float32_t sine_Ref_B;
extern float32_t sine_Ref_C;
extern float32_t sine_Ref_AB;
extern float32_t harm_Ref_A;
extern float32_t harm_Ref_B;
extern float32_t harm_Ref_C;
extern float32_t sine_A_prv;
//extern float32_t v_h_A[51];
//extern float32_t v_h_B[51];
//extern float32_t v_h_C[51];
//
//extern float32_t Harm_angle_A[51];
//extern float32_t Harm_angle_B[51];
//extern float32_t Harm_angle_C[51];


//extern float32_t slope_VacRef;
//extern float32_t slope_IacRef;
extern float32_t Flicker_slope;
extern float32_t slope_VdcRef;
//extern float32_t slope_FreqRef;
extern float32_t slope_AngleRef;

extern float32_t pll_ang;
extern float32_t pll_ang_A;
extern float32_t pll_ang_A_prev;

extern float32_t pll_ang_B;
extern float32_t pll_ang_C;
extern float32_t pll_ang_AB;
extern float32_t angle_A;
extern float32_t angle_B;
extern float32_t angle_C;
extern float32_t angle_AB;

extern float32_t Ma1;
extern float32_t Mb1;
extern float32_t Mc1;
extern volatile float32_t Ma_CV;
extern volatile float32_t Ma_CV_abs;
extern volatile float32_t Ma_CV_Max;
extern volatile float32_t Ma_CC;
extern volatile float32_t Ma_CC_abs;
extern volatile float32_t Ma_CC_Max;
extern volatile float32_t Ma_CV_Peak;
extern volatile float32_t Ma_CC_Peak;
extern float32_t Ref,Ref_A,Ref_B,Ref_C;
extern float32_t Ref_arbitary_A,Ref_arbitary_B,Ref_arbitary_C;
extern float32_t ka,kb,kc,ka,kb,kc,kdc1,kdc2,kdc3,kac1,kac2,kac3;
extern float32_t Ma_new;
extern float32_t Mb_new;
extern float32_t Mc_new;
extern float32_t Mcm;
extern float32_t M_alpha;
extern float32_t M_beta;
extern float32_t max_val;
extern float32_t min_val;

extern float32_t Va_fb;
extern float32_t Va_fb_old;

extern float32_t Vb_fb;
extern float32_t Vc_fb;
extern float32_t Va_fb_pu;
extern float32_t Vb_fb_pu;
extern float32_t Vc_fb_pu;

extern float32_t Vac_fb_pu;


extern float32_t Ia_fb;

extern float32_t I_fb[2];

extern float32_t scale;
extern float32_t Ib_fb;
extern float32_t Ic_fb;

extern float32_t Vc1_fb;

extern float32_t Ia_ref;
extern float32_t Ib_ref;
extern float32_t Ic_ref;
extern float32_t Va_ref;
extern float32_t Vb_ref;
extern float32_t Vc_ref;
extern float32_t Vdc_ref_A,Vdc_ref_B,Vdc_ref_C;
extern float32_t Idc_ref_A,Idc_ref_B,Idc_ref_C;
extern float32_t Va_ref1,Vb_ref1,Vc_ref1;
extern float32_t Ia_ref1,Ib_ref1,Ic_ref1;
extern float32_t err_VA;
extern float32_t err_VB;
extern float32_t err_VC;
extern float32_t err_IA;
extern float32_t err_IB;
extern float32_t err_IC;
extern float32_t vc1_fb;
extern float32_t vc2_fb;
//extern float32_t Vdc_fb;
extern float32_t Vdc_fb_flt;
extern float32_t vc1_fb_flt;
extern float32_t vc2_fb_flt;
extern float32_t vdc_fb_flt;
extern float32_t Va_fb_prev;
extern float32_t Vb_fb_prev;
extern float32_t Vc_fb_prev;

extern float32_t VdcRefSlewed;
extern float32_t VacRefSlewed;
extern float32_t VA_RefSlewed;
extern float32_t VB_RefSlewed;
extern float32_t VC_RefSlewed;
extern float32_t Vdc_RefSlewed;
extern float32_t IA_RefSlewed;
extern float32_t IB_RefSlewed;
extern float32_t IC_RefSlewed;
extern float32_t Idc_RefSlewed;
extern float32_t ImaxRefSlewed;

extern float32_t TEMP_A_fb;
extern float32_t Va_sns;

extern float32_t Va_sns1;
extern float32_t Va_sns2;


extern float32_t Vb_sns;
extern float32_t Vc_sns;
extern float32_t Ia_sns;
extern float32_t Ib_sns;
extern float32_t Ic_sns;
extern float32_t Ia_sns_flt;
extern float32_t Ib_sns_flt;
extern float32_t Ic_sns_flt;
extern float32_t Vc1_sns;
extern float32_t Vc2_sns;
extern float32_t TEMP_A_sense;

extern uint32_t dutyA_S1_Ref;
extern uint32_t dutyA_S2_Ref;
extern uint32_t dutyB_S1_Ref;
extern uint32_t dutyB_S2_Ref;
extern uint32_t dutyC_S1_Ref;
extern uint32_t dutyC_S2_Ref;
extern uint32_t dutyN_S1_Ref;
extern uint32_t dutyE_S1_Ref;                                  // Newly added variables for 3 bridge project
extern uint32_t dutyF_S1_Ref;                                  // Newly added variables for 3 bridge project  {need to transfer during code transfer]

extern float32_t DeadBand_INV;
extern float32_t DeadBand_DAB;
extern float32_t DeadBand;

extern float32_t duty_fan1;

//extern volatile int32_t StartPowerStage;
extern volatile int32_t clearPWMTrips;
extern volatile int32_t close_CurrentLoop;
extern volatile int32_t close_VoltageLoop;
extern volatile int32_t CC_Flag;
extern volatile int32_t CV_Flag;

//extern volatile int32_t OutputMode;                                              // Recently added to be updated


extern volatile int32_t firstTimeVoltageLoop;
extern volatile int32_t AC_OverVoltage_Trip;
extern volatile int32_t AC_UnderVoltage_Trip;
extern volatile int32_t PFC_RDY;
extern volatile int32_t test_variable;
extern volatile int16_t startFault_VoltageDip ;
extern volatile int16_t startFault_FreqVary;
extern volatile int16_t startFault_Flicker;
extern volatile int16_t start_fault_timer;
extern float32_t fault_timer;

extern Ref_Slew_Ramp VA_RefSlewRamp;
extern Ref_Slew_Ramp VB_RefSlewRamp;
extern Ref_Slew_Ramp VC_RefSlewRamp;
extern Ref_Slew_Ramp VacRefSlewRamp;
extern Ref_Slew_Ramp IacRefSlewRamp;
extern Ref_Slew_Ramp IA_RefSlewRamp;
extern Ref_Slew_Ramp IB_RefSlewRamp;
extern Ref_Slew_Ramp IC_RefSlewRamp;
extern Ref_Slew_Ramp VdcRefSlewRamp;
extern Ref_Slew_Ramp Idc_RefSlewRamp;
extern Ref_Slew_Ramp FreqRefSlewRamp;
extern Ref_Slew_Ramp FreqRefSlewRamp_A;
extern Ref_Slew_Ramp FreqRefSlewRamp_B;
extern Ref_Slew_Ramp FreqRefSlewRamp_C;
extern Ref_Slew_Ramp AngleRefSlewRamp_A;
extern Ref_Slew_Ramp AngleRefSlewRamp_B;
extern Ref_Slew_Ramp AngleRefSlewRamp_C;
extern Ref_Slew_Ramp FlickerRefSlewRamp;

extern RAMP theta;
extern RAMP theta_A;
extern RAMP theta_B;
extern RAMP theta_C;
extern RAMP theta_flicker;

extern DQ0_ABC Mabc;
extern float32_t Md;
extern float32_t Mq;


extern float32_t h;
extern float32_t f;
extern float32_t g1;
extern float32_t g2;

extern int32_t Relay_state;
extern int32_t OverCurrent_Flag;
extern float32_t FAN_FB_PRD;
extern float32_t FAN_SPEED;

//extern volatile float32_t AC_Freq_Ref;
//extern volatile float32_t AC_Freq_Ref_A;
//extern volatile float32_t AC_Freq_Ref_B;
//extern volatile float32_t AC_Freq_Ref_C;
extern volatile float32_t Angle_Ref_A;
extern volatile float32_t Angle_Ref_B;
extern volatile float32_t Angle_Ref_C;
extern volatile float32_t Grid_max_freq;
extern volatile float32_t Grid_min_freq;

//extern volatile float32_t VAR_Freq_Ref_C;
//extern volatile float32_t VAR_Freq_Ref_B;
//extern volatile float32_t VAR_Freq_Ref_A;

//
//power measurement related
//
//extern POWER_MEAS_SINE_ANALYZER Phase_A;
//extern POWER_MEAS_SINE_ANALYZER Phase_B;
//extern POWER_MEAS_SINE_ANALYZER Phase_C;
//extern POWER_MEAS_SINE_ANALYZER DC_OutPut;


extern float32_t VGridRms_A;
extern float32_t VGridRms_B;
extern float32_t VGridRms_C;
extern float32_t ICONVRms_A;
extern float32_t ICONVRms_B;
extern float32_t ICONVRms_C;
extern float32_t ICONVRms_N;
extern float32_t ICONV_peak_A;
extern float32_t ICONV_peak_B;
extern float32_t ICONV_peak_C;
extern float32_t Imax;
extern float32_t Vdc_link;
extern float32_t Idc_link;

// power measurement variables
extern float32_t gridFreq_Hz;
extern float32_t gridFreq_Hz_A;
extern float32_t gridFreq_Hz_B;
extern float32_t gridFreq_Hz_C;
//extern float32_t powerRms_A_Watts;
//extern float32_t powerRms_B_Watts;
//extern float32_t powerRms_C_Watts;
//extern float32_t powerRmsTotal_Watts;
//extern float32_t poweroutputTotal_Watts;
//extern float32_t powerFactor_A;
//extern float32_t powerFactor_B;
//extern float32_t powerFactor_C;
extern float32_t P_out_apparent;
extern float32_t effeciency;

extern volatile float32_t activePower;
extern volatile float32_t reactivePower;
extern volatile float32_t activePowerFilt;
extern volatile float32_t reactivePowerFilt;
extern float32_t PPA_FreqAvg;

extern volatile int32_t aux_isrTicker,aux_isrTicker1,aux_isrTicker2;
extern int16_t vTimer0[4];

//
// pr_controller instances
//

typedef struct  {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t x1;   //!< x1
    float32_t x2;   //!< x2
} PR_Custom_DF22;


/*
 * PI controller instances
 */

typedef struct {
    float32_t Kp;
    float32_t Ki;
    float32_t i10;  //  integrator
    float32_t Umax;
    float32_t Umin;
    float32_t i6;   // integrator enable (1 = on, 0 = hold)
} PI_Custom;

extern PI_Custom pi_I_inv;
extern PI_Custom pi_Id_inv;
extern PI_Custom pi_Iq_inv;

//default values to initialize the PI structure
#define Custom_PI_DEFAULTS { 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f }

//! \brief          Defines default values to initialize the DCL_DF22 structure
//!
#define Custom_DF22_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}






extern PR_Custom_DF22 Testg1; //Testing 1 phase INV
extern PR_Custom_DF22 Testg2;
extern PR_Custom_DF22 dutynotch;
extern PR_Custom_DF22 dutynotch1;

// voltage controller PhaseA
extern PR_Custom_DF22 gi_pr1_A;
extern PR_Custom_DF22 gi_r3_A;
extern PR_Custom_DF22 gi_r5_A;
extern PR_Custom_DF22 gi_r7_A;
extern PR_Custom_DF22 gi_r9_A;
extern PR_Custom_DF22 gi_r11_A;
extern PR_Custom_DF22 gi_lead_lag_A;
// voltage controller PhaseB
extern PR_Custom_DF22 gi_pr1_B;
extern PR_Custom_DF22 gi_r3_B;
extern PR_Custom_DF22 gi_r5_B;
extern PR_Custom_DF22 gi_r7_B;
extern PR_Custom_DF22 gi_r9_B;
extern PR_Custom_DF22 gi_r11_B;
extern PR_Custom_DF22 gi_lead_lag_B;
// voltage controller PhaseC
extern PR_Custom_DF22 gi_pr1_C;
extern PR_Custom_DF22 gi_r3_C;
extern PR_Custom_DF22 gi_r5_C;
extern PR_Custom_DF22 gi_r7_C;
extern PR_Custom_DF22 gi_r9_C;
extern PR_Custom_DF22 gi_r11_C;
extern PR_Custom_DF22 gi_lead_lag_C;

// current controller PhaseA
extern PR_Custom_DF22 gv_pr1_A;
extern PR_Custom_DF22 gv_r3_A;
extern PR_Custom_DF22 gv_r5_A;
extern PR_Custom_DF22 gv_r7_A;
extern PR_Custom_DF22 gv_r9_A;
extern PR_Custom_DF22 gv_r11_A;
// current controller PhaseB
extern PR_Custom_DF22 gv_pr1_B;
extern PR_Custom_DF22 gv_r3_B;
extern PR_Custom_DF22 gv_r5_B;
extern PR_Custom_DF22 gv_r7_B;
extern PR_Custom_DF22 gv_r9_B;
extern PR_Custom_DF22 gv_r11_B;
// current controller PhaseC
extern PR_Custom_DF22 gv_pr1_C;
extern PR_Custom_DF22 gv_r3_C;
extern PR_Custom_DF22 gv_r5_C;
extern PR_Custom_DF22 gv_r7_C;
extern PR_Custom_DF22 gv_r9_C;
extern PR_Custom_DF22 gv_r11_C;


// DC Mode
extern DCL_PI pi_Va;
extern DCL_PI pi_Vb;
extern DCL_PI pi_Vc;
extern DCL_PI pi_Ia;
extern DCL_PI pi_Ib;
extern DCL_PI pi_Ic;

//
// for tuning PR controllers
//
extern float32_t kpI_1H;
extern float32_t kiI_1H, kiI_3H, kiI_5H, kiI_7H, kiI_9H;
extern float32_t woI_1H, woI_3H, woI_5H, woI_7H, woI_9H;
extern float32_t wrcI_1H, wrcI_3H, wrcI_5H, wrcI_7H, wrcI_9H;

extern float32_t kpV_1H;
extern float32_t kiV_1H, kiV_3H, kiV_5H, kiV_7H, kiV_9H;
extern float32_t woV_1H, woV_3H, woV_5H, woV_7H, woV_9H;
extern float32_t wrcV_1H, wrcV_3H, wrcV_5H, wrcV_7H, wrcV_9H;
//
// Transformation & PLL instances
//
extern SPLL_1PH_SOGI spll_A;
extern SPLL_1PH_SOGI spll_B;
extern SPLL_1PH_SOGI spll_C;

extern SPLL_1PH_SOGI spll_line;


// auto start variables
typedef union{
    enum
    {
        systemState_waitForDCVoltage = 0,
        systemState_InverterON = 1,
        systemState_normalOperation = 2,
        systemState_InverterOFF =3,
        systemState_INV_Overcurrent = 4,
        systemState_dclinkovervoltage = 5,
        systemState_dclinkundervoltage = 6,
        systemState_DESAT = 7,
    }enum_systemState;
    int32_t pad;
}NPC_systemState;
extern NPC_systemState NPC_system_state;



//
//Notch filter instances
//
extern DCL_DF22 NPC_notch_A1,NPC_notch_A2,NPC_notch_A3,NPC_notch_A4,NPC_notch_A5,NPC_notch_A6,NPC_notch_A7,NPC_notch_A8,NPC_notch_A9,NPC_notch_A10;
extern DCL_DF22 NPC_notch_A11,NPC_notch_A12,NPC_notch_A13,NPC_notch_A14,NPC_notch_A15,NPC_notch_A16,NPC_notch_A17,NPC_notch_A18,NPC_notch_A19,NPC_notch_A20;

extern float32_t Notch_freq;

extern DCL_DF22 NPC_notch_B1,NPC_notch_B2,NPC_notch_B3,NPC_notch_B4,NPC_notch_B5,NPC_notch_B6,NPC_notch_B7,NPC_notch_B8,NPC_notch_B9,NPC_notch_B10;
extern DCL_DF22 NPC_notch_B11,NPC_notch_B12,NPC_notch_B13,NPC_notch_B14,NPC_notch_B15,NPC_notch_B16,NPC_notch_B17,NPC_notch_B18,NPC_notch_B19,NPC_notch_B20;

extern DCL_DF22 NPC_notch_C1,NPC_notch_C2,NPC_notch_C3,NPC_notch_C4,NPC_notch_C5,NPC_notch_C6,NPC_notch_C7,NPC_notch_C8,NPC_notch_C9,NPC_notch_C10;
extern DCL_DF22 NPC_notch_C11,NPC_notch_C12,NPC_notch_C13,NPC_notch_C14,NPC_notch_C15,NPC_notch_C16,NPC_notch_C17,NPC_notch_C18,NPC_notch_C19,NPC_notch_C20;

extern float32_t v_h[51];

extern DCL_DF22 NPC_notch_A_arb_freq,NPC_notch_B_arb_freq,NPC_notch_C_arb_freq;

//
// the function prototypes
//
extern void NPC_globalVariablesInit(void);
extern void NPC_autoStart_INVERTER(void);
extern void NPC_Reset_INV(void);
extern void computeDF22_PRcontrollerCoeff_1(PR_Custom_DF22 *v, float32_t kp, float32_t ki, float32_t wo,
                                   float32_t fs, float32_t wrc);
extern void computeDF22_PRcontrollerCoeff_2(PR_Custom_DF22 *v, float32_t kp, float32_t ki, float32_t wo,
                                   float32_t fs, float32_t wrc);

extern void NPC_computeNotchFltrCoeff(PR_Custom_DF22 *coeff, float32_t Fs, float32_t notch_freq,
                                      float32_t c1, float32_t c2);

// fan
extern float32_t current_flt;
extern float32_t duty_fan;

//
// programmable impedence
//
extern float32_t Za_va,Za_vb,Za_vc;
extern float32_t Za_Ia,Za_Ib,Za_Ic;

extern float32_t sine_arbitary_A,sine_arbitary_B,sine_arbitary_C;
extern volatile float32_t clip_A,clip_B,clip_C;

extern EMAVG vout;
extern EMAVG Vdc_out;
//
// ADC read function
//

extern float32_t Vgrid_Sense_scaling, Vgrid_sense_offset_A;     //0.222911585f//(for 143K divider)//0.37262f//(for 127K divider)//(REF3.0V[working in 12-bit])0.013928785f /*16-bit*/ // //0.245202744f(REF3.3V)




#pragma FUNC_ALWAYS_INLINE(NPC_readCurrentAndVoltageSignals)
static inline void NPC_readCurrentAndVoltageSignals(void)    // AC AND DC VOLTAGE AND CURRENT SENSING.
{
    Ia_sns = (float)((AdcaResultRegs.ADCRESULT0 + AdcaResultRegs.ADCRESULT1 + AdcaResultRegs.ADCRESULT2 + AdcaResultRegs.ADCRESULT3)*0.25f);
    Ia_fb =((float)Ia_sns - Iconv_sense_offset_A)*Iconv_Sense_scaling;
    PPA_phaseA.i = Ia_fb;


    Va_sns = (float)((AdcaResultRegs.ADCRESULT4 + AdcaResultRegs.ADCRESULT5 + AdcaResultRegs.ADCRESULT6 + AdcaResultRegs.ADCRESULT7)*0.25f);
//    Va_fb =((float)Va_sns - Vgrid_sense_offset_A)*Vgrid_Sense_scaling;
    Va_fb =( ((float)Va_sns * Vgrid_Sense_scaling) + Vgrid_sense_offset_A);
    PPA_phaseA.v = Va_fb;

    Vac_fb_pu = ((float)Va_sns - Vgrid_sense_offset_A)*Vgrid_Sense_scaling_PU;


    Vc1_sns = (float)((AdcaResultRegs.ADCRESULT8 + AdcaResultRegs.ADCRESULT9 + AdcaResultRegs.ADCRESULT10 + AdcaResultRegs.ADCRESULT11)*0.25f);
    vc1_fb = ((float)(Vc1_sns - VDC_sense_offset) * Vdc1_Sense_scaling);

    EMAVG_MACRO(vc1_fb, vc2_fb, 0.9875);
    Vdc_link = (2.0f*vc2_fb);



    POWER_MEAS_SINE_ANALYZER_run(&PPA_phaseA, AC_Freq_Ref);
//    Meas_Vrms = TempV;
//    Meas_Irms = TempI;
//    Meas_PF = TempPF;
//    Meas_Freq = TempFreq;
//    Meas_Preal = TempPreal;

    Meas_Vrms =  PPA_phaseA.v_trueRMS;
    Meas_Irms = PPA_phaseA.i_AC_RMS;
    Meas_PF = PPA_phaseA.powerFactor;
    Meas_Freq = PPA_phaseA.freq_Hz_filt;
    Meas_Preal = PPA_phaseA.activePower;
    Meas_Vdc = PPA_phaseA.v_DC;
    Meas_Idc = PPA_phaseA.i_DC;
    Meas_Vpk_P = PPA_phaseA.V_POS_PK;
    Meas_Vpk_N = PPA_phaseA.V_NEG_PK;
    Meas_Ipk_P = PPA_phaseA.I_POS_PK;
    Meas_Ipk_N = PPA_phaseA.I_NEG_PK;

    /* Voltage Crest Factor */
    if (PPA_phaseA.v_trueRMS > 0.001f)
    {
        float32_t Vpeak;
        Vpeak = fmaxf(fabsf(PPA_phaseA.V_POS_PK), fabsf(PPA_phaseA.V_NEG_PK));
        Meas_V_CF = Vpeak / PPA_phaseA.v_trueRMS;
    }
    else
    {
        Meas_V_CF = 0.0f;
    }


    /* Current Crest Factor */
    if (PPA_phaseA.i_AC_RMS > 0.001f)
    {
        float32_t Ipeak;
        Ipeak = fmaxf(fabsf(PPA_phaseA.I_POS_PK),fabsf(PPA_phaseA.I_NEG_PK));
        Meas_I_CF = Ipeak / PPA_phaseA.i_AC_RMS;
    }
    else
    {
        Meas_I_CF = 0.0f;
    }

    Va_fb_prev = Va_fb_pu;
    Va_fb_pu =((float)Va_sns - Vgrid_sense_offset)*Vgrid_Sense_scaling_PU;


//    if(masterFlag)
//    {
//        if(check_PFC_Boost_Status()) ACfail = 1U;
//        else ACfail = 0U;
//    }


    //DC link voltage sensing//
//     Vc1_sns = (float)((AdccResultRegs.ADCRESULT0 + AdccResultRegs.ADCRESULT1 + AdccResultRegs.ADCRESULT2 + AdccResultRegs.ADCRESULT3)*0.25f);
//     Vdc_fb =((float)(Vc1_sns)*Vdc_Sense_scaling);

    Vpgm_sns = (float)((AdccResultRegs.ADCRESULT0 + AdccResultRegs.ADCRESULT1 + AdccResultRegs.ADCRESULT2 + AdccResultRegs.ADCRESULT3)*0.25f);

    Ipgm_sns = (float)((AdcbResultRegs.ADCRESULT0 + AdcbResultRegs.ADCRESULT1 + AdcbResultRegs.ADCRESULT2 + AdcbResultRegs.ADCRESULT3)*0.25f);

    /* IP 10V = count 3411, 5V = 2631, 0= 1852, -5v = 1072, -10v = 290 */


   Vpgm_10 = (0.0064082f * Vpgm_sns) - 11.85837f;

   Ipgm_10 = (float) (0.0064082f * Ipgm_sns) - 11.85837f;
   //Vpgm_10 = (float) (Vpgm_sns/4095.0f)*3.0f;

   /*
    *
    */

}

//
// overBus voltage detect function
//
#pragma FUNC_ALWAYS_INLINE(NPC_filterAndCheckForBusOverVoltage)
static inline void NPC_filterAndCheckForBusOverVoltage(void)   // DC-LINK OVERVOLTAGE
{
    EMAVG_MACRO(vc1_fb, vc1_fb_flt, 0.9875);
    EMAVG_MACRO(vc2_fb, vc2_fb_flt, 0.9875);
    vdc_fb_flt = (float)(vc1_fb_flt + vc2_fb_flt);

    if((vc1_fb_flt > VBUS_OVERVOLT_LIMIT) || (vc2_fb_flt > VBUS_OVERVOLT_LIMIT))  // 400V + 400V
    {
        NPC_HAL_ForceOSTEVENTtoALLEPWM();
        NPC_system_state.enum_systemState = systemState_dclinkovervoltage;   // AUTO-START FUNCTION.
    }
}

//
//fan duty function
//
static inline void NPC_Calculate_Fan_duty(float32_t current)
{
    EMAVG_MACRO(current,current_flt,0.9875);     // moving average filter
    duty_fan = 0.05f + (float)(current_flt*(0.75f/50.0f));
}

//
//Custom PR Controller
//
static inline float32_t runPR_custom(PR_Custom_DF22 *p, float32_t ek)
{
    float32_t v7;

    v7 = (ek * p->b0) + p->x1;
    p->x1 = (ek * p->b1) + p->x2 - (v7 * p->a1);
    p->x2 = (ek * p->b2) - (v7 * p->a2);

    return(v7);
}

static inline float32_t resetPR_custom(PR_Custom_DF22 *p)
{
    p->b0 = 1;
    p->b1 = 0;
    p->b2 = 0;
    p->a1 = 0;
    p->a2 = 0;
    p->x1 = 0;
    p->x2 = 0;
}

/*
static inline void runPR_custom_reset(PR_Custom_DF22 *p)
{
    uint16_t v;

     __disable_interrupts();

    p->x1 = p->x2 = 0.0f;

    __enable_interrupts();
}
*/


static inline float32_t runPI_Custom(PI_Custom *p, float32_t rk , float32_t yk )
{
    float32_t v1, v2, v4, v5, v9;
     v1 = rk - yk;                         // error
//    v1 = rk + yk;
     v2 = p->Kp * v1;                      // proportional term
     v4 = (v1 * p->Ki * p->i6) + p->i10; // integrator update
     p->i10 = v4;
     v5 = v2 + v4;                         // control effort
     v9 = (v5 > p->Umax) ? p->Umax : v5;
     v9 = (v9 < p->Umin) ? p->Umin : v9;
     p->i6 = (v5 == v9) ? 1.0f : 0.0f;     // anti-windup gate

     return(v9);
}

static inline void resetPI_Custom(PI_Custom *p)
{
    p->i10 = 0.0f;
    p->i6 = 1.0f;
}


static inline void NPC_run_internal_PLL(void)
{
    float32_t ang_diff;

    REFslew_run(&FreqRefSlewRamp_A,(AC_Freq_Ref),slope_FreqRef);
    RAMP_run(&theta_A,FreqRefSlewRamp_A.out_slew,ISR_FREQUENCY);
    pll_ang_A = (float32_t)(theta_A.out*2*PI);

//    if(pll_ang_A > pll_ang_A_prev)
//    {
//        ang_diff = pll_ang_A - pll_ang_A_prev;
//    }
//    else
//    {
//        ang_diff = ((float32_t)2*PI - pll_ang_A_prev) + pll_ang_A;
//    }
//    float32_t Meas_Freq_radSec = (ang_diff / (float32_t)T_switching);
//
//    if(StartPowerStage == 1)
//    {
//        Meas_Freq = Meas_Freq_radSec / ((float32_t)2*PI);
//    }
//    else
//    {
//        Meas_Freq = 0.0f;
//    }
//
//    pll_ang_A_prev = pll_ang_A;

    // angle ramp
    REFslew_run(&AngleRefSlewRamp_A,Angle_Ref_A*(PI/180),AngleRefSlope);
    angle_A = (float32_t)(AngleRefSlewRamp_A.out_slew);  // PHASE ANGLES 0 120 240.

}

static inline void NPC_run_SOGI_PLL(void)
{
    SPLL_1PH_SOGI_run(&spll_A, Va_fb_pu);
    SPLL_1PH_SOGI_run(&spll_B, Vb_fb_pu);
    SPLL_1PH_SOGI_run(&spll_C, Vc_fb_pu);
    sine_A_pll = spll_A.sine;
    sine_B_pll = spll_B.sine;
    sine_C_pll = spll_C.sine;

    sine_AB_pll = (float32_t)(sine_A_pll - sine_B_pll) *0.57735;  // working

    pll_ang_A = spll_A.theta[1];  // return theta from 0 to 2*pi
    pll_ang_B = spll_B.theta[1];
    pll_ang_C = spll_C.theta[1];
    pll_ang_AB = (float32_t)(sine_A_pll - sine_B_pll) *0.57735;

    REFslew_run(&AngleRefSlewRamp_A,Angle_Ref_A*(PI/180),AngleRefSlope);
    angle_A = (float32_t)(AngleRefSlewRamp_A.out_slew);
    angle_B = angle_A;  // used in harmonic generation
    angle_C = angle_A;
}

//
//MAX&MIN functions
//
static inline void MAX_MIN_function(float32_t Ma,float32_t Mb,float32_t Mc)
{
    //Max function
    if(Ma>=Mb)
    {
        if(Ma>=Mc)
        {
            max_val = Ma;
        }
        else
        {
            max_val = Mc;
        }
    }
    else
    {
        if(Mb>=Mc)
        {
            max_val = Mb;
        }
        else
        {
            max_val = Mc;
        }
    }

    //Min function
    if(Ma<=Mb)
    {
        if(Ma<=Mc)
        {
            min_val = Ma;
        }
        else
        {
            min_val = Mc;
        }
    }
    else
    {
        if(Mb<=Mc)
        {
            min_val = Mb;
        }
        else
        {
            min_val = Mc;
        }
    }
}

//
// duty function
//
#pragma FUNC_ALWAYS_INLINE(NPC_Calculate_duty)


static inline void NPC_Calculate_duty(float32_t Ma,float32_t Mb,float32_t Mc)
{

//    Ma = (Ma > 1.154f) ? 1.154f : Ma;   // ? FOR IF CONDITION
//    Ma = (Ma < -1.154f) ? -1.154f : Ma;
//
//    Mb = (Mb > 1.154f) ? 1.154f : Mb;
//    Mb = (Mb < -1.154f) ? -1.154f : Mb;
//
//    Mc = (Mc > 1.154f) ? 1.154f : Mc;
//    Mc = (Mc < -1.154f) ? -1.154f : Mc;
//
//
//    MAX_MIN_function(Ma,Mb,Mc);
//    Mcm = (float)(-0.5*(max_val + min_val));  // MODULATION INDEX FOR 4TH LEG OR NEUTRAL LEG.
//
//    Mcm = (Mcm > 1.0f) ? 1.0f : Mcm;
//    Mcm = (Mcm < -1.0f) ? -1.0f : Mcm;
//
//    Ma_new = (float)(Ma + Mcm);
//    Mb_new = (float)(Mb + Mcm);
//    Mc_new = (float)(Mc + Mcm);
//
//    //
//    //Limit the New modulating signals between -1.0 to 1.0
//    //
//    Ma_new = (Ma_new > 1.0f) ? 1.0f : Ma_new;
//    Ma_new = (Ma_new < -1.0f) ? -1.0f : Ma_new;
//
//    Mb_new = (Mb_new > 1.0f) ? 1.0f : Mb_new;
//    Mb_new = (Mb_new < -1.0f) ? -1.0f : Mb_new;
//
//    Mc_new = (Mc_new > 1.0f) ? 1.0f : Mc_new;
//    Mc_new = (Mc_new < -1.0f) ? -1.0f : Mc_new;

    Ma = (Ma > 1.0f) ? 1.0f : Ma;   // ? FOR IF CONDITION
    Ma = (Ma < -1.0f) ? -1.0f : Ma;

    Mb = (Mb > 1.0f) ? 1.0f : Mb;
    Mb = (Mb < -1.0f) ? -1.0f : Mb;

    Mc = (Mc > 1.0f) ? 1.0f : Mc;
    Mc = (Mc < -1.0f) ? -1.0f : Mc;

    //INV_A_Duty
    dutyA_S1_Ref = (uint32_t) ((float32_t) ((1-Ma)*0.5f*TimeBase));   // TimeBASE = TBPRD.
    dutyB_S1_Ref = (uint32_t) ((float32_t) ((1+Ma)*0.5f*TimeBase));

    //INV_B_Duty
    dutyC_S1_Ref = (uint32_t) ((float32_t) ((1+Mb)*0.5f*TimeBase));
    dutyN_S1_Ref = (uint32_t) ((float32_t) ((1-Mb)*0.5f*TimeBase));

    //INV_C_Duty
    dutyE_S1_Ref = (uint32_t) ((float32_t) ((1+Mc)*0.5f*TimeBase));
    dutyF_S1_Ref = (uint32_t) ((float32_t) ((1-Mc)*0.5f*TimeBase));

}

static inline void NPC_Calculate_TotemPole_Inverter_Duty(float32_t Ma)
{
    float32_t m_abs;
    float32_t hf_leg_duty;

    /*
     * Limit modulation index
     * Keep small margin to avoid 0% / 100% duty edge problems
     */
    if(Ma > 0.98f)
    {
        Ma = 0.98f;
    }
    else if(Ma < -0.98f)
    {
        Ma = -0.98f;
    }

    m_abs = fabsf(Ma);

    /*
     * Your present AQ setting:
     *
     * AQCTLA.CAU = AQ_SET
     * AQCTLA.CAD = AQ_CLEAR
     *
     * So actual duty is approximately:
     *
     * Actual PWM duty = 1 - CMPA / TBPRD
     */

    if(m_abs <= 0.06f)
    {
        EPwm2Regs.AQCSFRC.bit.CSFA = AQ_NO_ACTION;
        EPwm2Regs.AQCSFRC.bit.CSFB = AQ_NO_ACTION;

        dutyA_S1_Ref = (uint32_t)(((1.0f - Ma) * 0.5f * (float32_t)TimeBase));
        dutyB_S1_Ref = (uint32_t)(((1.0f + Ma) * 0.5f * (float32_t)TimeBase));

    }

    else if(Ma > 0.0f)
    {
        /*
         * Positive half cycle
         *
         * EPWM2 low-frequency leg is clamped LOW.
         * EPWM1 high-frequency leg generates positive sine PWM.
         *
         * Required EPWM1 actual duty = |Ma|
         * Since actual duty = 1 - CMPA/TBPRD:
         *
         * CMPA = (1 - |Ma|) * TimeBase
         */
        hf_leg_duty = m_abs;

        dutyA_S1_Ref = (uint32_t)((1.0f - hf_leg_duty) * (float32_t)TimeBase);

        /*
         * EPWM2 low-frequency leg:
         * Force EPWM2A LOW, EPWM2B HIGH
         */
        EPwm2Regs.AQCSFRC.bit.CSFA = AQ_CLEAR;
        EPwm2Regs.AQCSFRC.bit.CSFB = AQ_SET;

        dutyB_S1_Ref = (uint32_t)(0.5f * (float32_t)TimeBase);

    }
    else
    {
        /*
         * Negative half cycle
         *
         * EPWM2 low-frequency leg is clamped HIGH.
         * EPWM1 high-frequency leg generates inverse sine PWM.
         *
         * Required EPWM1 actual duty = 1 - |Ma|
         * Since actual duty = 1 - CMPA/TBPRD:
         *
         * CMPA = |Ma| * TimeBase
         */
        hf_leg_duty = 1.0f - m_abs;

        dutyA_S1_Ref = (uint32_t)((1.0f - hf_leg_duty) * (float32_t)TimeBase);

        /*
         * EPWM2 low-frequency leg:
         * Force EPWM2A HIGH, EPWM2B LOW
         */
        EPwm2Regs.AQCSFRC.bit.CSFA = AQ_SET;
        EPwm2Regs.AQCSFRC.bit.CSFB = AQ_CLEAR;

        dutyB_S1_Ref = (uint32_t)(0.5f * (float32_t)TimeBase);
    }


    /*
     * Keep DAB bridge constant duty.
     * EPWM3, EPWM4, EPWM5, EPWM6 untouched.
     */
    dutyC_S1_Ref = (uint32_t)(0.5f * (float32_t)TimeBase);
    dutyN_S1_Ref = (uint32_t)(0.5f * (float32_t)TimeBase);
    dutyE_S1_Ref = (uint32_t)(0.5f * (float32_t)TimeBase);
    dutyF_S1_Ref = (uint32_t)(0.5f * (float32_t)TimeBase);
}

static inline float GetInterpolatedSinFromLUT(
        float radian_input, int x)      // PI_Radian_Value_from_Subhasis)
{
    float temp;
    uint16_t Array_Position;

    float x1, x2;
    float y1, y2;
    float m, c;
//    float calculated_sin_value;

    if(radian_input>=6.283)
    {
        radian_input = radian_input - TWO_PI;
    }

    else if(radian_input < 0)
    {
        radian_input = radian_input + TWO_PI;
    }



//    while(radian_input >= TWO_PI)
//    {
//        radian_input -= TWO_PI;
//    }
//
//    while(radian_input < 0.0f)
//    {
//        radian_input += TWO_PI;
//    }




    /* Find LUT position */
    temp = radian_input / Angle_Step;
    Array_Position = (uint16_t)(temp);

    /* Boundary protection */
    if(Array_Position >= (LUT_Size - 1U))
    {
        Array_Position = LUT_Size - 2U;
    }

    /* X coordinates in radians */
    x1 = (float)Array_Position * Angle_Step;
    x2 = (float)(Array_Position + 1U) * Angle_Step;

    /* Y coordinates from Q15 LUT */
    if(x == 0)
    {
        y1 = (float)BaseLUT_A[Array_Position];
        y2 = (float)BaseLUT_A[Array_Position + 1U];
    }
    else if(x == 1)
    {
        y1 = (float)BaseLUT_B[Array_Position];
        y2 = (float)BaseLUT_B[Array_Position + 1U];
    }
    else if(x == 2)
    {
        y1 = (float)BaseLUT_C[Array_Position];
        y2 = (float)BaseLUT_C[Array_Position + 1U];
    }
    else{}

    /* Line equation parameters */
    m = (y2 - y1) / (x2 - x1);
    c = y1 - (m * x1);

    /* Interpolated sine value */
    calculated_sin_value = (m * radian_input) + c;

    /* Normalize Q15 to float (-1 to +1) */
    calculated_sin_value = calculated_sin_value / 32767.0f;

    return calculated_sin_value;
}


static inline void Ref_Gen_function(void)
{

   float32_t angle_cal;

//        sine_A[1]      = (float)(sinf(pll_ang_A));
//        sine_B[1]      = (float)(sinf(pll_ang_A + 2.094f )); /**/
//        sine_C[1]      = (float)(sinf(pll_ang_A - 2.094f  )); /* angle_C*/


    if(masterFlag)
    {
        angle_cal = pll_ang_A;

        if(angle_cal>=0 && angle_cal<(PI/2.0f))
        {
            GPIO_WritePin(14, 1);
        }
        else
        {
            GPIO_WritePin(14, 0);
        }
        Ref_A = GetInterpolatedSinFromLUT(angle_cal,0);
    }
    else if(Slave1Flag)
    {
        syncIN = GPIO_readPin(29);

        if(syncIN ==1 && oldSyncIN==0)
        {
            GPIO_WritePin(14, 1);
            RAMP_reset(&theta_A);
        }
        else
        {
            GPIO_WritePin(14, 0);
        }

        oldSyncIN = syncIN;

        angle_cal = pll_ang_A + 2.094f;
        Ref_A = GetInterpolatedSinFromLUT(angle_cal,0);
    }

    else if(Slave2Flag)
    {
        syncIN = GPIO_readPin(29);

        if(syncIN ==1 && oldSyncIN==0)
        {
            GPIO_WritePin(14, 1);
            RAMP_reset(&theta_A);
        }
        else
        {
            GPIO_WritePin(14, 0);
        }

        oldSyncIN = syncIN;


        angle_cal = pll_ang_A - 2.094f;
        Ref_A = GetInterpolatedSinFromLUT(angle_cal,0);
    }


 //  Ref_A = (float)(sinf(pll_ang_A));

}


//
// select CC or CV loop ; balanced/ unbalanced from project defines.h file
// after selecting mode of operation make StartPowerStage = 1 from watch window
// give reference voltage using variable Vac_fundamental and reference current using variable Iac_fundamental
//

///////// ON OFF and modes are done needs to be tested at power and output off at 2

static inline float32_t toRadian(float32_t deg)
{
    float32_t angle;

    angle = (deg * 3.1415926f) / 180.0f;
    return angle;
}

static inline float32_t toDegree(float32_t rad)
{
    float32_t angle;

    angle = (rad * 180.0f) / 3.1415926f;
    return angle;
}

static inline void resetDeadband_DAB(void)
{
    DeadBand_DAB = DeadBandMax;
    dbRampCounter_DAB = 0;
}
static inline void resetDeadband_INV(void)
{
    DeadBand_INV = DeadBandMax;
    dbRampCounter_INV = 0;
}

static inline void resetBothDeadbands(void)
{
    resetDeadband_DAB();
    resetDeadband_INV();
}

static inline void updateDeadband_DAB(void)
{
    //If DAB deadband has already reached final value,do not reduce it further.

    if(DeadBand_DAB <= DBTicks)
    {
        DeadBand_DAB = DBTicks;
        return;
    }

    dbRampCounter_DAB++;

    if(dbRampCounter_DAB >= DB_RAMP_DIVIDER_DAB) // For every 50 times take One action
    {
        dbRampCounter_DAB = 0;
        DeadBand_DAB--;
    }
}

static inline void updateDeadband_INV(void)
{
    if(DeadBand_INV <= DBTicks)
    {
        DeadBand_INV = DBTicks;
        return;
    }

    dbRampCounter_INV++;

    if(dbRampCounter_INV >= DB_RAMP_DIVIDER_INV)
    {
        dbRampCounter_INV = 0;
        DeadBand_INV--;
    }
}

//static inline void RUN_INV_ISR_SourceMode(void)
//{
//
//    NPC_readCurrentAndVoltageSignals();  // ADC FEEDBACK
//    NPC_run_internal_PLL();
//    Ref_Gen_function();  // REFERENCE SINE GENERATION FUNC.
//
//    if(StartPowerStage == 0)
//    {
//        resetDeadband_DAB();
//    }
//
//    if (StartPowerStage != StartPowerStage_prev)
//    {
//        if(StartPowerStage == 1)
//        {
//            float32_t target_on_angle = (float32_t)((ON_degree * PI) / 180.0f) + PI;
//            if(target_on_angle > 2*PI) target_on_angle = target_on_angle - 2*PI;
//            float32_t angle_diff = fabsf(pll_ang_A - target_on_angle);
//            if (angle_diff <= ON_ANG_TOL)
//            {
////                REFslew_set(&VA_RefSlewRamp,0.0f);
////                REFslew_set(&VdcRefSlewRamp,0.0f);
////                NPC_HAL_ClearALLPWMTripFlags();
//                NPC_HAL_ClearDAB_PWMTripFlags();
//                DABreadyCounter = 10000;
//                DABreadyFlag = TRUE;
////                resetDeadband();
//                resetDeadband_DAB();
//                StartPowerStage_prev = StartPowerStage;
//            }
//        }
//        else if (StartPowerStage == 0)
//        {
//            float32_t target_off_angle = (float32_t)((OFF_degree * PI) / 180.0f) + PI;
//            if(target_off_angle > 2*PI) target_off_angle = target_off_angle - 2*PI;
//            float32_t angle_diff = fabsf(pll_ang_A - target_off_angle);
//            if (angle_diff <= OFF_ANG_TOL)
//            {
//                NPC_HAL_ForceOSTEVENTtoALLEPWM();
////                err_VA = 0;
////                resetPR_custom(&Testg1);
////                resetDeadband();
//                StartPowerStage_prev = StartPowerStage;
//            }
//        }
//    }
//
//    if (StartPowerStage_Harm != StartPowerStage_Harm_prev)
//    {
//        if(StartPowerStage_Harm == 1)
//        {
//            float32_t target_on_angle = (float32_t)((ON_degree * PI) / 180.0f);
//            float32_t angle_diff = fabsf(pll_ang_A - target_on_angle);
//
//            if(angle_diff > PI) angle_diff = (float32_t)((2 * PI) - angle_diff);
//            if(angle_diff <= ON_ANG_TOL)
//            {
//                REFslew_set(&VA_RefSlewRamp,0.0f);
//                REFslew_set(&VdcRefSlewRamp,0.0f);
////                close_VoltageLoop = 1;
//                NPC_HAL_ClearALLPWMTripFlags();
//                StartPowerStage_Harm_prev = StartPowerStage_Harm;
//            }
//        }
//        else if (StartPowerStage_Harm == 0)
//        {
//            float32_t target_off_angle = (float32_t)((OFF_degree * PI) / 180.0f);
//            float32_t angle_diff = fabsf(pll_ang_A - target_off_angle);
//
//            if(angle_diff > PI) angle_diff = (float32_t)((2 * PI) - angle_diff);
//            if(angle_diff <= OFF_ANG_TOL)
//            {
//                NPC_HAL_ForceOSTEVENTtoALLEPWM();
//                StartPowerStage_Harm_prev = StartPowerStage_Harm;
////                err_VA = 0;
//            }
//        }
//    }
//
//    if(DABreadyCounter > 0) DABreadyCounter--;
//    else{}
//
//    if(DABreadyCounter == 0 && DABreadyFlag == TRUE)
//    {
//        REFslew_set(&VA_RefSlewRamp,0.0f);
//        REFslew_set(&VdcRefSlewRamp,0.0f);
//        NPC_HAL_ClearINV_PWMTripFlags();
//        resetDeadband_INV();
//        DABreadyFlag = FALSE;
//    }
//
//    if(DABreadyFlag == FALSE)
//
//    kpI_1H = kpI_test;
//    kiI_1H = kiI_test;
//    wrcI_1H = wrcI_test;
//    woI_1H = 2.0*PI*AC_FREQ_HZ;
//
//    computeDF22_PRcontrollerCoeff(&Testg1, kpI_1H,kiI_1H,woI_1H,
//                                             ISR_FREQUENCY,wrcI_1H);
//
//
////    REFslew_run(&VA_RefSlewRamp, Vac_fundamental, slope_VacRef);
//    REFslew_run(&VA_RefSlewRamp, 1.0, slope_VacRef);
//    REFslew_run(&VdcRefSlewRamp, V_DC, slope_VacRef);
//    VA_RefSlewed = VA_RefSlewRamp.out_slew;
//    Vdc_RefSlewed = VdcRefSlewRamp.out_slew;
////    Va_ref = (1.4142f * VA_RefSlewed*Ref_A) + Vdc_RefSlewed;  // three different amplitude of sine.
////    Va_ref = (1.4142f * VA_RefSlewed*Ref_A) - Vdc_RefSlewed;  // three different amplitude of sine.
//    Va_ref = VA_RefSlewed * Ref_A;
//
////    uint16_t x = (uint16_t)(((Va_ref/dividingFactor)*dacScalingFactor) + dacOffset);
////    NPC_HAL_passDAC_AVals(x);
//
//       err_VA = (float)(Va_ref - Va_fb);  // ERROR SIGNAL GIVEN TO CONTROLLER.
//
////       uint16_t y = (uint16_t)(((err_VA/dividingFactor)*dacScalingFactor) + dacOffset);
////       NPC_HAL_passDAC_BVals(y);
//
////       uk_Va  = runPR_custom(&Testg1, err_VA);
////       Ma1 = (float)(uk_Va + Va_fb)/(400);   // PR-CONTROLLER OUTPUT + FEEDFORWARD.
//       Ma1 = openLoopGain * Va_ref;
// //      Ma1 = (uk_Va+Va_ref)/100.0f;
//
////       pi_I_inv.Kp = uk_kp;
////       pi_I_inv.Ki = uk_ki;
////       uk_Ia = runPI_Custom(&pi_I_inv, Va_ref, Va_fb);
//////       Mff = Va_fb*0.001f;
////
//////       Ma1 = uk_Ia + Mff;
////       Ma1 = uk_Ia;
//
//
//       Mb1 = 0.0f;  // DAB Duty
//       Mc1 = 0.0f;  // DAB Duty
//
//       NPC_Calculate_duty(Ma1, Mb1, Mc1);
////       updateDeadband();
//       updateDeadband_DAB();
//       updateDeadband_INV();
//       NPC_HAL_updatePWMDutyAndDeadBand(dutyA_S1_Ref,
//                                        dutyB_S1_Ref,
//                                        dutyC_S1_Ref,
//                                        dutyN_S1_Ref,
//                                        dutyE_S1_Ref,
//                                        dutyF_S1_Ref,
//                                        DeadBand_DAB,
//                                        DeadBand_INV);
//
////        // Soft Start//
////           DeadBand = DBTicks-1;
////        if(DeadBand >= DBTicks)
////        {
////            DeadBand = DeadBand - 1;
////        }
//}


static inline void DeadBand_Sequence_Manager(void)
{
//    if(StartPowerStage == 0)
//    {
//        NPC_HAL_ForceOSTEVENTtoALLEPWM();
//
//        resetBothDeadbands();
//
//        DeadBandSeqState_t = DB_STATE_OFF;
//        InvStartDelayCounter = 0;
//        return;
//    }

    switch(DeadBandSeqState_t)
    {
        case DB_STATE_OFF:
        {
            /*
             * StartPowerStage has become 1.
             * Keep both DAB and inverter deadband at max first.
             */
            resetBothDeadbands();
            break;
        }
        case DB_STATE_GATE_DRIVE_ON:
        {
            /*
             *
             */
            GateDriveON();
            NPC_HAL_ClearDAB_PWMTripFlags();
            DeadBandSeqState_t = DB_STATE_DAB_RAMP;
        }
        case DB_STATE_DAB_RAMP:
        {
            /*
             * Only DAB deadband reduces.
             * Inverter deadband remains max.
             */

            updateDeadband_DAB();

            if(DeadBand_DAB <= DBTicks)
            {
                DeadBand_DAB = DBTicks;

                InvStartDelayCounter = INV_START_DELAY_COUNT;
                DeadBandSeqState_t = DB_STATE_WAIT_INV_ON;
            }

            break;
        }
        case DB_STATE_WAIT_INV_ON:
        {
            /*
             * DAB is ready at DBTicks.
             * Inverter still held at max deadband.
             */

            if(InvStartDelayCounter > 0)
            {
                InvStartDelayCounter--;
            }
            else
            {
                REFslew_set(&VA_RefSlewRamp, 0.0f);
                REFslew_set(&IA_RefSlewRamp, 0.0f);
                REFslew_set(&VdcRefSlewRamp, 0.0f);
                REFslew_set(&Idc_RefSlewRamp, 0.0f);
                NPC_HAL_ClearINV_PWMTripFlags();
                DeadBandSeqState_t = DB_STATE_RUN1;
            }

            break;
        }
        case DB_STATE_RUN1:
        {
            /*
             * Normal running condition.
             */
            DeadBand_DAB = DBTicks;
            DeadBand_INV = DBTicks;

            REFslew_run(&VA_RefSlewRamp, Vac_fundamental, slope_VacRef);
            REFslew_run(&IA_RefSlewRamp, Iset, slope_VacRef);
            REFslew_run(&VdcRefSlewRamp, V_DC, slope_VdcRef);

//            if(Meas_Vrms > (1.2f * Limit_VAC)) outOVP = 1U;
//            if(Meas_Irms > (1.2f * Limit_IAC)) outOCP = 1U;
//            if(Vdc_link > 650.0f) DCbus_OVP = 1U;
//            if(Vdc_link < 530.0f) DCbus_UVP = 1U;

//            if(invStart == 0)
//            {
//                DeadBand_INV = DeadBandMax;
//            }
//            else if(invStart == 1)
//            {
//                DeadBand_INV = DBTicks;
//                REFslew_set(&VA_RefSlewRamp, 0.0f);
//                REFslew_set(&VdcRefSlewRamp, 0.0f);
//                NPC_HAL_ClearINV_PWMTripFlags();
//                DeadBandSeqState_t = DB_STATE_RUN2;
//            }

            break;
        }

        case DB_STATE_RUN2:
        {
            DeadBand_DAB = DBTicks;

            if(invStart == 1)
            {
                DeadBand_INV = DBTicks;
            }
            else if(invStart == 0)
            {
                NPC_HAL_ForceOSTEVENT_to_INV_EPWM();
                DeadBand_INV = DeadBandMax;
                DeadBandSeqState_t = DB_STATE_RUN1;
            }

            break;
        }
        case DB_STATE_DAB_OFF:
        {
//            NPC_HAL_ForceOSTEVENT_to_DAB_EPWM();
            resetDeadband_DAB();
            InvStopDelayCounter = INV_STOP_DELAY_COUNT;
            DeadBandSeqState_t = DB_STATE_WAIT_INV_OFF;

            break;
        }
        case DB_STATE_WAIT_INV_OFF:
        {
            if(InvStopDelayCounter > 0)
            {
                InvStopDelayCounter--;
            }
            else
            {
                DeadBandSeqState_t = DB_STATE_INV_OFF;
            }

            break;
        }
        case DB_STATE_INV_OFF:
        {
//            NPC_HAL_ForceOSTEVENT_to_INV_EPWM();
            NPC_HAL_ForceOSTEVENTtoALLEPWM();
            resetDeadband_INV();
            InvStartDelayCounter = 0;
            InvStopDelayCounter = 0;
            DeadBandSeqState_t = DB_STATE_GATE_DRIVE_OFF;

//            invStart = 0;

            break;
        }
        case DB_STATE_GATE_DRIVE_OFF:
        default:
        {
            GateDriveOFF();

            break;
        }
    }
}

//static inline uint16_t Vmon_To_DacCount(float32_t vmon)
//{
//    float32_t dac_count;
//
//    // Limit input range: -10.5V to +10.5V
//    if (vmon > 10.5f)
//    {
//        vmon = 10.5f;
//    }
//    else if (vmon < -10.5f)
//    {
//        vmon = -10.5f;
//    }
//
//    // Linear mapping from table:
//    // 0V = 2047 count
//    // 1V = 187 counts approximately
//    dac_count = 2047.0f + (vmon * 187.0f);
//
//    // Clamp to valid 12-bit DAC range
//    if (dac_count > 4095.0f)
//    {
//        dac_count = 4095.0f;
//    }
//    else if (dac_count < 0.0f)
//    {
//        dac_count = 0.0f;
//    }
//
//    return (uint16_t)(dac_count + 0.5f);
//}



static inline void RUN_INV_ISR_SourceMode(void)
{
    NPC_readCurrentAndVoltageSignals();
    NPC_run_internal_PLL();
    Ref_Gen_function();

    /*
     * Start/stop angle synchronization logic
     */
    if (StartPowerStage != StartPowerStage_prev)
    {
        if(StartPowerStage == 1)
        {
            float32_t target_on_angle = (float32_t)((ON_degree * PI) / 180.0f) + PI;
            if(target_on_angle > 2.0f * PI)
            {
                target_on_angle = target_on_angle - 2.0f * PI;
            }
            float32_t angle_diff = fabsf(pll_ang_A - target_on_angle);

            if(angle_diff <= ON_ANG_TOL)
            {
                resetBothDeadbands();
                DeadBandSeqState_t = DB_STATE_GATE_DRIVE_ON;
                StartPowerStage_prev = StartPowerStage;

                REFslew_set(&VA_RefSlewRamp,0.0f);
                REFslew_set(&VdcRefSlewRamp, 0.0f);
                REFslew_set(&Idc_RefSlewRamp, 0.0f);
                REFslew_set(&IA_RefSlewRamp,0.0f);
            }
        }
        else
        {
            float32_t target_off_angle = (float32_t)((OFF_degree * PI) / 180.0f) + PI;
            if(target_off_angle > 2.0f * PI) target_off_angle = target_off_angle - 2.0f * PI;
            float32_t angle_diff = fabsf(pll_ang_A - target_off_angle);
            if(angle_diff <= OFF_ANG_TOL)
            {
                DeadBandSeqState_t = DB_STATE_DAB_OFF;
                StartPowerStage_prev = StartPowerStage;
            }
        }


    }

    /*
     * The below if logic is to reduce the sudden spike in output voltage at starting
     * during StartPowerStage == 0 , controller resetting, prevents the controller saturation
     */
    if(StartPowerStage == 0)
    {
        REFslew_set(&VA_RefSlewRamp,0.0f);
        REFslew_set(&IA_RefSlewRamp,0.0f);
        REFslew_set(&VdcRefSlewRamp, 0.0f);
        REFslew_set(&Idc_RefSlewRamp, 0.0f);
        resetPR_custom(&Testg1);
        resetPR_custom(&dutynotch1);
    }

    DeadBand_Sequence_Manager();

    VA_RefSlewed = VA_RefSlewRamp.out_slew;
    IA_RefSlewed = IA_RefSlewRamp.out_slew;
    Vdc_RefSlewed = VdcRefSlewRamp.out_slew;
    Idc_RefSlewed = Idc_RefSlewRamp.out_slew;
    NPC_HAL_passDAC_AVals((uint16_t)Va_sns);

    woI_1H = 2.0*PI*(FreqRefSlewRamp_A.out_slew);
    kpI_1H = kpI_test;
    kiI_1H = kiI_test;
    wrcI_1H = wrcI_test;
    computeDF22_PRcontrollerCoeff_2(&Testg1, kpI_1H,kiI_1H,woI_1H,ISR_FREQUENCY,wrcI_1H);

    NPC_computeNotchFltrCoeff(&dutynotch1,ISR_FREQUENCY,FreqRefSlewRamp_A.out_slew ,0.0001f, 0.8f);

    switch(SelMode)
    {
        case 0:     //AC
        {
            Va_ref = 1.41421356f * VA_RefSlewed * Ref_A;
            Ia_ref = 1.41421356f * IA_RefSlewed * Ref_A;
            break;
        }

        case 1:     //DC
        {
            Va_ref = Vdc_RefSlewed;
            Ia_ref = Idc_RefSlewed;
            break;
        }

        case 2:   //AC+DC
        {
            Va_ref = (1.41421356f * VA_RefSlewed * Ref_A) + Vdc_RefSlewed;
            Ia_ref = (1.41421356f * IA_RefSlewed * Ref_A) + Idc_RefSlewed;
            break;
        }

        default:
        {
            Va_ref = 0.0f;
            Ia_ref = 0.0f;
            break;
        }
    }

#if LOOP_TYPE == OPEN_LOOP

    Ma1 = openLoopGain * Va_ref;

#elif LOOP_TYPE == CLOSED_LOOP
/*
    err_VA = (float)(Va_ref - Va_fb);
    uk_Va1  = runPR_custom(&Testg1, err_VA) ;
    uk_Va2  = runPR_custom(&dutynotch, uk_Va1) ;
    uk_Va  = runPR_custom(&dutynotch1, uk_Va2) ;
//    Ma1 = ((uk_Va + Va_fb)/560.0f);
 //   Ma1 = ((uk_Va + Va_fb)/400.0f);

    Ma1 = ((uk_Va + Va_fb)/100.0f);

 //   Ma1 = (M_beta + (M_alpha*Ref_A));

 */
// Grid EMulator Control Code //

    err_VA = (float)(Va_ref - Va_fb);
    err_IA = (float)(Ia_ref - Ia_fb);

//    uk_Va1  = runPR_custom(&Testg1, err_VA) ;
//    uk_Va  = runPR_custom(&dutynotch, uk_Va1) ;


  //  uk_Va  = runPR_custom(&Testg1, err_VA); //(h*) ;

    uk_Ia  = runPR_custom(&Testg2, err_IA);

    uk_Va = runPR_custom(&Testg1, err_VA); //runPR_custom(&dutynotch1, err_VA);

    Ma_CV = ((uk_Va + Va_fb)/400.0f);
    Ma_CC = ((uk_Ia + Ia_fb)/30.0f);

    Ma1 = Ma_CV ;

//    Ma_CV_abs = fabsf(Ma_CV);
//  //  Ma_CV_Max = fmaxf(Ma_CV_Max, Ma_CV_abs);
//    Ma_CC_abs = fabsf(Ma_CC);
// //   Ma_CC_Max = fmaxf(Ma_CC_Max, Ma_CC_abs);      // these two lines giving issue
//
//    /* Find maximum value during present AC cycle */
//    if (Ma_CV_abs > Ma_CV_Max)
//    {
//        Ma_CV_Max = Ma_CV_abs;
//    }
//
//    if (Ma_CC_abs > Ma_CC_Max)
//    {
//        Ma_CC_Max = Ma_CC_abs;
//    }
//
//    /*
//     * Positive-going zero crossing.
//     * This happens once per complete AC cycle.
//     */
//    if ((Va_fb_old <= 0.0f) && (Va_fb > 0.0f))
//    {
//        /* Store peak values of completed cycle */
//        Ma_CV_Peak = Ma_CV_Max;
//        Ma_CC_Peak = Ma_CC_Max;
//
//        /* Reset for next cycle */
//        Ma_CV_Max = 0.0f;
//        Ma_CC_Max = 0.0f;
//    }
//
//    Va_fb_old = Va_fb;
//
//    if (Ma_CV_Peak < Ma_CC_Peak)
//      {
//        Ma1 = Ma_CV;
//        CV_Flag = 1;
//        CC_Flag = 0;
//       // resetPR_custom(&Testg2);
//      }
//      else
//        {
//           Ma1 = Ma_CC;
//           CC_Flag = 1;
//           CV_Flag = 0;
//         //  resetPR_custom(&Testg1);
//        }


#endif


    Mb1 = 0.0f;
    Mc1 = 0.0f;

    NPC_Calculate_duty(Ma1, Mb1, Mc1);

//    NPC_Calculate_TotemPole_Inverter_Duty(Ma1);

//    DeadBand_Sequence_Manager();

    NPC_HAL_updatePWMDutyAndDeadBand(dutyA_S1_Ref,
                                     dutyB_S1_Ref,
                                     dutyC_S1_Ref,
                                     dutyN_S1_Ref,
                                     dutyE_S1_Ref,
                                     dutyF_S1_Ref,
                                     DeadBand_DAB,
                                     DeadBand_INV);
}



static inline void RUN_INV_ISR_LoadMode(void)
{
    NPC_readCurrentAndVoltageSignals();  // ADC FEEDBACK
    SPLL_1PH_SOGI_run(&V_line_pll, Vac_fb_pu);

    if (StartPowerStage != StartPowerStage_prev)
    {
        if(StartPowerStage == 1)
        {
            REFslew_set(&IA_RefSlewRamp,0.0f);
            NPC_HAL_ClearALLPWMTripFlags();
            StartPowerStage_prev = StartPowerStage;
        }
        else if (StartPowerStage == 0)
        {
            StartPowerStage_prev = StartPowerStage;
        }
    }

    if(StartPowerStage == 0) resetPI_Custom(&pi_I_inv);
    else;

    float32_t I_ref_slew = ((float32_t)(0.01/(0.001*ISR_FREQUENCY)));

    REFslew_run(&IacRefSlewRamp, -Iset, I_ref_slew);
    REFslew_run(&Idc_RefSlewRamp, -Iset_dc, I_ref_slew);
    IA_RefSlewed = IacRefSlewRamp.out_slew;
    Idc_RefSlewed = Idc_RefSlewRamp.out_slew;
    Ia_ref = (1.414f) * IA_RefSlewed * sinf(V_line_pll.theta[1]-((3.141592653f * phase_angle)/180.0f) + 3.141592653f) - Idc_RefSlewed;


    /*
     * For Single Phase
     *
     *
     * uk_kp = 0.0599999987
     * uk_ki = 0.00499999989 /// these Kp & Ki gives better in phase condition
     *
     *
     * uk_kp = 0.0149999997
     * uk_ki = 0.00100000005 /// these Kp & Ki gives better thd
     */
    pi_I_inv.Kp = uk_kp;
    pi_I_inv.Ki = uk_ki;

    uk_Ia = runPI_Custom(&pi_I_inv, Ia_ref, Ia_fb);
    Mff = Va_fb * 0.001f;

    Ma1 = uk_Ia + Mff; //feed forward

    // duty update//
    NPC_Calculate_duty(Ma1,0,0);

//    NPC_HAL_updatePWMDutyAndDeadBand(dutyA_S1_Ref,    dutyB_S1_Ref,
//                                     DeadBand);

//    // Soft Start//
//    if(DeadBand >= DBTicks)
//    {
//        DeadBand = DeadBand - 1;
//    }
}



/*******************************************************
 * *****************************************************
 * *****************************************************
 */

static inline void RUN_INV_ISR_SourceMode_CC_Loop(void)
{

    NPC_readCurrentAndVoltageSignals();  // ADC FEEDBACK
    NPC_run_internal_PLL();
    Ref_Gen_function();  // REFERENCE SINE GENERATION FUNC.
    if (StartPowerStage != StartPowerStage_prev)
    {
        if(StartPowerStage == 1)
        {
            REFslew_set(&IA_RefSlewRamp,0.0f);
            NPC_HAL_ClearALLPWMTripFlags();
            StartPowerStage_prev = StartPowerStage;
        }
        else if (StartPowerStage == 0)
        {
//            NPC_HAL_ForceOSTEVENTtoALLEPWM();
            StartPowerStage_prev = StartPowerStage;
            err_VA = 0;
        }
    }


    REFslew_run(&IA_RefSlewRamp, Iset, 0.001);
    IA_RefSlewed = IA_RefSlewRamp.out_slew;
    Ia_ref = (1.4142f * IA_RefSlewed*Ref_A);  // three different amplitude of sine.


    pi_I_inv.Kp   = uk_kp; //GI_PI_kp_loadMode;
    pi_I_inv.Ki   = uk_ki; //GI_PI_ki_loadMode;


//    err_IA = (float)(Ia_ref - Ia_fb);  // ERROR SIGNAL GIVEN TO CONTROLLER.
//    uk_Ia  = runPR_custom(&Testg1, err_IA);


    uk_Ia  = runPI_Custom(&pi_I_inv, Ia_ref, Ia_fb);

    Ma1 = (float)uk_Ia;   // PR-CONTROLLER OUTPUT + FEEDFORWARD.
//    NPC_Calculate_duty(Ma1);
//    NPC_HAL_updatePWMDutyAndDeadBand(dutyA_S1_Ref,
//                                    dutyB_S1_Ref,
//                                    DeadBand);
//    // Soft Start//
//    DeadBand = DBTicks-1;
//    if(DeadBand >= DBTicks)
//    {
//        DeadBand = DeadBand - 1;
//    }
}



#pragma FUNC_ALWAYS_INLINE(Run_aux_ISR)
static inline void Run_aux_ISR(void)
{

}


#endif /* NPC_SOLUTION_H_ */
