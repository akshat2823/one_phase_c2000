/*
 * Project_Defines.h
 *
 *  Created on: 17-Jun-2025
 *      Author: Anamitra Sarkar
 */


#ifndef PROJECT_DEFINES_H_
#define PROJECT_DEFINES_H_
//
//Project_Defines
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * select converter type
 */
#define SINGLE_PHASE     1
#define THREE_PHASE      2
#define CONVERTER_TYPE  SINGLE_PHASE

#define OPEN_LOOP        1
#define CLOSED_LOOP      2
#define LOOP_TYPE       CLOSED_LOOP

//
// select CC or CV loop
//
#define CV_loop 1
#define CC_loop 2
#define ON 3
#define loop CV_loop//CC_loop//
#define power_loop  ON

//
// select mode1  --> GE/EL
//
#define GE_AC                 1
#define EL_AC                 2
#define GE_DC                 3
#define EL_DC                 4
#define GE_AC_DC              5
#define testing               6
#define mode1                 GE_AC //  testing//  GE_AC//GE_DC//  GE_AC// EL_AC//

//
// sub mode in GE_AC
//
#define NormalOperation                 1
#define ACFaults                        2
#define harmonic_injection              3
#define arbitary_frequency              4
#define SINGLE_PHASE_paralleling        5
#define programmable_output_impedence   6
#define Arbitrary_waveform_mode         7
#define AC_submode                      NormalOperation//Arbitrary_waveform_mode//harmonic_injection//arbitary_frequency//  programmable_output_impedence//arbitary_frequency//SINGLE_PHASE_paralleling

// mode2 -- balanced/unbalanced
#define balanced 1
#define unbalanced 2
#define mode2 balanced   // unbalanced//

//
// sub mode in GE_DC
//
#define NormalOperation                    1
#define Bipolar                            2
#define paralleling                        3
#define programmable_output_impedence_dc   4
#define DC_submode                         NormalOperation//Bipolar// NormalOperation//Bipolar//programmable_output_impedence_dc//


//ACFaults mode --> applicable in balanced mode only
#define VoltageDip              1
#define Frequency_Variation     2
#define Flickering              3
#define ACFaultmode             Frequency_Variation // VoltageDip //Frequency_Variation//Flickering //


//Arbitrary_waveform_Gen
#define pos_sawtooth        1
#define neg_sawtooth        2
#define sin_wave            3
#define rectified_sin_wave  4
#define clipped_sin_wave    5
#define square              6
#define triac               7

#define Arbitrary_waveform_mode_A sin_wave
#define Arbitrary_waveform_mode_B sin_wave
#define Arbitrary_waveform_mode_C sin_wave

//
//VAC reference peak value
//
#define Vac_Ref                 ((float32_t)100)
#define VacRefSlope             ((float32_t)(0.1/(0.001*ISR_FREQUENCY))) //slope: 0.1V per ms
//
//IAC reference peak value
//
#define Imax_Ref                 ((float32_t)5)
#define IacRefSlope              ((float32_t)(0.1/(0.001*ISR_FREQUENCY))) //slope: 0.1A per ms

//
// arbitary_frequency
//
#define arbitary_frequency_A    50.0f     // working upto 1khz in balanced mode and not working in unbalanced mode
#define arbitary_frequency_B    50.0f
#define arbitary_frequency_C    50.0f
//#define startpowerstage         2
//
// programmable_output_impedence
//
#define Za_v 1.0f
#define Zb_v 1.0f
#define Zc_v 1.0f

#define Za_I 1000.0f
#define Zb_I 1000.0f
#define Zc_I 1000.0f

//
//AC faults related
//
//Voltage Dips
#define Fault_initial_time       (float32_t)(1005*ONE_MILLI_SEC)
#define Fault_fall_time          (float32_t)(15*ONE_MICRO_SEC)   //(1*ONE_MILLI_SEC)//
#define Fault_dip_time           (float32_t)(4000*ONE_MILLI_SEC)
#define Fault_raise_time         (float32_t)(1000*ONE_MILLI_SEC)
#define Tinit   Fault_initial_time
#define Tfall     (float32_t)(Fault_initial_time + Fault_fall_time)
#define Tdip      (float32_t)(Tfall + Fault_dip_time)
#define Traise    (float32_t)(Tdip + Fault_raise_time)
#define AC_fault_Vinitial      300
#define AC_fault_Vdip          150
#define AC_fault_Vfinal        250

