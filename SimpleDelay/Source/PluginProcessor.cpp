/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDelayAudioProcessor::SimpleDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    maxDelay = 3;
    lCurDelay = 0.1;
    rCurDelay = 0.1;
    lCurRNG = 273965;
    rCurRNG = 987632;
    g = 0.118;
    gCross = 0.612;
    cutoff = 20;
    dry = 0.5;
    wet = 0.5;
    tableSize = 1 << 24;
    int waveTableSize = tableSize;
    waveTable.initialise([waveTableSize](size_t index) {return sin(2 * M_PI * index / (waveTableSize - 1));}, tableSize);
    lMod = Osc(&waveTable);
    rMod = Osc(&waveTable);
    lModWidth = 0;
    lModWidth = 0;
    rModFreq = 4;
    lModFreq = 6;
    
}

SimpleDelayAudioProcessor::~SimpleDelayAudioProcessor()
{
}

//==============================================================================
const String SimpleDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    delayBuf = DelayBuffer(maxDelay * getSampleRate(), 2);
    damp = DelayBuffer(getSampleRate(), 2);
}

void SimpleDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    // Buffer to contain the output samples for each channel's processing chain
    float chainOuts[2];
    // Iterate through every sample
    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
        // Iterate through every channel (TODO: SHOULD ONLY BE 2)
        for (int channel = 0; channel < totalNumInputChannels; channel++) {
            // get delay output
            float delayOffset;
            if (channel == 0) {
                float maxWidth = std::min(lCurDelay, maxDelay - lCurDelay);
                float lWidth = maxWidth * lModWidth;
                delayOffset = (lCurDelay + lMod.get(getSampleRate(), lModFreq) * lWidth) * getSampleRate();
            } else {
                float maxWidth = std::min(rCurDelay, maxDelay - rCurDelay);
                float rWidth = maxWidth * rModWidth;
                delayOffset = (rCurDelay + rMod.get(getSampleRate(), rModFreq) * rWidth) * getSampleRate();
            }
            float delayOut = delayBuf.getOffset(channel, delayOffset);

            // Dampen (low pass filter) the delay output
            float filterOut = 0;
            damp.put(channel, delayOut);
            float sum = 0;
            for (int i = 0; i < cutoff; i++) {
                sum += damp.getOffset(channel, i);
            }
            filterOut = sum / cutoff;

            // Get the incoming sample
            float channelSample = buffer.getSample(channel, sample);

            // Set the processing chain output sample
            chainOuts[channel] = channelSample + filterOut;

            // Set the outgoing sample
            buffer.setSample(channel, sample, (filterOut * wet) + (channelSample * dry));
        }

        // Place samples into the delay buffers for each channel, including crossing
        // This implicitly creates a 1 sample delay (delay offset of 0 will return
        // data from previously processed sample as no sample is placed until after
        // the processing chain is finished).
        for (int i = 0; i < 2; i++) {
            delayBuf.put(i, chainOuts[1 - i] * gCross + chainOuts[i] * g);
        }
    }
}

//==============================================================================
bool SimpleDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleDelayAudioProcessor::createEditor()
{
    return new SimpleDelayAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDelayAudioProcessor();
}
