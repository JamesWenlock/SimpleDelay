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
    LowpassFilter(int numChannels, float cutoffFreq, float sampleRate);
    ~LowpassFilter();
    
    //==============================================================================
    void put(int channel, float sample);
    float get(int channel);
    void calc(float cutoffFreq, float sampleRate);
    
private:
    int numChannels;
    //float cutoffFreq;
    //float damping;
    float sampleRate;
    //float inputDelayCoeff[3] = {0, 0, 0};
    //float outputDelayCoeff[3] = {0, 0, 0};
    float c;
    float y[2] = {0, 0};
    float x1[2] = {0, 0};
    float y1[2] = {0, 0};
    //DelayBuffer inputDelay;
    //DelayBuffer outputDelay;
};
