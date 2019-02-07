/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayBuffer.h"
#include "RandParam.h"
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
    float curDelaySync = 0.5;
    float curDelayLo = 0.001;
    float curDelayHi = MAX_DELAY;
    RandParam curDelay = RandParam(2, true, CUR_DELAY_RNG, curDelayLo, curDelayHi, curDelaySync, 0, "exp");
    
    // Mod width
    int MOD_WIDTH_RNG[NUM_CHANNELS + 1] = {10437, 6321, 8534};
    float modWidthSync = 0.5;
    // better values? 0.001, 0.1
    // TODO: Maybe width should be based on frequency, as that will determine the amount of pitch shifting
    float modWidthLo = 0;
    float modWidthHi = 0.01;
    RandParam modWidth = RandParam(2, true, MOD_WIDTH_RNG, modWidthLo, modWidthHi, modWidthSync, 0, "lin");
    
    // Mod freq
    int MOD_FREQ_RNG[NUM_CHANNELS + 1] = {8567, 5622, 23487};
    float modFreqSync = 0.5;
    float modFreqLo = 0.01;
    float modFreqHi = 19;
    RandParam modFreq = RandParam(2, true, MOD_FREQ_RNG, modFreqLo, modFreqHi, modFreqSync, 0, "exp");
    
    // Feedback constant: g
    int G_RNG[NUM_CHANNELS + 1] = {7236, 11523, 23462};
    float gSync = 0.5;
    float gLo = 0;
    float gHi = 0.8732;
    RandParam g = RandParam(2, true, G_RNG, gLo, gHi, gSync, 0, "lin");
    
    // Cross feedback
    int G_CROSS_RNG[NUM_CHANNELS + 1] = {3716, 12474, 67543};
    float gCrossSync = 0.5;
    float gCrossLo = 0;
    float gCrossHi = 0.8732;
    RandParam gCross = RandParam(2, true, G_CROSS_RNG, gCrossLo, gCrossHi, gCrossSync, 0, "lin");
    
    // Feedback cutoff frequency
    // TODO: CHANGE THIS TO FREQUENCY VALUE ONCE FILTER IS CORRECTED
    int CUTOFF_RNG[NUM_CHANNELS + 1] = {47123, 23784, 12334};
    float cutoffSync = 0.5;
    float cutoffLo = 1;
    float cutoffHi = 20;
    RandParam cutoff = RandParam(2, true, CUTOFF_RNG, cutoffLo, cutoffHi, cutoffSync, 0, "exp");
    
    // Mix
    // 0 = dry, 1 = wet
    int MIX_RNG[1] = {10234};
    RandParam mix = RandParam(1, false, MIX_RNG, 0, 1, 0, 0, "lin");
    
private:
    DelayBuffer delayBuf;
    DelayBuffer damp;
    dsp::LookupTable<float> waveTable;
    unsigned int tableSize;
    Osc mod[NUM_CHANNELS];
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessor)
};
