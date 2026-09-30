/*
 * power_meas_sine_analyzer.h
 *
 *  Created on: May 9, 2026
 *      Author: Anamitra
 */

#ifndef POWER_MEAS_SINE_ANALYZER_H_
#define POWER_MEAS_SINE_ANALYZER_H_

#include <stdint.h>
#include <math.h>
#include "hw_types.h"

typedef struct {

    // ======================================================
    // Input samples
    // ======================================================
    float32_t v;                    // voltage sample
    float32_t i;                    // current sample

    // ======================================================
    // Voltage measurement
    // ======================================================
    float32_t v_sum;
    float32_t v_squared_sum;
    float32_t v_trueRMS;
    float32_t v_DC;
    float32_t v_AC_RMS;
    float32_t V_POS_PK;
    float32_t V_NEG_PK;

    // ======================================================
    // Current measurement
    // ======================================================
    float32_t i_sum;
    float32_t i_squared_sum;
    float32_t i_trueRMS;
    float32_t i_DC;
    float32_t i_AC_RMS;
    float32_t I_POS_PK;
    float32_t I_NEG_PK;

    // ======================================================
    // Power measurement
    // ======================================================
    float32_t p_inst;               // instantaneous power = v * i
    float32_t p_sum;                // accumulated instantaneous power

    float32_t activePower;          // P, watt
    float32_t apparentPower;        // S, VA
    float32_t reactivePower;        // Q, VAR
    float32_t powerFactor;          // PF = P / S

    // Optional AC-only apparent power
    float32_t apparentPower_AC;     // Vac_rms * Iac_rms

    // ======================================================
    // Sampling information
    // ======================================================
    float32_t Fs;
    float32_t Ts;

    uint32_t maxSamples;
    uint32_t runSample;

    // ======================================================
    // Frequency estimator
    // ======================================================
    float32_t v_dc_est;              // slow DC estimator
    float32_t v_ac;                  // DC removed voltage
    float32_t prev_v_ac;             // previous AC sample

    float32_t dcAlpha;               // DC estimator coefficient

    float32_t freq_Hz;               // instant frequency
    float32_t freq_Hz_filt;          // filtered frequency
    float32_t freqAlpha;             // frequency filter coefficient

    float32_t hysteresis;            // zero-crossing hysteresis band

    uint32_t sampleCounter;          // continuously running sample counter
    float32_t lastCrossSample_f;     // previous zero crossing sample position

    uint16_t zeroCrossArmed;         // zero crossing arm flag
    uint16_t crossValid;             // first crossing completed flag
    uint16_t freqValid;              // frequency valid flag

    uint32_t samplesSinceCross;
    uint32_t timeoutSamples;

    float32_t minFreq_Hz;
    float32_t maxFreq_Hz;

} POWER_MEAS_SINE_ANALYZER;