//Frequency variation
#define AC_fault_setFreq            40
#define AC_fault_setFreqSlope       (float)(0.01/ONE_MILLI_SEC)      //Hz per ms

//Flicker
#define T_fadeIN                  (float32_t)(200*ONE_MILLI_SEC)
#define T_fadeOUT                 (float32_t)(200*ONE_MILLI_SEC)
#define T_flicker                 (float32_t)(2000*ONE_MILLI_SEC)
#define Flicker_Amplitude         0.25f
#define Flicker_FREQ              5.0f
//
//slope for Frequency Reference
//
#define FreqRefSlope            ((float32_t)(0.1/(0.001*ISR_FREQUENCY))) //slope: 0.1Hz per ms
#define AngleRefSlope           ((float32_t)(0.01/(0.001*ISR_FREQUENCY))) //slope: 0.1randian per ms


#if mode1 == GE_AC
    #if AC_submode == ACFaults //NormalOperation //
            #if ACFaultmode == Frequency_Variation
            //
            //PR controller related
            // changed KIV_1H from 100 to 1000 for freq. variation

            //voltage loop EL mode(final)
            #define KPI_1H              0.004567875851731f
            #define KII_1H              1000.0f//10//1000  // changed KIV_1H from 100 to 1000 for freq. variation
            #define WRCI_1H             0.628f*1//0.314159265f*0.5//0.0000628f
            #define KII_3H              25.0f//3.9975f//250
            #define WRCI_3H             0.031415f
            #define KII_5H              25.0f//2.0f//3.9975//250
            #define WRCI_5H             0.031415f//0.44879895f*0.5//0.031415f
            #define KII_7H              10.0f//2.0f//250
            #define WRCI_7H             0.0031415f//0.1303f*0.5//0.44879895f//0.031415f
            #define KII_9H              10.0f//125
            #define WRCI_9H             0.00314157f

            #else
            //voltage loop EL mode(final)
            #define KPI_1H              0.004567875851731f
            #define KII_1H              100.0f//10//1000  // changed KIV_1H from 100 to 1000 for freq. variation
            #define WRCI_1H             0.628f*1//0.314159265f*0.5//0.0000628f
            #define KII_3H              25.0f//3.9975f//250
            #define WRCI_3H             0.031415f
            #define KII_5H              25.0f//2.0f//3.9975//250
            #define WRCI_5H             0.031415f//0.44879895f*0.5//0.031415f
            #define KII_7H              10.0f//2.0f//250
            #define WRCI_7H             0.0031415f//0.1303f*0.5//0.44879895f//0.031415f
            #define KII_9H              10.0f//125
            #define WRCI_9H             0.00314157f

            #endif

            //current loop EL mode(final)
            #define KPV_1H              0.004567875851731f
            #define KIV_1H              100.0f//10//1000
            #define WRCV_1H             0.628f//0.314159265f*0.5//0.0000628f
            #define KIV_3H              25.0f//3.9975f//250
            #define WRCV_3H             0.031415f
            #define KIV_5H              25.0f//2.0f//3.9975//250
            #define WRCV_5H             0.031415f//0.44879895f*0.5//0.031415f
            #define KIV_7H              10.0f//2.0f//250
            #define WRCV_7H             0.0031415f//0.1303f*0.5//0.44879895f//0.031415f
            #define KIV_9H              10.0f//125
            #define WRCV_9H             0.00314157f


    #else
    #endif

#if mode1 == GE_AC// testing //
    #if AC_submode == NormalOperation // ACFaults //
            //voltage loop
