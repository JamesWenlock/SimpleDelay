/*
 ==============================================================================
 
 RandParam.h
 Created: 17 Jan 2019 1:07:37pm
 Author:  Mick Marchan
 
 ==============================================================================
 */

#pragma once

#include <iostream>

class RandParam
{
public:
    RandParam();
    RandParam(int numChannels, bool hasSync, int *RNG, float lo,
              float hi, float syncLikelihood, float biLikelihood, std::string curve);
    ~RandParam();
    
    //==============================================================================
    void updateParam(int seed);
    float get(int channel);
    
private:
    const int expBase = 4;
    
    int numChannels;
    bool hasSync;
    int *RNG;
    float *val;
    float lo;
    float hi;
    float syncLikelihood;
    float biLikelihood;
    std::string curve;
    
    float getRNG(int RNG, int seed);
    float map(float input);
};
