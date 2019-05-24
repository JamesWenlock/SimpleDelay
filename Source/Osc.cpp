/*
  ==============================================================================

    Osc.cpp
    Created: 25 Sep 2018 6:37:35pm
    Author:  DxLocal

  ==============================================================================
*/

#include "Osc.h"
#include "math.h"

Osc::Osc(dsp::LookupTable<float> * waveTable) : index (0), waveTable (waveTable)
{
    
};

float Osc::get(int sampleRate, float freq) {
    float result = waveTable->get(index * waveTable->getNumPoints());
    float deltaCycles = freq / sampleRate;
    index += deltaCycles;
    index = fmod(index, 1);
    while (index < 0) index += 1;
    return result;
}