//static inline void POWER_MEAS_SINE_ANALYZER_freqEstimator(
//        volatile POWER_MEAS_SINE_ANALYZER *p)
//{
//    float32_t crossingSample_f;
//    float32_t periodSamples;
//    float32_t frac;
//    float32_t denom;
//
//    /*
//     * Slow DC removal.
//     * This prevents DC offset from shifting the zero crossing point.
//     */
//    p->v_dc_est += p->dcAlpha * (p->v - p->v_dc_est);
//
//    p->v_ac = p->v - p->v_dc_est;
//
//    /*
//     * Arm zero-crossing only after signal goes sufficiently negative.
//     * This prevents noise around zero from creating false crossings.
//     */
//    if(p->v_ac < -p->hysteresis)
//    {
//        p->zeroCrossArmed = 1U;
//    }
//
//    /*
//     * Detect negative-to-positive zero crossing.
//     */
//    if((p->zeroCrossArmed == 1U) &&
//       (p->prev_v_ac < 0.0f) &&
//       (p->v_ac >= 0.0f))
//    {
//        /*
//         * Linear interpolation for more accurate crossing position.
//         *
//         * prev sample index = sampleCounter - 1
//         * current sample index = sampleCounter
//         */
//        denom = p->prev_v_ac - p->v_ac;
//
//        if(denom != 0.0f)
//        {
//            frac = p->prev_v_ac / denom;
//        }
//        else
//        {
//            frac = 0.0f;
//        }
//
//        crossingSample_f = ((float32_t)p->sampleCounter - 1.0f) + frac;
//
//        if(p->crossValid == 1U)
//        {
//            periodSamples = crossingSample_f - p->lastCrossSample_f;
//
//            if(periodSamples > 0.0f)
//            {
//                p->freq_Hz = p->Fs / periodSamples;
//
//                /*
//                 * Validate frequency range.
//                 */
//                if((p->freq_Hz >= p->minFreq_Hz) &&
//                   (p->freq_Hz <= p->maxFreq_Hz))
//                {
//                    if(p->freqValid == 0U)
//                    {
//                        p->freq_Hz_filt = p->freq_Hz;
//                        p->freqValid = 1U;
//                    }
//                    else
//                    {
//                        p->freq_Hz_filt += p->freqAlpha *
//                                           (p->freq_Hz - p->freq_Hz_filt);
//                    }
//                }
//            }
//        }
//
//        p->lastCrossSample_f = crossingSample_f;
//        p->crossValid = 1U;
//        p->zeroCrossArmed = 0U;
//        p->samplesSinceCross = 0U;
//    }
//
//    p->prev_v_ac = p->v_ac;
//
//    p->sampleCounter++;
//    p->samplesSinceCross++;
//
//    /*
//     * Timeout protection.
//     * If signal disappears or zero crossing stops, mark frequency invalid.
//     */
//    if(p->samplesSinceCross > p->timeoutSamples)
//    {
//        p->freqValid = 0U;
//        p->freq_Hz = 0.0f;
//        p->freq_Hz_filt = 0.0f;
//        p->crossValid = 0U;
//        p->zeroCrossArmed = 0U;
//        p->samplesSinceCross = 0U;
//    }
//}

////////////////////////////////////////////////////////////////////////////////

