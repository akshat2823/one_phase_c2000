////#############################################################################
////
//// FILE:     power_meas_sine_analyzer.h
////
//// TITLE:    Sine Analyzer with Power Measurement Module
////
////#############################################################################
//// $TI Release: Power Measurement Library v1.02.00.00 $
//// $Release Date: Thu Jan 30 00:21:55 CST 2025 $
//// $Copyright:
//// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
////
//// ALL RIGHTS RESERVED
//// $
////#############################################################################
//
//#ifndef POWER_MEAS_SINE_ANALYZER_H
//#define POWER_MEAS_SINE_ANALYZER_H
//
//#ifdef __cplusplus
//
//extern "C"
//{
//#endif
//
////*****************************************************************************
////
////! \addtogroup POWER_MEAS_SINE_ANALYZER
////! @{
////
////*****************************************************************************
//
////
//// Included Files
////
//#include <stdint.h>
//#ifndef __TMS320C28XX_CLA__
//#include <math.h>
//#else
//#include <CLAmath.h>
//#endif
//
////#############################################################################
////
//// Macro Definitions
////
////#############################################################################
//#ifndef C2000_IEEE754_TYPES
//#define C2000_IEEE754_TYPES
//#ifdef __TI_EABI__
//typedef float         float32_t;
//typedef double        float64_t;
//#else // TI COFF
//typedef float         float32_t;
//typedef long double   float64_t;
//#endif // __TI_EABI__
//#endif // C2000_IEEE754_TYPES
//
////! \brief Defines the POWER_MEAS_SINE_ANALYZER structure
////!
////! \details The POWER_MEAS_SINE_ANALYZER can be used to analyze the
////!          input sine wave and calculates several parameters like
////!          RMS, Average and Frequency
////!
//typedef volatile struct {
//    float32_t v;           //!< Input: Voltage Sine Signal
//    float32_t i;           //!< Input Current Signal
//    float32_t sampleFreq;  //!< Input: Signal Sampling Freq
//    float32_t threshold;   //!< Input: Voltage level corresponding to zero i/p
//    float32_t vRms;        //!< Output: RMS Value
//    float32_t vAvg;        //!< Output: Average Value
//    float32_t vEma;        //!< Output: Exponential Moving Average Value
//    float32_t acFreq;      //!< Output: Signal Freq
//    float32_t acFreqAvg;   //!< Output: Signal Freq
//    float32_t iRms;        //!< Output: RMS Value of current
//    float32_t pRms;        //!< Output: RMS Value of input power
//    float32_t vaRms;       //!< Output: RMS VA
//    float32_t powerFactor; //!< Output: powerFactor
//    int16_t  zcd;          //!< Output: Zero Cross detected
//
//    float32_t vSum;        //!< Internal : running sum for vac calculation over one sine cycles
//    float32_t vSqrSum;     //!< Internal : running sum for vacc square calculation over one sine cycle
//    float32_t iSqrSum;     //!< Internal : running sum for Iacc_rms calculation over one sine cycle
//    float32_t acFreqSum;   //!< Internal : running sum of acFreq
//    float32_t pSum;        //!< Internal : running sum for Pacc_rms calculation over one sine cycle
//    float32_t vaSumMul;    //!< Internal : running sum for Pacc_rms calculation over one sine cycle
//    float32_t vNorm;       //!< Internal: Normalized value of the input voltage
//    float32_t iNorm;       //!< Internal: Normalized value of the input current
//    int16_t  prevSign;     //!< Internal: Flag to detect ZCD
//    int16_t  currSign;     //!< Internal: Flag to detect ZCD
//    int32_t  nSamples;     //!< Internal: No of samples in one cycle of the sine wave
//    int32_t  nSamplesMin;  //!< Internal: Lowerbound for no of samples in one sine wave cycle
//    int32_t  nSamplesMax;  //!< Internal: Upperbound for no of samples in one sine wave cycle
//    float32_t inverse_nSamples; //!< Internal: 1/( No of samples in one cycle of the sine wave)
//    float32_t sqrt_inverse_nSamples; //!< Internal: sqrt(1/( No of samples in one cycle of the sine wave))
//    int16_t  slewPowerUpdate; //!< Internal: used to slew update of the power value
//    float32_t pRmsSumMul; //!< Internal: used to sum Pac value over multiple sine cycles (100)
//    int16_t jitterCount; //!< Internal: used to store jitter information due to noise on input
//    float32_t emaFilterMultiplier;  //!< Internal: multiplier value used for the exponential moving average filter
//
//    float32_t Vpeak_Pos;
//    float32_t Vpeak_Neg;
//    float32_t Ipeak_Pos;
//    float32_t Ipeak_Neg;
//
//} POWER_MEAS_SINE_ANALYZER;
//
////! \brief Resets internal data to zero
////! \param *v The POWER_MEAS_SINE_ANALYZER structure pointer
////!
//static inline void POWER_MEAS_SINE_ANALYZER_reset(POWER_MEAS_SINE_ANALYZER *v)
//{
//    v->vRms=0;
//    v->vAvg=0;
//    v->vEma=0;
//    v->acFreq=0;
//    v->iRms=0;
//    v->pRms=0;
//    v->vaRms=0;
//    v->powerFactor=0;
//    v->zcd=0;
//    v->vSum=0;
//    v->vSqrSum=0;
//    v->iSqrSum=0;
//    v->pSum=0;
//    v->vaSumMul=0;
//    v->vNorm=0;
//    v->iNorm=0;
//    v->prevSign=0;
//    v->currSign=0;
//    v->nSamples=0;
//    v->nSamplesMin = 0;
//    v->nSamplesMax = 0;
//    v->inverse_nSamples=0;
//    v->sqrt_inverse_nSamples=0;
//    v->pRmsSumMul=0;
//    v->acFreqSum=0;
//    v->acFreqAvg=0;
//    v->jitterCount=0;
//    v->emaFilterMultiplier=0;
//}
//
////! \brief Configures the power measurment module
////! \param *v The POWER_MEAS_SINE_ANALYZER structure pointer
////! \param isrFrequency Frequency at which SPLL module is run
////! \param threshold Threshold value to avoid zero crossing issues
////! \param gridMaxFreq Max grid frequency
////! \param gridMinFreq Min grid frequency
////!
//static inline void POWER_MEAS_SINE_ANALYZER_config(POWER_MEAS_SINE_ANALYZER *v,
//                                                   float32_t isrFrequency,
//                                                   float32_t threshold,
//                                                   float32_t gridMaxFreq,
//                                                   float32_t gridMinFreq)
//{
//    v->sampleFreq = (float)(isrFrequency);
//    v->threshold = (float)(threshold);
//    v->nSamplesMax=isrFrequency/gridMinFreq;
//    v->nSamplesMin=isrFrequency/gridMaxFreq;
//    v->emaFilterMultiplier=2.0f/isrFrequency;
//}
//
////! \brief Perform calculations using the POWER_MEAS_SINE_ANALYZER module
////! \param *v The POWER_MEAS_SINE_ANALYZER structure pointer
////!
//static inline void POWER_MEAS_SINE_ANALYZER_run(POWER_MEAS_SINE_ANALYZER *v)
//{
//    if(v->v > v->Vpeak_Pos) v->Vpeak_Pos = v->v;
//    if(v->v < v->Vpeak_Neg) v->Vpeak_Neg = v->v;
//
//    if(v->i > v->Ipeak_Pos) v->Ipeak_Pos = v->i;
//    if(v->i < v->Ipeak_Neg) v->Ipeak_Neg = v->i;
//
//    v->vNorm = fabsf(v->v);
//    v->iNorm = fabsf(v->i);
//    v->currSign = ( v->v > v->threshold) ? 1 : 0;
//    v->nSamples++;
//    v->vSum = v->vSum+v->vNorm;
//    v->vSqrSum = v->vSqrSum+(v->vNorm*v->vNorm);
//    v->vEma = v->vEma+(v->emaFilterMultiplier*(v->vNorm - v->vEma));
//    v->iSqrSum = v->iSqrSum+(v->iNorm*v->iNorm);
//    v->pSum = v->pSum+(v->i*v->v);
//    v->zcd=0;
//
//    if((v->prevSign != v->currSign) && (v->currSign == 1))
//    {
//        //
//        // check if the nSamples are in the ball park of a real frequency
//        // that can be on the grid, this is done by comparing the nSamples
//        // with the max value and min value it can be for the
//        // AC Grid Connection these Max and Min are initialized by the
//        // user in the code
//        //
//        if(v->nSamplesMin < v->nSamples )
//        {
//            v->zcd=1;
//            v->inverse_nSamples = (1.0f)/(v->nSamples);
//            v->sqrt_inverse_nSamples = sqrtf(v->inverse_nSamples);
//            v->vAvg = (v->vSum*v->inverse_nSamples);
//            v->vRms = sqrtf(v->vSqrSum)*v->sqrt_inverse_nSamples;
//            v->iRms = sqrtf(v->iSqrSum)*v->sqrt_inverse_nSamples;
//            v->pRmsSumMul = v->pRmsSumMul + (v->pSum*v->inverse_nSamples);
//            v->vaSumMul = v->vaSumMul + v->vRms*v->iRms;
//            v->acFreq = (v->sampleFreq*v->inverse_nSamples);
//            v->acFreqSum = v->acFreqSum + v->acFreq;
//
//            v->slewPowerUpdate++;
//
//            if(v->slewPowerUpdate >= 100)
//            {
//                v->slewPowerUpdate=0;
//                v->pRms = (v->pRmsSumMul*(0.01f));
//                v->pRmsSumMul = 0;
//                v->vaRms = v->vaSumMul * (0.01f);
//                v->vaSumMul = 0;
//                v->powerFactor=v->pRms/v->vaRms;
//                v->acFreqAvg=v->acFreqSum*0.01f;
//                v->acFreqSum=0;
//
//                v->Vpeak_Pos = -6000.0f;
//                v->Vpeak_Neg = 6000.0f;
//                v->Ipeak_Pos = -6000.0f;
//                v->Ipeak_Neg = 6000.0f;
//
//            }
//
//            v->jitterCount=0;
//
//            v->nSamples=0;
//            v->vSum=0;
//            v->vSqrSum=0;
//            v->iSqrSum=0;
//            v->pSum =0;
//        }
//        else
//        {
//            //
//            // otherwise it may be jitter ignore this reading
//            // but count the number of jitters you are getting
//            // but do not count to infinity as then when the grid comes back
//            // it will take too much time to wind down the jitter count
//            //
//            if(v->jitterCount<30)
//            {
//                v->jitterCount++;
//            }
//            v->nSamples=0;
//        }
//    }
//
//    if(v->nSamples>v->nSamplesMax || v->jitterCount>20)
//    {
//        //
//        // most certainly the AC voltage is not present
//        //
//        v->vRms = 0;
//        v->vAvg = 0;
//        v->vEma = 0;
//        v->acFreq=0;
//        v->iRms = 0;
//        v->pRms = 0;
//        v->vaRms =0;
//        v->powerFactor=0;
//
//        v->zcd=0;
//        v->vSum=0;
//        v->vSqrSum=0;
//        v->iSqrSum=0;
//        v->pSum=0;
//        v->vaSumMul=0;
//        v->pRmsSumMul = 0;
//        v->acFreqAvg = 0;
//        v->acFreqSum =0 ;
//        v->nSamples=0;
//        v->jitterCount=0;
//    }
//
//    v->prevSign = v->currSign;
//}
//
////*****************************************************************************
////
//// Close the Doxygen group.
////! @}
////
////*****************************************************************************
//
//#ifdef __cplusplus
//}
//#endif                                  // extern "C"
//
//#endif // end of _SineAlanyzer_diff_wPower_F_C_H_ definition
//
////
//// End of File
////
//






















