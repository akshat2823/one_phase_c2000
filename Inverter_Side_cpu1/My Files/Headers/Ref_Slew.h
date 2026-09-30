/*
 * Ref_Slew.h
 *
 *  Created on: 07-Apr-2025
 *      Author: a
 */

#ifndef REF_SLEW_H_
#define REF_SLEW_H_

#include <stdint.h>
#include <math.h>

///////////Reference slew function///////////
typedef volatile struct
{
    float32_t  set_value;        // Input: set reference
    float32_t  slope;            // Parameter: slope in units/ms
    float32_t  out_slew;              // Output: slewed reference
}Ref_Slew_Ramp;

static inline void REFslew_reset(Ref_Slew_Ramp *v)
{
    v->out_slew=0;
}

static inline void REFslew_set(Ref_Slew_Ramp *v,float32_t initialVal)
{
    v->out_slew=initialVal;
}
static inline void REFslew_config(Ref_Slew_Ramp *v,float32_t set_Ref,float32_t slope)
{
    v->slope=(float32_t)(slope);
    v->set_value = set_Ref;
}

static inline void REFslew_run(Ref_Slew_Ramp *v,float32_t set_Ref,float32_t slope)
{
    v->slope=(float32_t)(slope);
    v->set_value = set_Ref;
    //
    // Slew out to set value
    //
    if(fabsf((v->set_value - v->out_slew)) > v->slope)
    {
        if(v->set_value > v->out_slew)
        {
            v->out_slew = v->out_slew + v->slope;
        }
        else
        {
            v->out_slew = v->out_slew - v->slope;
        }
    }

    else
    {
        v->out_slew = v->set_value;
    }
}

//////////////Ramp Generation/////////////////

typedef volatile struct {
    float32_t  freq;        // Input: Ramp frequency (pu)
    float32_t  stepAngleMax;// Parameter: Maximum step angle (pu)
    float32_t  out;         // Output: Ramp signal (pu)
} RAMP;
static inline void RAMP_reset(RAMP *v)
{
    v->out=0;
}

static inline void RAMP_run(RAMP *v,float32_t rampFrequency,float32_t isrFrequency)
{
    v->freq=rampFrequency;
    v->stepAngleMax=((float32_t)1.0)/isrFrequency;
    //
    // Compute the angle rate
    //
    v->out += (v->stepAngleMax*v->freq);

    //
    // Saturate the angle rate within (0,1)
    //
    if (v->out>(1.0f))
    {
        v->out -= (1.0f);
    }
}

// negative ramp
typedef volatile struct {
    float32_t  freq;        // Input: Ramp frequency (pu)
    float32_t  stepAngleMax;// Parameter: Maximum step angle (pu)
    float32_t  out;         // Output: Ramp signal (pu)
} RAMP_NEG;
static inline void RAMP_NEG_reset(RAMP_NEG *v)
{
    v->out=1;
}

static inline void RAMP_NEG_run(RAMP_NEG *v,float32_t rampFrequency,float32_t isrFrequency)
{
    v->freq=rampFrequency;
    v->stepAngleMax=((float32_t)1.0)/isrFrequency;
    //
    // Compute the angle rate
    //
    v->out -= (v->stepAngleMax*v->freq);

    //
    // Saturate the angle rate within (0,1)
    //
    if (v->out<(0.0f))
    {
        v->out = (1.0f);
    }
}

//triangle
typedef volatile struct {
    float32_t  freq;        // Input: Ramp frequency (pu)
    float32_t  stepAngleMax;// Parameter: Maximum step angle (pu)
    float32_t  out;         // Output: Ramp signal (pu)
} tri;
static inline void tri_reset(tri *v)
{
    v->out=0;
}

static inline void tri_run(tri *v,float32_t rampFrequency,float32_t isrFrequency,float32_t ZCD)
{
    v->freq=rampFrequency;
    v->stepAngleMax=((float32_t)1.0)/(2.0f*isrFrequency);

    if (ZCD == 1.0f)
    {
        v->out += (v->stepAngleMax*v->freq);
    }
    else if(ZCD == -1.0f)
    {
        v->out -= (v->stepAngleMax*v->freq);
    }
}



#endif /* REF_SLEW_H_ */
