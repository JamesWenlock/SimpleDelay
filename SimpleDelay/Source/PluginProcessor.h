/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayBuffer.h"
#include "Osc.h"

//==============================================================================
/**
*/
class SimpleDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimpleDelayAudioProcessor();
    ~SimpleDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    static const int NUM_CHANNELS = 2;
    static const int SYNC_INDEX = NUM_CHANNELS;
    // TODO: FIND A BETTER SOLUTION THAN BEING AN INT. CANT USE STATIC CONST FLOAT
    static const int MAX_DELAY = 3;
    
    int seed;
    
    // Current delay duration
    int CUR_DELAY_RNG[NUM_CHANNELS + 1] = {4721, 9732, 8753};
    float curDelay[NUM_CHANNELS];
    float curDelaySync = 0.5;
    float curDelayLo = 0;
    float curDelayHi = MAX_DELAY;
    
    // Mod width
    int MOD_WIDTH_RNG[NUM_CHANNELS + 1] = {10437, 6321, 8534};
    float modWidth[NUM_CHANNELS];
    float modWidthSync = 0.5;
    // better values? 0.001, 0.1
    // TODO: Maybe width should be based on frequency, as that will determine the amount of pitch shifting
    float modWidthLo = 0;
    float modWidthHi = 0.01;
    
    // Mod freq
    int MOD_FREQ_RNG[NUM_CHANNELS + 1] = {8567, 5622, 23487};
    float modFreq[NUM_CHANNELS];
    float modFreqSync = 0.5;
    float modFreqLo = 0.01;
    float modFreqHi = 19;
    
    // Feedback constant: g
    int G_RNG[NUM_CHANNELS + 1] = {7236, 11523, 23462};
    float g[NUM_CHANNELS];
    float gSync = 0.5;
    float gLo = 0;
    float gHi = 0.8732;
    
    // Cross feedback
    int G_CROSS_RNG[NUM_CHANNELS + 1] = {3716, 12474, 67543};
    float gCross[NUM_CHANNELS];
    float gCrossSync = 0.5;
    float gCrossLo = 0;
    float gCrossHi = 0.8732;
    
    // Feedback cutoff frequency
    // TODO: CHANGE THIS TO FREQUENCY VALUE ONCE FILTER IS CORRECTED
    int CUTOFF_RNG[NUM_CHANNELS + 1] = {47123, 23784, 12334};
    float cutoff[NUM_CHANNELS];
    float cutoffSync = 0.5;
    float cutoffLo = 1;
    float cutoffHi = 20;
    
private:
    DelayBuffer delayBuf;
    DelayBuffer damp;
    dsp::LookupTable<float> waveTable;
    unsigned int tableSize;
    Osc mod[NUM_CHANNELS];
    float wet, dry;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessor)
};