//#############################################################################
//
// FILE:     power_meas_sine_analyzer.h
//
// TITLE:    Sine Analyzer with Power Measurement Module
//
//#############################################################################
// $TI Release: Power Measurement Library v1.02.00.00 $
// $Release Date: Thu Jan 30 00:21:55 CST 2025 $
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
//
// ALL RIGHTS RESERVED
// $
//#############################################################################

#ifndef POWER_MEAS_SINE_ANALYZER_H
#define POWER_MEAS_SINE_ANALYZER_H


#include <stdint.h>
#ifndef __TMS320C28XX_CLA__
#include <math.h>
#else
#include <CLAmath.h>
#endif

#include "emavg.h"

#define MAX_JITTER_COUNT     10U
//#define AC_LOSS_JITTER_CNT   30U

//#define FREQ_MIN_HZ        0.1f //5Hz
#define FREQ_MAX_HZ      1000.0f

#define ZCD_HYST_HIGH     0.5f
#define ZCD_HYST_LOW      0.2f

extern float32_t H_alpha;

extern float32_t updateRate;

//typedef struct
//{
//    /* Inputs (update these every ISR/sample) */
//    float32_t Va;
//    float32_t Ia;
//
//    /* Timing */
//    float32_t Ts;              // sample time (sec)
//    float32_t Fs;              // derived sample frequency (Hz)
////    float32_t Vth;             // threshold for crossing detect (V)
//
//    /* ZCD thresholds */
//    float32_t Vth_high;
//    float32_t Vth_low;
//
//    /* Per-cycle accumulators */
//    float32_t VaSum;
//    float32_t IaSum;
//    float32_t Va_rms_Sum;
//    float32_t Ia_rms_Sum;
//    float32_t Pa_sum;
//
//
//
//    /* Instantaneous power (optional) */
//    float32_t Pa_inst;
//
//    /* Computed results (per cycle) */
//    float32_t invSampleA;
//    float32_t Va_avgP;
//    float32_t Ia_avgP;
//    float32_t Va_rms;
//    float32_t Ia_rms;
//    float32_t Pa_avg;
//    float32_t Sa_apparent;
//    float32_t Frequency_A;
//
//    float32_t POS_PK;
//    float32_t NEG_PK;
//
//    /* 100-cycle averaging */
////    float32_t Pa_sum100;
////    float32_t Sa_sum100;
//    float32_t Power_RealA;
//    float32_t Power_ApparentA;
////    float32_t PF_A;
//    uint16_t  PhaseA_Average;     // 0..99
//
////    float32_t Frequency_A_sum100;
////
////    float32_t Va_rms_sum100;
////    float32_t Ia_rms_sum100;
////
////    float32_t Vrms_avg100;
////    float32_t Irms_avg100;
////    float32_t Freq_avg100;
//
//
//    /* ZCD / threshold-cross detect */
//    uint16_t  ZCD_A;              // pulse flag (0/1)
//    uint16_t  CurrSignPHA;
//    uint16_t  OldSignPHA;
//
//    uint16_t HalfCycleFlag;   // 0 or 1
//
//    /* Sample counter */
//    uint32_t  runSamplesA;
////    uint32_t  MinimumSample;
//    uint32_t  MinSamples;
//    uint32_t  MaxSamples;
//
//    /* Debug */
//    uint32_t  jitterCount;
//
//} POWER_MEAS_SINE_ANALYZER;


