/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                         private Button::Listener
{
public:
    SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor&);
    ~SimpleDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    void buttonClicked(Button * thisBtn) override;

    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDelayAudioProcessor& processor;

    TextButton button;
    TextButton left;
    TextButton right;
    
    int guiWidth;
    int guiHeight;
    int randBtnSize;
    int lBtnSize;
    int rBtnSize;
    int btnMargin;
    int textSize;
    
    String debugText;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessorEditor)
};
