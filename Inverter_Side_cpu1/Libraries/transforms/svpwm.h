/*
 * svpwm.h
 *
 *  Created on: 05-Jan-2023
 *      Author: rndl6
 */

#ifndef LIBRARIES_TRANSFORMS_SVPWM_H_
#define LIBRARIES_TRANSFORMS_SVPWM_H_
#include <math.h>
#include "f28x_project.h"
#include "device.h"
#include "driverlib.h"

typedef struct  {
                  float32_t  Ualpha;          // Input: reference alpha-axis phase voltage
                  float32_t  Ubeta;           // Input: reference beta-axis phase voltage
                  float32_t  Ta;              // Variable: Two Level duty phase-a
                  float32_t  Tb;              // Variable: Two Level duty phase-b
                  float32_t  Tc;              // Variable: Two Level duty phase-c
                  float32_t  tmp1;            // Variable: temp variable
                  float32_t  tmp2;            // Variable: temp variable
                  float32_t  tmp3;            // Variable: temp variable
                  Uint16 VecSector;           // Space vector sector
                } SVGEN_2LVL;

static inline void SVGEN_2LVL_run(SVGEN_2LVL*v,float32_t alpha,float32_t beta)
{
    v->Ualpha = alpha;
    v->Ubeta = beta;
    v->tmp1= v->Ubeta;
    v->tmp2= 0.5f*(v->Ubeta) + 0.866*v->Ualpha;
    v->tmp3= v->tmp2 - v->tmp1;

    v->VecSector=3;
    v->VecSector=(v->tmp2> 0)?( v->VecSector-1):v->VecSector;
    v->VecSector=(v->tmp3> 0)?( v->VecSector-1):v->VecSector;
    v->VecSector=(v->tmp1< 0)?(7-v->VecSector) :v->VecSector;

    if     (v->VecSector==1 || v->VecSector==4)
      {     v->Ta= v->tmp2;
            v->Tb= v->tmp1-v->tmp3;
            v->Tc=-v->tmp2;
      }

    else if(v->VecSector==2 || v->VecSector==5)
      {     v->Ta= v->tmp3+v->tmp2;
            v->Tb= v->tmp1;
            v->Tc=-v->tmp1;
      }

    else
      {     v->Ta= v->tmp3;
            v->Tb=-v->tmp3;
            v->Tc=-(v->tmp1+v->tmp2);
      }
}
#endif /* LIBRARIES_TRANSFORMS_SVPWM_H_ */