//static inline void POWER_MEAS_SINE_ANALYZER_freqEstimator(
//        volatile POWER_MEAS_SINE_ANALYZER *p,
//        float32_t expectedFreq)
//{
//    float32_t crossingSample_f;
//    float32_t periodSamples;
//    float32_t frac;
//    float32_t denom;
//
//    float32_t expectedPeriodSamples;
//    float32_t minAllowedPeriodSamples;
//    float32_t maxAllowedPeriodSamples;
//
//    /*
//     * Slow DC removal.
//     */
//    p->v_dc_est += p->dcAlpha * (p->v - p->v_dc_est);
//    p->v_ac = p->v - p->v_dc_est;
//
//    /*
//     * Arm only when signal goes sufficiently negative.
//     */
//    if(p->v_ac < -p->hysteresis)
//    {
//        p->zeroCrossArmed = 1U;
//    }
//
//    /*
//     * Detect negative-to-positive crossing, but not at 0V.
//     * Detect when signal crosses +hysteresis.
//     * This avoids false triggering due to noise near zero.
//     */
//    if((p->zeroCrossArmed == 1U) &&
//       (p->prev_v_ac < p->hysteresis) &&
//       (p->v_ac >= p->hysteresis))
//    {
//        /*
//         * Interpolate crossing of +hysteresis level.
//         */
//        denom = p->v_ac - p->prev_v_ac;
//
//        if(denom != 0.0f)
//        {
//            frac = (p->hysteresis - p->prev_v_ac) / denom;
//        }
//        else
//        {
//            frac = 0.0f;
//        }
//
//        if(frac < 0.0f)
//        {
//            frac = 0.0f;
//        }
//        else if(frac > 1.0f)
//        {
//            frac = 1.0f;
//        }
//
//        crossingSample_f = ((float32_t)p->sampleCounter - 1.0f) + frac;
//
//        if(p->crossValid == 1U)
//        {
//            periodSamples = crossingSample_f - p->lastCrossSample_f;
//
//            /*
//             * Command-frequency based validation.
//             * This is very important.
//             *
//             * Example:
//             * expectedFreq = 50Hz
//             * expectedPeriodSamples = 50000 / 50 = 1000 samples
//             *
//             * Accept only approx 50% to 200% range:
//             * 500 to 2000 samples.
//             *
//             * So false 500Hz detection:
//             * 500Hz period = 100 samples
//             * This will be rejected.
//             */
//            if(expectedFreq > 0.0f)
//            {
//                expectedPeriodSamples = p->Fs / expectedFreq;
//
//                minAllowedPeriodSamples = expectedPeriodSamples * 0.5f;
//                maxAllowedPeriodSamples = expectedPeriodSamples * 2.0f;
//            }
//            else
//            {
//                minAllowedPeriodSamples = p->Fs / p->maxFreq_Hz;
//                maxAllowedPeriodSamples = p->Fs / p->minFreq_Hz;
//            }
//
//            if((periodSamples >= minAllowedPeriodSamples) &&
//               (periodSamples <= maxAllowedPeriodSamples))
//            {
//                p->freq_Hz = p->Fs / periodSamples;
//
//                if((p->freq_Hz >= p->minFreq_Hz) &&
//                   (p->freq_Hz <= p->maxFreq_Hz))
//                {
//                    if(p->freqValid == 0U)
//                    {
//                        p->freq_Hz_filt = p->freq_Hz;
//                        p->freqValid = 1U;
//                    }
//                    else
//                    {
//                        p->freq_Hz_filt += p->freqAlpha *
//                                           (p->freq_Hz - p->freq_Hz_filt);
//                    }
//                }
//            }
//        }
//
//        p->lastCrossSample_f = crossingSample_f;
//        p->crossValid = 1U;
//        p->zeroCrossArmed = 0U;
//        p->samplesSinceCross = 0U;
//    }
//
//    p->prev_v_ac = p->v_ac;
//
//    p->sampleCounter++;
//    p->samplesSinceCross++;
//
//    if(p->samplesSinceCross > p->timeoutSamples)
//    {
//        p->freqValid = 0U;
//        p->freq_Hz = 0.0f;
//        p->freq_Hz_filt = 0.0f;
//        p->crossValid = 0U;
//        p->zeroCrossArmed = 0U;
//        p->samplesSinceCross = 0U;
//    }
//}

////////////////////////////////////////////////////////////////////////////