//            #define KPV_1H            1.5f //1.0f //0.5f //0.97f////0.045f //10//1.4567875851731f
//            #define KIV_1H            1000.0f //1000.0f //300.0f ////100.0f // 50.0f//10//1000  // changed KIV_1H from 100 to 1000 for freq. variation//0.051
//            #define WRCV_1H           0.00628f //0.00628f //25.0f //62.8f //628.0f //1.0f//20.0f//100.0f // 50.0f //0.6f//0.00628f// 0.628f*1//0.314159265f*0.5//1.0f

#else
#endif

#else
#endif

#else
#endif


            #define KPV_1H            1.0f //1.0f //0.5f //0.97f////0.045f //10//1.4567875851731f
            #define KIV_1H            1000.0f //1000.0f //300.0f ////100.0f // 50.0f//10//1000  // changed KIV_1H from 100 to 1000 for freq. variation//0.051
            #define WRCV_1H           0.00628f //0.00628f //25.0f //62.8f //628.0f //1.0f//20.0f//100.0f // 50.0f //0.6f//0.00628f// 0.628f*1//0.314159265f*0.5//1.0f


//
//PI controller for DC mode
//
#define GI_PI_kp_V          0.002436839034552f
#define GI_PI_ki_V          0.0001531111121786025f
#define GI_PI_MAX_V         1.0f
#define GI_PI_MIN_V         -1.0f

// current controller coef. same as pfc coeff.
#define GI_PI_kp_I          0.004567875851731f
#define GI_PI_ki_I          0.001033229175718f*2.0f
#define GI_PI_MAX_I         1.0f
#define GI_PI_MIN_I         -1.0f

#define GI_PI_kp      0.004567875851731f
#define GI_PI_ki      0.001033229175718f*2.0f // (50khz)  0.001033229175718f*2.5f // (40khz)  //
#define GI_PI_MAX     1.13f
#define GI_PI_MIN    -1.13f

/**********PI Controller Defines**********/
//
//current controller(PFC)
//

#define GI_PI_kp_loadMode      0.007542758915403f        // Kp - PFC current controller
#define GI_PI_ki_loadMode      0.0009478510398571098f    // Ki - PFC current controller
#define GI_PI_MAX_loadMode     1.0f                      // positive saturation limit
#define GI_PI_MIN_loadMode    -1.0f



////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ONE_NANO_SEC  ((float32_t)0.000000001)
#define ONE_MICRO_SEC ((float32_t)0.000001)
#define ONE_MILLI_SEC ((float32_t)0.001)
//
//Hardware peripheral related define
//
/**********EPWM Related Defines**********/
#define DEVICE_FREQ     200000000U
#define Fsysclock       100000000

#if CONVERTER_TYPE == SINGLE_PHASE
#define Fswitching      50000.0f       // select switching frequency
//#define Fswitching      50000.0f
#define T_switching     (1 / Fswitching)
#define Faux            (Fswitching/10)        // select auxilary ISR frequency
#define Fsw_FAN         20000       // select fan switching frequency
#define TimeBase        (Uint16)(Fsysclock*0.5/Fswitching)
#define TimeBase_aux    (Uint16)(Fsysclock*0.5/Faux)
#define TimeBase_FAN    (Uint16)((float)(Fsysclock/Fsw_FAN) - 1)

#define DBTicks         (Uint16)(450*ONE_NANO_SEC*Fsysclock)
#define DB_RAMP_DIVIDER_DAB   50U   // increase this to slow down the deadband update more
#define DB_RAMP_DIVIDER_INV   50U   // increase this to slow down the deadband update more
#define INV_START_DELAY_COUNT   10000U
#define INV_STOP_DELAY_COUNT    25000U

#elif CONVERTER_TYPE == THREE_PHASE
#define Fswitching      50000
#define T_switching     (1 / Fswitching)
#define Faux            1000        // select auxilary ISR frequency
#define Fsw_FAN         20000       // select fan switching frequency
#define TimeBase        (Uint16)(Fsysclock*0.5/Fswitching)
#define TimeBase_aux    (Uint16)(Fsysclock*0.5/Faux)
#define TimeBase_FAN    (Uint16)((float)(Fsysclock/Fsw_FAN) - 1)

