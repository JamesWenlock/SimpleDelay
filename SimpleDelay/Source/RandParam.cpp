/*
  ==============================================================================

    RandParam.cpp
    Created: 17 Jan 2019 1:07:37pm
    Author:  Mick Marchan

  ==============================================================================
*/

#include "RandParam.h"

//==============================================================================
RandParam::RandParam(int numChannels, bool hasSync, int *RNG, float lo,
                     float hi, float syncLikelihood, float biLikelihood, std::string curve)
{
    this->numChannels = numChannels;
    this->hasSync = hasSync;
    this->lo = lo;
    this->hi = hi;
    this->syncLikelihood = syncLikelihood;
    this->biLikelihood = biLikelihood;
    this->curve = curve;
    
    // store RNG values
    int rngSize = numChannels + hasSync;
    this->RNG = (int *) malloc(sizeof(int) * rngSize);
    for(int i = 0; i < rngSize; i++) {
        this->RNG[i] = RNG[i];
    }
    
    // create space for parameter values
    this->val = (float *) malloc(sizeof(float) * numChannels);
}

RandParam::RandParam()
{
}

RandParam::~RandParam()
{
    free(RNG);
    free(val);
}
//==============================================================================
void RandParam::updateParam(int seed) {
    
    bool isSync = false;
    if (hasSync) {
        isSync = getRNG(RNG[numChannels], seed) < syncLikelihood;
    }
    
    for (int channel = 0; channel < numChannels; channel++) {
        val[channel] = 
    }
}

float RandParam::get(int channel) {
    // error if channel out of range?
    return val[channel];
}

float getRNG(int RNG, int seed) {
    return (seed % RNG) / (float) RNG;
}
