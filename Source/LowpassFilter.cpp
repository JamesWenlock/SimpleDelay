/*
 ==============================================================================
 
 LowpassFilter.cpp
 Created: 30 Apr 2019 10:17:35pm
 Author:  Mick Marchan
 
 ==============================================================================
 */

#include "LowpassFilter.h"
#include <cmath>

//==============================================================================
LowpassFilter::LowpassFilter (int numChannels, float cutoffFreq, float sampleRate)
: numChannels (numChannels)
{
    // I think we only need to store two samples (since we are being passed the current input sample
    // and calculating the current output sample in the put function
    
    // calculate input and output delay buffer coefficients given cutoffFreq, sampleRate
    this->calc(cutoffFreq, sampleRate);
}

LowpassFilter::LowpassFilter()
{
}

LowpassFilter::~LowpassFilter()
{
}

//==============================================================================
void LowpassFilter::put(int channel, float sample)
{
    // double check that this formula is right. is a0 supposed to be positive or negative?
    // y(n) = bo * x(n) + b1 * x(n - 1) + b2 * x(n - 2) + a1 * y(n - 1) - a2 * y(n - 2)
    
    // here is my understanding of what variables correlate to what:
    // x[n] = sample
    // x[n-1] = inputDelay.getOffset(channel, 0)
    // x[n-2] = inputDelay.getOffset(channel, 1)
    // y[n-1] = outputDelay.getOffset(channel, 0)
    // y[n-2] = outputDelay.getOffset(channel, 1)
    // b0 - b2 = inputDelayCoeff[0 - 2]
    // a0 - a1 = outputDelayCoeff[1 - 2]
    // y(n) = cz(n)+2(n-l)-cy(n-l),
    // calculate y[n]
    // b0 * x[n]
    /*float y = inputDelayCoeff[0] * sample;
     // b1 * x[n - 1]
     y += inputDelayCoeff[1] * inputDelay.getOffset(channel, 0);
     // b2 * x[n - 2]
     y += inputDelayCoeff[2] * inputDelay.getOffset(channel, 1);
     // a1 * y[n - 1]
     y += outputDelayCoeff[0] * outputDelay.getOffset(channel, 1);
     // (- a2) * y[n - 2]
     y += (-1) * outputDelayCoeff[1] * outputDelay.getOffset(channel, 2);*/
    
    this->y[channel] = (this->c * sample) + this->x1[channel] - (this->c * y1[channel]);
    this->x1[channel] = sample;
    this->y1[channel] = this->y[channel];
    
    
    // After calculating y, we can update our delays
}

// Calculates frequency
void LowpassFilter::calc(float cutoffFreq, float sampleRate)
{
    //    this->cutoffFreq = cutoffFreq;
    //    this->damping = damping;
    
    
    float cFac = tan(M_PI * cutoffFreq / sampleRate);
    
    this->c = (cFac - 1) / (cFac + 1);
    
    /* float dFac = (2 * this->damping * cFac) + (pow(cFac, 2));
     
     inputDelayCoeff[0] = 1 / (1 + dFac);         //b0
     inputDelayCoeff[1] = 2 * inputDelayCoeff[0]; //b1
     inputDelayCoeff[2] = inputDelayCoeff[0];     //b2
     
     outputDelayCoeff[0] = inputDelayCoeff[1] * (1 - pow(cFac, 2)); //a1
     outputDelayCoeff[1] = inputDelayCoeff[0] * (1 - dFac); //a2
     */
}

float LowpassFilter::get(int channel)
{
    // returns y[n]
    return this->y[channel];
}