static inline void POWER_MEAS_SINE_ANALYZER_freqEstimator(
        volatile POWER_MEAS_SINE_ANALYZER *p,
        float32_t expectedFreq)
{
    float32_t crossingSample_f;
    float32_t periodSamples;
    float32_t frac;
    float32_t denom;

    float32_t expectedPeriodSamples;
    float32_t minAllowedPeriodSamples;
    float32_t maxAllowedPeriodSamples;

    uint16_t crossingAccepted = 0U;

    /*
     * Slow DC removal.
     */
    p->v_dc_est += p->dcAlpha * (p->v - p->v_dc_est);
    p->v_ac = p->v - p->v_dc_est;

    /*
     * Arm only when signal goes sufficiently negative.
     */
    if(p->v_ac < -p->hysteresis)
    {
        p->zeroCrossArmed = 1U;
    }

    /*
     * Detect negative-to-positive crossing at +hysteresis.
     */
    if((p->zeroCrossArmed == 1U) &&
       (p->prev_v_ac < p->hysteresis) &&
       (p->v_ac >= p->hysteresis))
    {
        denom = p->v_ac - p->prev_v_ac;

        if(denom != 0.0f)
        {
            frac = (p->hysteresis - p->prev_v_ac) / denom;
        }
        else
        {
            frac = 0.0f;
        }

        if(frac < 0.0f)
        {
            frac = 0.0f;
        }
        else if(frac > 1.0f)
        {
            frac = 1.0f;
        }

        crossingSample_f = ((float32_t)p->sampleCounter - 1.0f) + frac;

        /*
         * First valid crossing reference.
         * Do not calculate frequency on first crossing.
         */
        if(p->crossValid == 0U)
        {
            p->lastCrossSample_f = crossingSample_f;
            p->crossValid = 1U;
            crossingAccepted = 1U;
        }
        else
        {
            periodSamples = crossingSample_f - p->lastCrossSample_f;

            if(expectedFreq > 0.0f)
            {
                expectedPeriodSamples = p->Fs / expectedFreq;

                /*
                 * Tight validation.
                 * For 50Hz, expected = 1000 samples.
                 * Allowed = 800 to 1200 samples.
                 */
                minAllowedPeriodSamples = expectedPeriodSamples * 0.80f;
                maxAllowedPeriodSamples = expectedPeriodSamples * 1.20f;
            }
            else
            {
                minAllowedPeriodSamples = p->Fs / p->maxFreq_Hz;
                maxAllowedPeriodSamples = p->Fs / p->minFreq_Hz;
            }

            if((periodSamples >= minAllowedPeriodSamples) &&
               (periodSamples <= maxAllowedPeriodSamples))
            {
                p->freq_Hz = p->Fs / periodSamples;

                if((p->freq_Hz >= p->minFreq_Hz) &&
                   (p->freq_Hz <= p->maxFreq_Hz))
                {
                    if(p->freqValid == 0U)
                    {
                        p->freq_Hz_filt = p->freq_Hz;
                        p->freqValid = 1U;
                    }
                    else
                    {
                        p->freq_Hz_filt += p->freqAlpha *
                                           (p->freq_Hz - p->freq_Hz_filt);
                    }

                    /*
                     * Update previous crossing only after valid period.
                     */
                    p->lastCrossSample_f = crossingSample_f;
                    crossingAccepted = 1U;
                }
            }
        }

        /*
         * Disarm after crossing attempt.
         * It must go negative again before next positive crossing.
         */
        p->zeroCrossArmed = 0U;

        /*
         * Reset timeout only if crossing was accepted.
         */
        if(crossingAccepted == 1U)
        {
            p->samplesSinceCross = 0U;
        }
    }

    p->prev_v_ac = p->v_ac;

    p->sampleCounter++;
    p->samplesSinceCross++;

    if(p->samplesSinceCross > p->timeoutSamples)
    {
        p->freqValid = 0U;
        p->freq_Hz = 0.0f;
        p->freq_Hz_filt = 0.0f;
        p->crossValid = 0U;
        p->zeroCrossArmed = 0U;
        p->samplesSinceCross = 0U;
    }
}


