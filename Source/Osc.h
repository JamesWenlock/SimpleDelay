/*
  ==============================================================================

    Osc.h
    Created: 25 Sep 2018 6:37:35pm
    Author:  DxLocal

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class Osc
{
public:
    Osc() {};
    Osc(dsp::LookupTable<float> *waveTable);
    ~Osc() {};
    
    float get(int sampleRate, float freq);
    
private:
    unsigned int tableSize;
    float index;
    dsp::LookupTable<float> *waveTable;
};
