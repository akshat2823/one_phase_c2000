/*
 * Ref_Gen.c
 *
 *  Created on: Dec 11, 2025
 *      Author: admin
 */

#include "Ref_Gen.h"
#include "Control_Variables.h"


uint16_t i;
uint16_t j;

float32_t thetaBase;
float32_t harmonicAngle;
float32_t resultA;
float32_t outA;

#define DEG_TO_RAD                                          (0.01745329251994329577f)

#define LOAD_HARMONIC_A(index, no_var, amp_var, pha_var)     \
    do                                                       \
    {                                                        \
        HarmonicA[(index)][0] = (no_var);                    \
        HarmonicA[(index)][1] = (amp_var);                   \
        HarmonicA[(index)][2] = (pha_var) * DEG_TO_RAD;      \
    } while(0)




void Harmonic_Array_clear(void)
{
    uint16_t i;
    i = 0;
    for(i = 0; i < MAX_HARMONIC_NO; i++)
    {
        //Phase A
        HarmonicA[i][0] = 0.0f;   // harmonic number
        HarmonicA[i][1] = 0.0f;   // amplitude
        HarmonicA[i][2] = 0.0f;   // phase
        //Phase B
        HarmonicB[i][0] = 0.0f;   // harmonic number
        HarmonicB[i][1] = 0.0f;   // amplitude
        HarmonicB[i][2] = 0.0f;   // phase
        //Phase C
        HarmonicC[i][0] = 0.0f;   // harmonic number
        HarmonicC[i][1] = 0.0f;   // amplitude
        HarmonicC[i][2] = 0.0f;   // phase
    }
}

void Harmonic_Array_Init(void)
{
    /* Fundamental only */
    HarmonicA[0][0] = 1.0f;     HarmonicA[0][1] = 100.0f;      HarmonicA[0][2] = 0.0f;
//    HarmonicB[0][0] = 1.0f;     HarmonicB[0][1] = 1.0f;      HarmonicB[0][2] = 0.0f;
//    HarmonicC[0][0] = 1.0f;     HarmonicC[0][1] = 1.0f;      HarmonicC[0][2] = 0.0f;

//    HarmonicA[1][0] = 2.0f;     HarmonicA[1][1] = 0.0219f;   HarmonicA[1][2] = 0.0f;

//    HarmonicA[2][0] = 3.0f;     HarmonicA[2][1] = 0.33f;   HarmonicA[2][2] = 0.0f;

//    HarmonicA[3][0] = 4.0f;     HarmonicA[3][1] = 0.0f;      HarmonicA[3][2] = 0.0f;

//    HarmonicA[4][0] = 5.0f;     HarmonicA[4][1] = 0.2f;   HarmonicA[4][2] = 0.0f;

//    HarmonicA[5][0] = 6.0f;     HarmonicA[5][1] = 0.0f;      HarmonicA[5][2] = 0.0f;

//    HarmonicA[6][0] = 7.0f;     HarmonicA[6][1] = 0.14f;   HarmonicA[6][2] = 0.0f;

//    HarmonicA[7][0] = 8.0f;     HarmonicA[7][1] = 0.0234f;   HarmonicA[7][2] = 0.0f;

//    HarmonicA[8][0] = 9.0f;     HarmonicA[8][1] = 0.11f;   HarmonicA[8][2] = 0.0f;
}