static inline void POWER_MEAS_SINE_ANALYZER_run(
        volatile POWER_MEAS_SINE_ANALYZER *p, float32_t freq)
{
    float32_t v_ac_rms_sq;
    float32_t i_ac_rms_sq;
    float32_t q_sq;
    uint32_t N;
    float32_t freq_used;

    if(freq <= 0.0f)
    {
        return;
    }

    // ======================================================
    // Frequency Estimation
    // ======================================================
    POWER_MEAS_SINE_ANALYZER_freqEstimator(p, freq);

    /*
     * Use estimated frequency if valid.
     * Otherwise use commanded/output frequency.
     */
    if(p->freqValid == 1U)
    {
        freq_used = p->freq_Hz_filt;
    }
    else
    {
        freq_used = freq;
    }

    if(freq_used <= 0.0f)
    {
        return;
    }


    /*
     * Update sample window continuously based on present output frequency.
     * 10 cycles measurement window.
     */
    p->maxSamples = (uint32_t)((p->Fs / freq) * 10.0f);

    if(p->maxSamples < 10U)
    {
        p->maxSamples = 10U;
    }

    // ======================================================
    // RMS accumulation
    // ======================================================

    //a) Voltage accumulation
    p->v_sum += p->v;
    p->v_squared_sum += p->v * p->v;

    //b) Current accumulation
    p->i_sum += p->i;
    p->i_squared_sum += p->i * p->i;

    //c) Instantaneous power accumulation
    p->p_inst = p->v * p->i;
    p->p_sum += p->p_inst;


    p->runSample++;

    if(p->runSample >= p->maxSamples)
    {
        N = p->runSample;

        // ==================================================
        // Voltage calculations
        // ==================================================
        p->v_DC = p->v_sum / (float32_t)N;

        p->v_trueRMS = sqrtf(p->v_squared_sum / (float32_t)N);

        v_ac_rms_sq = (p->v_trueRMS * p->v_trueRMS) -
                      (p->v_DC * p->v_DC);

        if(v_ac_rms_sq < 0.0f)
        {
            v_ac_rms_sq = 0.0f;
        }

        p->v_AC_RMS = sqrtf(v_ac_rms_sq);

        /*
         * Peak calculated from RMS.
         * Suitable for sinusoidal output.
         */
        p->V_POS_PK = p->v_DC + (1.41421356f * p->v_AC_RMS);
        p->V_NEG_PK = p->v_DC - (1.41421356f * p->v_AC_RMS);

        // ==================================================
        // Current calculations
        // ==================================================
        p->i_DC = p->i_sum / (float32_t)N;

        p->i_trueRMS = sqrtf(p->i_squared_sum / (float32_t)N);

        i_ac_rms_sq = (p->i_trueRMS * p->i_trueRMS) -
                      (p->i_DC * p->i_DC);

        if(i_ac_rms_sq < 0.0f)
        {
            i_ac_rms_sq = 0.0f;
        }

        p->i_AC_RMS = sqrtf(i_ac_rms_sq);

        /*
         * Peak calculated from RMS.
         * Suitable for sinusoidal current.
         */
        p->I_POS_PK = p->i_DC + (1.41421356f * p->i_AC_RMS);
        p->I_NEG_PK = p->i_DC - (1.41421356f * p->i_AC_RMS);

        // ==================================================
        // Power calculations
        // ==================================================

        /*
         * Active power:
         * This is the most important and most reliable power calculation.
         * P = average of instantaneous v * i.
         */
        p->activePower = p->p_sum / (float32_t)N;
        if(p->activePower < 0) p->activePower = 0.0f;
        else{}

        /*
         * True apparent power.
         * Includes AC + DC component.
         */
        p->apparentPower = p->v_trueRMS * p->i_trueRMS;

        /*
         * AC-only apparent power.
         * Useful for AC source/load display.
         */
        p->apparentPower_AC = p->v_AC_RMS * p->i_AC_RMS;

        /*
         * Power factor.
         */
        if(p->apparentPower > 0.0001f)
        {
            p->powerFactor = p->activePower / p->apparentPower;
        }
        else
        {
            p->powerFactor = 0.0f;
        }

        /*
         * Limit PF between -1 and +1.
         */
        if(p->powerFactor > 1.0f)
        {
            p->powerFactor = 1.0f;
        }
        else if(p->powerFactor < 0.0f)
        {
            p->powerFactor = 0.0f;
        }

        /*
         * Reactive power magnitude.
         * Q = sqrt(S^2 - P^2)
         *
         * Note:
         * This gives magnitude of reactive power.
         * For signed reactive power, phase information or quadrature calculation is required.
         */
        q_sq = (p->apparentPower * p->apparentPower) -
               (p->activePower * p->activePower);

        if(q_sq < 0.0f)
        {
            q_sq = 0.0f;
        }

        p->reactivePower = sqrtf(q_sq);

        // ==================================================
        // Reset accumulators
        // ==================================================
        p->v_sum = 0.0f;
        p->v_squared_sum = 0.0f;

        p->i_sum = 0.0f;
        p->i_squared_sum = 0.0f;

        p->p_sum = 0.0f;

        p->runSample = 0U;
    }
}