#define DBTicks         (Uint16)(1000*ONE_NANO_SEC*Fsysclock) //(400*ONE_NANO_SEC*Fsysclock)
#else
#endif

#define DeadBandMax     (Uint16)(Fsysclock/Fswitching)

/**********ADC Related**********/
#if CONVERTER_TYPE == SINGLE_PHASE
#define ADCPrescaler 6
#define Acqps        25
#define VgridSense_channel  2
#define IconvSense_channel  4
#define Vdc_1Sense_channel  3

#define Vpgm_channel        3
#define Ipgm_channel        3

#define ADCSOCTrigger1      5
#define ADCSOCTrigger2      9
#define ADCSOCTrigger3      10
#define ADCSOCTrigger4      6

#elif CONVERTER_TYPE == THREE_PHASE

#define ADCPrescaler 6
#define Acqps        14
#define VgridSense_channel  3
#define IconvSense_channel  4
#define Vdc_1Sense_channel  2
#define Vdc_2Sense_channel  2
#define TEMP_A_channel  5
#define TEMP_B_channel  5
#define ADCSOCTrigger1      11
#define ADCSOCTrigger2      13
#define ADCSOCTrigger3      14
#define ADCSOCTrigger4      12
#define ADCSOCTrigger5      19

#else
#endif

/**********Board Protection Related**********/

#if CONVERTER_TYPE == SINGLE_PHASE

//#define NPC_A_CMPSS_BASE        CMPSS3_BASE
//#define NPC_A_XBAR_MUX          XBAR_MUX04
//#define NPC_A_XBAR_MUX_VAL      XBAR_EPWM_MUX04_CMPSS3_CTRIPH_OR_L
//#define NPC_A_XBAR_FLAG1        XBAR_INPUT_FLG_CMPSS3_CTRIPL
//#define NPC_A_XBAR_FLAG2        XBAR_INPUT_FLG_CMPSS3_CTRIPH

#define NPC_A_CMPSS_BASE        CMPSS2_BASE
#define NPC_A_XBAR_MUX          XBAR_MUX02
#define NPC_A_XBAR_MUX_VAL      XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L
#define NPC_A_XBAR_FLAG1        XBAR_INPUT_FLG_CMPSS2_CTRIPL
#define NPC_A_XBAR_FLAG2        XBAR_INPUT_FLG_CMPSS2_CTRIPH

#elif CONVERTER_TYPE == THREE_PHASE

#define NPC_A_CMPSS_BASE        CMPSS2_BASE
#define NPC_A_XBAR_MUX          XBAR_MUX02
#define NPC_A_XBAR_MUX_VAL      XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L
#define NPC_A_XBAR_FLAG1        XBAR_INPUT_FLG_CMPSS2_CTRIPL
#define NPC_A_XBAR_FLAG2        XBAR_INPUT_FLG_CMPSS2_CTRIPH

#define NPC_B_CMPSS_BASE        CMPSS6_BASE
#define NPC_B_XBAR_MUX          XBAR_MUX10
#define NPC_B_XBAR_MUX_VAL      XBAR_EPWM_MUX10_CMPSS6_CTRIPH_OR_L
#define NPC_B_XBAR_FLAG1        XBAR_INPUT_FLG_CMPSS6_CTRIPL
#define NPC_B_XBAR_FLAG2        XBAR_INPUT_FLG_CMPSS6_CTRIPH

#define NPC_C_CMPSS_BASE        CMPSS5_BASE
#define NPC_C_XBAR_MUX          XBAR_MUX08
#define NPC_C_XBAR_MUX_VAL      XBAR_EPWM_MUX08_CMPSS5_CTRIPH_OR_L
#define NPC_C_XBAR_FLAG1        XBAR_INPUT_FLG_CMPSS5_CTRIPL
#define NPC_C_XBAR_FLAG2        XBAR_INPUT_FLG_CMPSS5_CTRIPH

#else
#endif