void updateBaseLookUpTable(void)
{


    for(i = 0U; i < LUT_SIZE; i++)
    {
        thetaBase = ((float32_t)i * Angle_Step);
        resultA = 0.0f;
        for(j = 0U; j < MAX_HARMONIC_NO; j++)
        {
            if(HarmonicA[j][0] <= 0.0f)
            {
                continue;
            }

            harmonicAngle = (HarmonicA[j][0] * thetaBase)+ HarmonicA[j][2];
            resultA += sinf(harmonicAngle) * HarmonicA[j][1] * 0.01f;
        }

        outA = resultA * 32767.0f;

        /* Saturation */
        if(outA > 32767.0f)
        {
            outA = 32767.0f;
        }
        else if(outA < -32768.0f)
        {
            outA = -32768.0f;
        }


        BaseLUT_A[i] = (signed int)outA;
    }
}
void Load_Received_Harmonics_To_Array(void)
{
    /* ================================================================
     * Harmonic 1
     *
     * Keep fundamental explicitly at 100%.
     *
     * If you want harmonic-1 amplitude also from MCU,
     * replace 100.0f with harm1_amp.
     * ================================================================ */

    HarmonicA[0][0] = 1.0f;
    HarmonicA[0][1] = 100.0f;
    HarmonicA[0][2] = harm1_pha;


    /* ================================================================
     * Harmonics 2 ... 50
     * ================================================================ */

    LOAD_HARMONIC_A(1U,  harm2_no,  harm2_amp,  harm2_pha);
    LOAD_HARMONIC_A(2U,  harm3_no,  harm3_amp,  harm3_pha);
    LOAD_HARMONIC_A(3U,  harm4_no,  harm4_amp,  harm4_pha);
    LOAD_HARMONIC_A(4U,  harm5_no,  harm5_amp,  harm5_pha);

    LOAD_HARMONIC_A(5U,  harm6_no,  harm6_amp,  harm6_pha);
    LOAD_HARMONIC_A(6U,  harm7_no,  harm7_amp,  harm7_pha);
    LOAD_HARMONIC_A(7U,  harm8_no,  harm8_amp,  harm8_pha);
    LOAD_HARMONIC_A(8U,  harm9_no,  harm9_amp,  harm9_pha);
    LOAD_HARMONIC_A(9U,  harm10_no, harm10_amp, harm10_pha);

    LOAD_HARMONIC_A(10U, harm11_no, harm11_amp, harm11_pha);
    LOAD_HARMONIC_A(11U, harm12_no, harm12_amp, harm12_pha);
    LOAD_HARMONIC_A(12U, harm13_no, harm13_amp, harm13_pha);
    LOAD_HARMONIC_A(13U, harm14_no, harm14_amp, harm14_pha);
    LOAD_HARMONIC_A(14U, harm15_no, harm15_amp, harm15_pha);

    LOAD_HARMONIC_A(15U, harm16_no, harm16_amp, harm16_pha);
    LOAD_HARMONIC_A(16U, harm17_no, harm17_amp, harm17_pha);
    LOAD_HARMONIC_A(17U, harm18_no, harm18_amp, harm18_pha);
    LOAD_HARMONIC_A(18U, harm19_no, harm19_amp, harm19_pha);
    LOAD_HARMONIC_A(19U, harm20_no, harm20_amp, harm20_pha);

    LOAD_HARMONIC_A(20U, harm21_no, harm21_amp, harm21_pha);
    LOAD_HARMONIC_A(21U, harm22_no, harm22_amp, harm22_pha);
    LOAD_HARMONIC_A(22U, harm23_no, harm23_amp, harm23_pha);
    LOAD_HARMONIC_A(23U, harm24_no, harm24_amp, harm24_pha);
    LOAD_HARMONIC_A(24U, harm25_no, harm25_amp, harm25_pha);

    LOAD_HARMONIC_A(25U, harm26_no, harm26_amp, harm26_pha);
    LOAD_HARMONIC_A(26U, harm27_no, harm27_amp, harm27_pha);
    LOAD_HARMONIC_A(27U, harm28_no, harm28_amp, harm28_pha);
    LOAD_HARMONIC_A(28U, harm29_no, harm29_amp, harm29_pha);
    LOAD_HARMONIC_A(29U, harm30_no, harm30_amp, harm30_pha);

    LOAD_HARMONIC_A(30U, harm31_no, harm31_amp, harm31_pha);
    LOAD_HARMONIC_A(31U, harm32_no, harm32_amp, harm32_pha);
    LOAD_HARMONIC_A(32U, harm33_no, harm33_amp, harm33_pha);
    LOAD_HARMONIC_A(33U, harm34_no, harm34_amp, harm34_pha);
    LOAD_HARMONIC_A(34U, harm35_no, harm35_amp, harm35_pha);

    LOAD_HARMONIC_A(35U, harm36_no, harm36_amp, harm36_pha);
    LOAD_HARMONIC_A(36U, harm37_no, harm37_amp, harm37_pha);
    LOAD_HARMONIC_A(37U, harm38_no, harm38_amp, harm38_pha);
    LOAD_HARMONIC_A(38U, harm39_no, harm39_amp, harm39_pha);
    LOAD_HARMONIC_A(39U, harm40_no, harm40_amp, harm40_pha);

    LOAD_HARMONIC_A(40U, harm41_no, harm41_amp, harm41_pha);
    LOAD_HARMONIC_A(41U, harm42_no, harm42_amp, harm42_pha);
    LOAD_HARMONIC_A(42U, harm43_no, harm43_amp, harm43_pha);
    LOAD_HARMONIC_A(43U, harm44_no, harm44_amp, harm44_pha);
    LOAD_HARMONIC_A(44U, harm45_no, harm45_amp, harm45_pha);

    LOAD_HARMONIC_A(45U, harm46_no, harm46_amp, harm46_pha);
    LOAD_HARMONIC_A(46U, harm47_no, harm47_amp, harm47_pha);
    LOAD_HARMONIC_A(47U, harm48_no, harm48_amp, harm48_pha);
    LOAD_HARMONIC_A(48U, harm49_no, harm49_amp, harm49_pha);
    LOAD_HARMONIC_A(49U, harm50_no, harm50_amp, harm50_pha);
}




















