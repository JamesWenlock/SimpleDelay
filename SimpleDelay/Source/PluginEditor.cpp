/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDelayAudioProcessorEditor::SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    guiWidth = 400;
    guiHeight = 400;
    lBtnSize = 200;
    rBtnSize = 200;
    textSize = 300;
    btnMargin = 10;
    
    debugText.setText("default", dontSendNotification);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (guiWidth, guiHeight);
    
    left.setButtonText("left");
    right.setButtonText("right");

    addAndMakeVisible(left);
    addAndMakeVisible(right);
    addAndMakeVisible(debugText);
    left.addListener(this);
    right.addListener(this);
}

SimpleDelayAudioProcessorEditor::~SimpleDelayAudioProcessorEditor()
{
}

float SimpleDelayAudioProcessorEditor::getRNG(int RNG, float lo, float hi) {
    float range = hi - lo;
    return (processor.rand % RNG) / (float) RNG * range + lo;
}

void SimpleDelayAudioProcessorEditor::buttonClicked(Button * thisBtn)
{
    if (thisBtn == &left)
    {
        debugText.setText("left", dontSendNotification);
    }
    else if (thisBtn == &right)
    {
        processor.rand = rand();
        for (int channel = 0; channel < processor.NUM_CHANNELS; channel++) {
            processor.curDelay[channel] = getRNG(processor.CUR_DELAY_RNG[channel], 0, processor.maxDelay);
        }
        
        debugText.setText("lCurDelay: " + (String) processor.curDelay[0] + " | rCurDelay: " + (String) processor.curDelay[1], dontSendNotification);
    }
}

//==============================================================================
void SimpleDelayAudioProcessorEditor::paint (Graphics& g)
{

    // fill the whole window white
    g.fillAll (Colours::black);
    // set the current drawing colour to black
    g.setColour (Colours::black);
    // set the font size and draw text to the screen
    g.setFont (15.0f);
}

void SimpleDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();
    debugText.setBounds(r.removeFromTop(textSize));
    left.setBounds(r.removeFromLeft(lBtnSize).reduced(10));
    right.setBounds(r.removeFromLeft(rBtnSize).reduced(10));
}