//#define NPC_FAULT_GPIO                      95
//#define NPC_FAULT_GPIO_PIN_CONFIG           GPIO_95_GPIO95
#define NPC_FAULT_XBAR_MUX_VAL              XBAR_EPWM_MUX01_INPUTXBAR1
#define NPC_FAULT_XBAR_MUX                  XBAR_MUX01
#define NPC_FAULT_XBAR_FLAG                 XBAR_INPUT_FLG_INPUT1

//#define NPC_FAN_FB_GPIO                     29
//#define NPC_FAN_FB_GPIO_PIN_CONFIG          GPIO_29_GPIO29
#define TINV_PROFILING1_ECAP                ECAP1_BASE

#define NPC_INVONOFF_GPIO                      25
#define NPC_INVONOFF_GPIO_PIN_CONFIG           GPIO_25_GPIO25
//
//write '1' to enable DESAT based protection
//write '0' to disable DESAT based protection
//
#define BOARD_PROTECTION_DESAT      0
//
//write '1' to enable CMPSS based protection
//write '0' to disable CMPSS based protection
//
#define BOARD_PROTECTION_CMPSS      0
//
//Back Ground Task Related
//
#define TASKA_FREQ      100
#define NPC_GET_TASK_A_TIMER_OVERFLOW_STATUS CPUTimer_getTimerOverflowStatus(CPUTIMER0_BASE)
#define NPC_CLEAR_TASK_A_TIMER_OVERFLOW_FLAG CPUTimer_clearOverflowFlag(CPUTIMER0_BASE)

//#############################################END of Hardware peripheral related defines############################//
//
//Solution related define
//

//
//protection related defines
//
/**********Trip current reference**********/
//
//
#if CONVERTER_TYPE == SINGLE_PHASE

#define Iconv_MAX_SENSE_AMPS  ((float32_t)88)
#define Iconv_TRIP_LIMIT_AMPS ((float32_t)88)

#elif CONVERTER_TYPE == THREE_PHASE

#define Iconv_MAX_SENSE_AMPS  ((float32_t)70) //((float32_t)88)
#define Iconv_TRIP_LIMIT_AMPS ((float32_t)70) //((float32_t)88)

#else
#endif
//
// protection with filter
//
#define VBUS_OVERVOLT_LIMIT     440

#define VGRID_BASE              381.8376618f//325
#define GRID_MIN_VRMS           190
#define GRID_MAX_VRMS           300
#define GRID_MAX_FREQ           100 //60
#define GRID_MIN_FREQ           10  //45

#define MIN_DCLINK_volt  340
#define MAX_DCLINK_volt  400

//
//EMAVG macro
//
#define EMAVG_MACRO(in, out, multiplier) out = ((out - in) * multiplier) + in;

/**********ADC scaling&offset Defines**********/
//#if CONVERTER_TYPE == SINGLE_PHASE

//#define Vgrid_Sense_scaling     0.340331903868f//(REF3.0V[working in 12-bit])0.013928785f /*16-bit*/ // //0.245202744f(REF3.3V)
//#define Vgrid_Sense_scaling_PU  0.0077525359256128f //[working in 12-bit] //0.0005837862720829731f//(REF3.0V)//0.0006421648992912699f//(REF3.3V)
//#define Iconv_Sense_scaling     0.03662109375f //[working in 12-bit] //0.039467198f /*16-bit*/ //0.036716425985f//0.038657326632f
////#define Vdc_Sense_scaling       0.2501000000f //[working in 12-bit] //0.264384851206f//0.258356532356f//0.265246039646f//0.263523662766f//
//#define Vdc_Sense_scaling       0.264269f  //0.282083333f //0.273535354f
////
////Average current OFF set used in CMPSS
////
//#define Vgrid_sense_offset    2265 //2332 //2332
//#define Iconv_sense_offset    1885 //2251 //1885
//#define Vdc_sense_offset      12

//#elif CONVERTER_TYPE == THREE_PHASE


//tttt