typedef struct
{
    float32_t Vacdc;
    float32_t Vac;

    float32_t Vac_old;
    float32_t Vacdc_old;

    float32_t Vac_prev_freq;

    float32_t Vacdc_rms;
    float32_t Vac_rms;
    float32_t Vdc_rms;
    float32_t Vacdc_avg;

    float32_t Vacdc_rms_Sum;
    float32_t Vac_rms_Sum;
    float32_t Vacdc_Sum;

    float32_t POS_PK;
    float32_t NEG_PK;
    float32_t POS_PK_DISP;
    float32_t NEG_PK_DISP;

    float32_t Freq;
    float32_t FreqFilt;
    float32_t FreqMin;
    float32_t FreqMax;

    float32_t lastCrossSample;

    uint32_t runSamplesA;
    uint32_t MaxSamples;

    uint32_t sampleCountFreq;
    uint16_t freqDetectReady;

    uint32_t ZCD[200];
    uint32_t index;

    /* Timing */
    float32_t Ts;
    float32_t Fs;

} POWER_MEAS_SINE_ANALYZER1;

//static inline void POWER_MEAS_SINE_ANALYZER_run(
//        volatile POWER_MEAS_SINE_ANALYZER *p)
//{
//    /* Peak tracking */
//    if (p->Va > p->POS_PK) p->POS_PK = p->Va;
//    if (p->Va < p->NEG_PK) p->NEG_PK = p->Va;
//
//    /* Accumulate */
//    p->VaSum       += p->Va;
//    p->IaSum       += p->Ia;
//    p->Va_rms_Sum  += p->Va * p->Va;
//    p->Ia_rms_Sum  += p->Ia * p->Ia;
//
//    p->Pa_inst = p->Va * p->Ia;
//    p->Pa_sum += p->Pa_inst;
//
//    /* ---------- Hysteresis-based sign detection ---------- */
//    if (p->Va > p->Vth_high)
//        p->CurrSignPHA = 1;
//    else if (p->Va < p->Vth_low)
//        p->CurrSignPHA = 0;
//
//    p->ZCD_A = 0;
//
//    /* ---------- Rising zero-cross detection ---------- */
//    if ((p->CurrSignPHA == 1) && (p->OldSignPHA == 0))
//    {
//        if ((p->runSamplesA >= p->MinSamples) &&
//            (p->runSamplesA <= p->MaxSamples))
//        {
//            /* ---------- VALID CYCLE ---------- */
//            p->ZCD_A = 1;
//
//            p->invSampleA = 1.0f / (float32_t)p->runSamplesA;
//            p->Frequency_A = 2.0f * (1.0f / (p->runSamplesA * p->Ts));
//
//            p->Va_avgP = p->VaSum * p->invSampleA;
//            p->Ia_avgP = p->IaSum * p->invSampleA;
//
//            p->Va_rms = sqrtf(p->Va_rms_Sum * p->invSampleA);
//            p->Ia_rms = sqrtf(p->Ia_rms_Sum * p->invSampleA);
//
//            p->Pa_avg = p->Pa_sum * p->invSampleA;
//            p->Sa_apparent = p->Va_rms * p->Ia_rms;
//
//            /* 100-cycle accumulation */
////            p->Pa_sum100          += p->Pa_avg;
////            p->Sa_sum100          += p->Sa_apparent;
////            p->Va_rms_sum100      += p->Va_rms;
////            p->Ia_rms_sum100      += p->Ia_rms;
////            p->Frequency_A_sum100 += p->Frequency_A;
//
//            p->PhaseA_Average++;
//
//            if (p->PhaseA_Average >= 100)
//            {
//                p->PhaseA_Average = 0;
//
////                p->Power_RealA     = p->Pa_sum100 * 0.01f;
////                p->Power_ApparentA = p->Sa_sum100 * 0.01f;
//
////                p->Vrms_avg100 = p->Va_rms_sum100 * 0.01f;
////                p->Irms_avg100 = p->Ia_rms_sum100 * 0.01f;
////                p->Freq_avg100 = p->Frequency_A_sum100 * 0.01f;
//
////                p->PF_A = (p->Power_ApparentA > 1e-6f) ?
////                           (p->Power_RealA / p->Power_ApparentA) : 0.0f;
//
////                p->Pa_sum100 = 0.0f;
////                p->Sa_sum100 = 0.0f;
////                p->Va_rms_sum100 = 0.0f;
////                p->Ia_rms_sum100 = 0.0f;
////                p->Frequency_A_sum100 = 0.0f;
//
//                p->POS_PK = -6000.0f;
//                p->NEG_PK =  6000.0f;
//            }
//
//            /* Reset per-cycle accumulators */
//            p->runSamplesA = 0;
//            p->VaSum = p->IaSum = 0.0f;
//            p->Va_rms_Sum = p->Ia_rms_Sum = 0.0f;
//            p->Pa_sum = 0.0f;
//            p->jitterCount = 0;
//        }
//        else
//        {
//            /* Invalid ZCD — ignore, do NOT reset counter */
//            if (p->jitterCount < MAX_JITTER_COUNT)
//                p->jitterCount++;
//        }
//    }
//
//    /* AC-loss protection */
//    if (p->runSamplesA > p->MaxSamples)
//    {
//        p->Frequency_A = 0.0f;
//        p->Va_rms = 0.0f;
//        p->Ia_rms = 0.0f;
//        p->Pa_avg = 0.0f;
////        p->PF_A   = 0.0f;
//
//        p->runSamplesA = 0;
//        p->jitterCount = 0;
//    }
//
//    p->runSamplesA++;
//    p->OldSignPHA = p->CurrSignPHA;
//}