static inline void POWER_MEAS_SINE_ANALYZER_config(
        volatile POWER_MEAS_SINE_ANALYZER *p,
        float32_t Ts,
        float32_t freq)
{
    p->Ts = Ts;
    p->Fs = 1.0f / p->Ts;

    // ======================================================
    // Input samples
    // ======================================================
    p->v = 0.0f;
    p->i = 0.0f;

    // ======================================================
    // Voltage variables
    // ======================================================
    p->v_sum = 0.0f;
    p->v_squared_sum = 0.0f;
    p->v_trueRMS = 0.0f;
    p->v_DC = 0.0f;
    p->v_AC_RMS = 0.0f;
    p->V_POS_PK = 0.0f;
    p->V_NEG_PK = 0.0f;

    // ======================================================
    // Current variables
    // ======================================================
    p->i_sum = 0.0f;
    p->i_squared_sum = 0.0f;
    p->i_trueRMS = 0.0f;
    p->i_DC = 0.0f;
    p->i_AC_RMS = 0.0f;
    p->I_POS_PK = 0.0f;
    p->I_NEG_PK = 0.0f;

    // ======================================================
    // Power variables
    // ======================================================
    p->p_inst = 0.0f;
    p->p_sum = 0.0f;

    p->activePower = 0.0f;
    p->apparentPower = 0.0f;
    p->apparentPower_AC = 0.0f;
    p->reactivePower = 0.0f;
    p->powerFactor = 0.0f;

    // ======================================================
    // Sampling variables
    // ======================================================
    p->runSample = 0U;

    if(freq > 0.0f)
    {
        p->maxSamples = (uint32_t)((p->Fs / freq) * 10.0f);
    }
    else
    {
        p->maxSamples = 1000U;
    }

    if(p->maxSamples < 10U)
    {
        p->maxSamples = 10U;
    }

    // ======================================================
    // Frequency estimator setup
    // ======================================================

    p->v_dc_est = 0.0f;
    p->v_ac = 0.0f;
    p->prev_v_ac = 0.0f;

    /*
     * DC estimator cutoff should be much lower than minimum AC frequency.
     * For minimum frequency = 25 Hz, choose DC estimator cutoff around 1 Hz.
     *
     * alpha approximately = 2*pi*fc/Fs
     * For fc = 1 Hz and Fs = 50000:
     * alpha = 0.0001256
     */
    p->dcAlpha = 0.0001256f;

    /*
     * Frequency display filter.
     * 0.05 means slow but stable.
     * 0.10 means faster.
     */
    p->freqAlpha = 0.02f; //0.10f; //0.05f;

    p->freq_Hz = 0.0f;
    p->freq_Hz_filt = 0.0f;

    /*
     * Hysteresis should be bigger than ADC noise.
     * If your voltage is in real volts, 2V to 5V is okay.
     */
    p->hysteresis = 4.0f; //2.0f;

    p->sampleCounter = 0U;
    p->lastCrossSample_f = 0.0f;

    p->zeroCrossArmed = 0U;
    p->crossValid = 0U;
    p->freqValid = 0U;

    p->samplesSinceCross = 0U;

    p->minFreq_Hz = 20.0f;
    p->maxFreq_Hz = 1200.0f;

    /*
     * Timeout:
     * If no crossing is detected for long time, frequency becomes invalid.
     * For minimum 20Hz, one cycle = Fs / 20.
     * Timeout = 3 cycles.
     */
    p->timeoutSamples = (uint32_t)((p->Fs / p->minFreq_Hz) * 3.0f);
}



#endif /* POWER_MEAS_SINE_ANALYZER_H_ */

