//#define Vgrid_Sense_scaling     0.222911585f//(for 143K divider)//0.37262f//(for 127K divider)//(REF3.0V[working in 12-bit])0.013928785f /*16-bit*/ // //0.245202744f(REF3.3V)
#define Vgrid_Sense_scaling_PU  0.0005837862720829731f //0.003152445869248f //[working in 12-bit] //0.0005837862720829731f//(REF3.0V)//0.0006421648992912699f//(REF3.3V)
#define Iconv_Sense_scaling     0.039476832096f //[working in 12-bit] //0.039467198f /*16-bit*/ //0.036716425985f//0.038657326632f
#define Vdc_Sense_scaling       0.265246039646f //[working in 12-bit] //0.264384851206f//0.258356532356f//0.265246039646f//0.263523662766f//
#define Vdc1_Sense_scaling      0.22498995580554f //[working in 12-bit] //(calibrated in DBR mode)  //0.22549576167120f//(calibrated in PFC mode @750vdc)//
#define Vdc2_Sense_scaling      0.22498995580554f//[working in 12-bit]//(calibrated in DBR mode)  //0.22247805869952f//(calibrated in DBR mode @750vdc)//
#define Temp_Scaling            (float32_t)(3/4095) //(float32_t)(3/65535) //

//#define Vgrid_sense_offset_A  2251 //2265 //36060     //
#define Vgrid_sense_offset_B  2255 //36060     //
#define Vgrid_sense_offset_C  2251 //36060     //
#define VDC_sense_offset      2252

#define Vsens_grid_offset     1604
#define Vsens_grid_scaling    240.0f

#define Iconv_sense_offset_A  2265 // 36060    //
#define Iconv_sense_offset_B  2255 //36060    //
#define Iconv_sense_offset_C  2265 //36060    //
//
//Average current OFF set used in CMPSS
//
#define Vgrid_sense_offset    2252 //36080   //
#define Iconv_sense_offset    2251 //36064   //

//#else
//#endif
/**********ISRfreq&Linefreq Defines**********/
#define ISR_FREQUENCY   (float32_t)(Fswitching)
#define ISR2_FREQUENCY_HZ  (Uint16)(1000)             //(Fswitching/100)
#define ISR3_FREQUENCY_HZ  (Uint16)(12800)
#define AC_FREQ_HZ      50

#define PI      ((float32_t)3.141592653589)
#define ON_ANG_TOL      ((float32_t)(PI/180.0f)*5.0f)        //off_angle tolerance is at 1 degree
#define OFF_ANG_TOL     ((float32_t)(PI/180.0f)*5.0f)        //off_angle tolerance is at 1 degree

//****************Analog Monitoring*************//

#define mon_5_peak2peak           (float32_t)1.5f
#define mon_10_peak2peak          (float32_t)3.0f

#define dac_count                 (float32_t)4095.0f
#define dac_count_factor          ((float32_t)(dac_count / 3.0f))

#define dac_offset                (float32_t)2048.0f

/*
 * ****************Voltage Monitoring
 */
#define V_out_rms                   (float32_t)300.0f

#define V_out_peak2peak             ((float32_t)(2.0f * 1.41421356f * V_out_rms))

#define V_mon_5_scalingFactor       ((float32_t)(mon_5_peak2peak / V_out_peak2peak))
#define V_mon_10_scalingFactor      ((float32_t)(mon_10_peak2peak / V_out_peak2peak))

#define V_dac_count_factor_5        ((float32_t)(V_mon_5_scalingFactor * dac_count_factor))
#define V_dac_count_factor_10       ((float32_t)(V_mon_10_scalingFactor * dac_count_factor))

/*
 * ****************Current Monitoring
 */
#define I_out_rms                   (float32_t)35.0f

#define I_out_peak2peak             ((float32_t)(2.0f * 1.41421356f * I_out_rms))

#define I_mon_5_scalingFactor       ((float32_t)(mon_5_peak2peak / I_out_peak2peak))
#define I_mon_10_scalingFactor      ((float32_t)(mon_10_peak2peak / I_out_peak2peak))

#define I_dac_count_factor_5        ((float32_t)(I_mon_5_scalingFactor * dac_count_factor))
#define I_dac_count_factor_10       ((float32_t)(I_mon_10_scalingFactor * dac_count_factor))


#endif /* PROJECT_DEFINES_H_ */
