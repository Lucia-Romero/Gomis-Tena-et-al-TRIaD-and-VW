#include <math.h>
#include <stdio.h>
#include <iostream>
#include "humandata.h"
#include "human.h"

 
void human::stim(int x, int stim_here, int extra_stim_here)
{
     if (       fabs(t - (start + n * CL)) < 1e-6
                        || fabs(t - (start + n * CL + duration - dt)) < 1e-6
                        ||     (t > (start + n * CL) &&
                                t < (start + n * CL + duration - dt)) )
        {
                        if (Ist == 0.0)
                        {
                                if (CL != 1e6)
                                {
                                        p->vrest = p->v;
                                }
                        }
        }
 
        Ist = 0;
 
        if (x == stim_here)
        {
                                if (       fabs(t - (start + n * CL)) < 1e-6
                                                || fabs(t - (start + n * CL + duration - dt)) < 1e-6
                                                ||     (t > (start + n * CL) &&
                                                                t < (start + n * CL + duration - dt)) )
                                {
                                                Ist = amp;
                                }
                                else
                                {
                                        if (t > (start + n * CL + duration - dt))
                                        {
                                                n++;
                                        }
                                }
        }
 
        if ( extra_flag == 1)
        if (x == extra_stim_here)
        {
                                if ((fmod(t,CL) > extra_start)&&(fmod(t,CL) < extra_start+duration))
                                {
                                                Ist = 2.0 * amp;
                                }
        }
 
}