static inline void POWER_MEAS_SINE_ANALYZER_run1(
        volatile POWER_MEAS_SINE_ANALYZER1 *p)
{
    float32_t temp = 0.0f;

    float32_t frac = 0.0f;
    float32_t thisCrossSample = 0.0f;
    float32_t periodSamples = 0.0f;
    float32_t freqNew = 0.0f;

    float32_t Max_diff = -5000.0f;

    float32_t diff = 0.0f;

    uint16_t i = 0;

    /* Peak tracking */
    if (p->Vacdc > p->POS_PK) p->POS_PK = p->Vacdc;
    if (p->Vacdc < p->NEG_PK) p->NEG_PK = p->Vacdc;

    p->MaxSamples = (uint32_t)(1.2f * (p->Fs / updateRate));  // == 2400 at 25Hz

    p->runSamplesA++;

    p->Vacdc_rms_Sum = p->Vacdc_rms_Sum + p->Vacdc * p->Vacdc;

    p->Vac = p->Vacdc - p->Vacdc_old + H_alpha*p->Vac_old;

    p->Vac_rms_Sum = p->Vac_rms_Sum + p->Vac * p->Vac;

    p->Vacdc_Sum = p->Vacdc_Sum + p->Vacdc;
// //***************************************************************************************
//    /******************************************************************
//     * FREQUENCY DETECTION
//     * Detect only positive-going zero crossing:
//     * previous Vac <= 0  and current Vac > 0
//     ******************************************************************/
    if ((p->Vac_old <= 0.0f) && (p->Vac > 0.0f))
    {
        if(p->index<20)
        {
            p->ZCD[p->index] = p->runSamplesA;
            p->index++;
        }


    }


//    if ((p->Vac_old <= 0.0f) && (p->Vac > 0.0f))
//    {
//        /* Linear interpolation:
//           crossing occurs between previous and current sample */
//        temp = p->Vac - p->Vac_prev_freq;
//
//        if (temp != 0.0f)
//        {
//            frac = (0.0f - p->Vac_prev_freq) / temp;
//        }
//        else
//        {
//            frac = 0.0f;
//        }
//
//        /* Sample index of this crossing */
//        thisCrossSample = ((float32_t)(p->sampleCountFreq - 1U)) + frac;
//
//        if (p->freqDetectReady == 1U)
//        {
//            periodSamples = thisCrossSample - p->lastCrossSample;
//
//            /* Validity check to reject false crossings/noise */
//            if ((periodSamples > 1.0f) && (periodSamples < (p->Fs * 2.0f)))
//            {
//                freqNew = p->Fs / periodSamples;
//
//                /* Optional range limit */
//                if ((freqNew >= p->FreqMin) && (freqNew <= p->FreqMax))
//                {
//                    p->Freq = freqNew;
//
//                    /* simple smoothing */
//                    p->FreqFilt = (0.9f * p->FreqFilt) + (0.1f * freqNew);
//                }
//            }
//        }
//        else
//        {
//            p->freqDetectReady = 1U;
//        }
//
//        p->lastCrossSample = thisCrossSample;
//    }
//
//    p->Vac_prev_freq = p->Vac;
//
// //***************************************************************************************

    p->Vac_old = p->Vac;

    p->Vacdc_old = p->Vacdc;

    if (p->runSamplesA >= p->MaxSamples)
    {
        p->Vacdc_rms =sqrtf( p->Vacdc_rms_Sum/p->MaxSamples) ;

        p->Vac_rms =sqrtf( p->Vac_rms_Sum/p->MaxSamples) ;

        p->Vacdc_avg = p->Vacdc_Sum / p->MaxSamples;

        temp = (p->Vacdc_rms * p->Vacdc_rms) - (p->Vac_rms * p->Vac_rms);

        if(temp<=0)
        {
            temp = 0;
        }

        p->Vdc_rms = sqrtf(temp);

        p->POS_PK_DISP = p->POS_PK;
        p->NEG_PK_DISP = p->NEG_PK;


        for(i=1;i<200;i++)
        {
            diff = p->ZCD[i]- p->ZCD[i-1] ;

            if(diff>0)
            {
                if(diff>Max_diff)
                {
                    Max_diff = diff;
                }
            }

        }

        if(Max_diff> 630 && Max_diff<12600 )
        {

        p->Freq = 50000.0f/Max_diff;
        }
        for(i=0;i<200;i++)
        {
            p->ZCD[i] = 0;
        }

        p->runSamplesA = 0;
        p->Vacdc_rms_Sum = 0;
        p->Vac_rms_Sum = 0;
        p->Vacdc_Sum = 0;
        p->POS_PK = -60000.0f;
        p->NEG_PK = 60000.0f;
        p->index = 0;
    }

}



