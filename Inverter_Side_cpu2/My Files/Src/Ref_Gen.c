/*
 * Ref_Gen.c
 *
 *  Created on: Dec 11, 2025
 *      Author: admin
 */

#include "Ref_Gen.h"

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
    uint16_t i, j;

    for(i = 0; i < LUT_SIZE; i++)
    {
        float theta_base = (float)i * Angle_Step;

        float ResultA = 0.0f;
        float ResultB = 0.0f;
        float ResultC = 0.0f;

        for(j = 0; j < MAX_HARMONIC_NO; j++)
        {
            /* Phase A */
//            float TimeA = (HarmonicA[j][0] * theta_base) + HarmonicA[j][2];
//            ResultA += sinf(TimeA) * HarmonicA[j][1] * 0.01f;

            if(j == 0)
            {
                float TimeA = (1.0f * theta_base) + HarmonicA[j][2];
                ResultA += sinf(TimeA) * HarmonicA[j][1] * 0.01f;
            }
            else
            {
                float TimeA = (HarmonicA[j][0] * theta_base) + HarmonicA[j][2];
                ResultA += sinf(TimeA) * HarmonicA[j][1] * 0.01f;
            }

//            /* Phase B */
//            float TimeB = (HarmonicB[j][0] * theta_base) + HarmonicB[j][2];
//            ResultB += sinf(TimeB) * HarmonicB[j][1];
//
//            /* Phase C */
//            float TimeC = (HarmonicC[j][0] * theta_base) + HarmonicC[j][2];
//            ResultC += sinf(TimeC) * HarmonicC[j][1];
        }

        /* Scale */
        float OutA = ResultA * 32767.0f;
//        float OutB = ResultB * 32767.0f;
//        float OutC = ResultC * 32767.0f;

        /* Saturate */
        if(OutA >  32767.0f) OutA =  32767.0f;
        if(OutA < -32768.0f) OutA = -32768.0f;

//        if(OutB >  32767.0f) OutB =  32767.0f;
//        if(OutB < -32768.0f) OutB = -32768.0f;
//
//        if(OutC >  32767.0f) OutC =  32767.0f;
//        if(OutC < -32768.0f) OutC = -32768.0f;

        /* Store */
        BaseLUT_A[i] = (signed int)OutA;
//        BaseLUT_B[i] = (signed int)OutB;
//        BaseLUT_C[i] = (signed int)OutC;
    }
}
























