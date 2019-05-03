/*
  ==============================================================================

    LowpassFilter.h
    Created: 30 Apr 2019 10:17:35pm
    Author:  Mick Marchan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayBuffer.h"

//==============================================================================
/**
 */
class LowpassFilter
{
public:
    LowpassFilter();
    LowpassFilter(int numChannels, float cutoffFreq, float damping, float sampleRate);
    ~LowpassFilter();
    
    //==============================================================================
    void put(int channel, float sample);
    float get(int channel);
    
private:
    int numChannels;
    float cutoffFreq;
    float damping;
    float sampleRate;
    float inputDelayCoeff[3];
    float outputDelayCoeff[3];
    DelayBuffer inputDelay;
    DelayBuffer outputDelay;
};