//static inline void POWER_MEAS_SINE_ANALYZER_reset(volatile POWER_MEAS_SINE_ANALYZER *PowerAnalyzer)
//{
//    /* Inputs */
//    PowerAnalyzer->Va = 0.0f;
//    PowerAnalyzer->Ia = 0.0f;
//
//    /* Timing */
//    PowerAnalyzer->Ts = 0.0f;
//    PowerAnalyzer->Fs = 0.0f;
//    PowerAnalyzer->Vth_high = 0.0f;
//    PowerAnalyzer->Vth_low = 0.0f;
//
//    /* Per-cycle accumulators */
//    PowerAnalyzer->VaSum = 0.0f;
//    PowerAnalyzer->IaSum = 0.0f;
//
//    PowerAnalyzer->Va_rms_Sum = 0.0f;
//    PowerAnalyzer->Ia_rms_Sum = 0.0f;
//
//    PowerAnalyzer->Pa_sum  = 0.0f;
//    PowerAnalyzer->Pa_inst = 0.0f;
//
//    /* Computed results (per cycle) */
//    PowerAnalyzer->invSampleA = 0.0f;
//
//    PowerAnalyzer->Va_avgP = 0.0f;
//    PowerAnalyzer->Ia_avgP = 0.0f;
//
//    PowerAnalyzer->Va_rms = 0.0f;
//    PowerAnalyzer->Ia_rms = 0.0f;
//
//    PowerAnalyzer->Pa_avg = 0.0f;
//    PowerAnalyzer->Sa_apparent = 0.0f;
//
//    PowerAnalyzer->Frequency_A = 0.0f;
//
//    /* 100-cycle averaging */
////    PowerAnalyzer->Pa_sum100 = 0.0f;
////    PowerAnalyzer->Sa_sum100 = 0.0f;
////
////    PowerAnalyzer->Va_rms_sum100 = 0.0f;
////    PowerAnalyzer->Ia_rms_sum100 = 0.0f;
////    PowerAnalyzer->Frequency_A_sum100 = 0.0f;
//
//    PowerAnalyzer->Power_RealA     = 0.0f;
//    PowerAnalyzer->Power_ApparentA = 0.0f;
////    PowerAnalyzer->PF_A            = 0.0f;
//
////    PowerAnalyzer->PhaseA_Average = 0U;
//
//    /* ZCD / sign detection */
//    PowerAnalyzer->ZCD_A        = 0U;
//    PowerAnalyzer->CurrSignPHA = 0U;
//    PowerAnalyzer->OldSignPHA  = 0U;
//
//    /* Sample counters */
//    PowerAnalyzer->runSamplesA  = 0U;
//    PowerAnalyzer->MinSamples = 0U;
//    PowerAnalyzer->MaxSamples = 0U;
//
//    /* Debug */
//    PowerAnalyzer->jitterCount = 0U;
//}

static inline void POWER_MEAS_SINE_ANALYZER_config1(
        volatile POWER_MEAS_SINE_ANALYZER1 *p,
        float32_t Ts)
{
    p->Ts = Ts;
    p->Fs = 1.0f / Ts;

    //p->MinSamples = (uint32_t)(0.7f * (p->Fs / FREQ_MAX_HZ));  // == 35 at 1kHz
//    p->MaxSamples = (uint32_t)(1.2f * (p->Fs / FREQ_MIN_HZ));  // == 2400 at 25Hz
//    p->MaxSamples = (uint32_t)(1.2f * (p->Fs / updateRate));  // == 2400 at 25Hz

   // p->Vth_high = ZCD_HYST_HIGH;
    //p->Vth_low  = ZCD_HYST_LOW;

    p->POS_PK = -60000.0f;
    p->NEG_PK = 60000.0f;


    p->FreqMin = 20.0f;     // adjust as needed
    p->FreqMax = 500.0f;    // adjust as needed

}



#endif // end of _SineAlanyzer_diff_wPower_F_C_H_ definition

//
// End of File
//

