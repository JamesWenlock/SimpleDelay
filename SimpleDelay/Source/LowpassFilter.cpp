/*
  ==============================================================================

    LowpassFilter.cpp
    Created: 30 Apr 2019 10:17:35pm
    Author:  Mick Marchan

  ==============================================================================
*/

#include "LowpassFilter.h"

//==============================================================================
LowpassFilter::LowpassFilter (int numChannels, float cutoffFreq, float damping, float sampleRate)
: numChannels (numChannels), cutoffFreq (cutoffFreq), damping (damping), sampleRate (sampleRate)
{
    // I think we only need to store two samples (since we are being passed the current input sample
    // and calculating the current output sample in the put function
    inputDelay = DelayBuffer(2, numChannels);
    outputDelay = DelayBuffer(2, numChannels);
    // calculate input and output delay buffer coefficients given cutoffFreq, sampleRate
    inputDelayCoeff[0] = 1;
    inputDelayCoeff[1] = 2;
    inputDelayCoeff[2] = 3;
    
    outputDelayCoeff[0] = 1;
    outputDelayCoeff[1] = 2;
    outputDelayCoeff[2] = 3;
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
    // calculate y[n]
    // double check that this formula is right. is a0 supposed to be positive or negative?
    // y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a0 * y[n-1] - a1 * y[n-2]
    float y;
    
    // here is my understanding of what variables correlate to what:
    // x[n] = sample
    // x[n-1] = inputDelay.getOffset(channel, 0)
    // x[n-2] = inputDelay.getOffset(channel, 1)
    // y[n-1] = outputDelay.getOffset(channel, 0)
    // y[n-2] = outputDelay.getOffset(channel, 1)
    // b0 - b2 = inputDelayCoeff[0 - 2]
    // a0 - a1 = outputDelayCoeff[1 - 2]
    
    // After calculating y, we can update our delays
}

float LowpassFilter::get(int channel)
{
    // returns y[n]
    return outputDelay.getOffset(channel, 0);
}
