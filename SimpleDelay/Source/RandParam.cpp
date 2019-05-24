/*
  ==============================================================================

    RandParam.cpp
    Created: 17 Jan 2019 1:07:37pm
    Author:  Mick Marchan

  ==============================================================================
*/

#include "RandParam.h"
#include <cmath>

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
        int rngChannel = isSync ? 0 : channel;
        val[channel] = map(getRNG(RNG[rngChannel], seed));
    }
}

float RandParam::get(int channel) {
    // error if channel out of range?
    return val[channel];
}

float RandParam::getRNG(int RNG, int seed) {
    return (seed % RNG) / (float) RNG;
}

float RandParam::map(float input) {
    float range = hi - lo;
    float output = input;
    
    if (curve == "exp") {
        output = pow(expBase, (input + 1.0)) * (1.0 / (expBase * (expBase - 1.0)));
    } else if (curve == "bi") {
        output = input < biLikelihood;
    }
    
    output = output * range + lo;
    
    return output;
}
