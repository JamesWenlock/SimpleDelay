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
    randBtnSize = 200;
    lBtnSize = 200;
    rBtnSize = 200;
    textSize = 100;
    btnMargin = 10;
    
    debugText = "test";
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (guiWidth, guiHeight);
    
    left.setButtonText("left");
    right.setButtonText("right");

    addAndMakeVisible(button);
    addAndMakeVisible(left);
    addAndMakeVisible(right);
    button.addListener(this);
    left.addListener(this);
    right.addListener(this);
}

SimpleDelayAudioProcessorEditor::~SimpleDelayAudioProcessorEditor()
{
}

void SimpleDelayAudioProcessorEditor::buttonClicked(Button * thisBtn)
{
    debugText = "clicked";
    if (thisBtn == &left)
    {
        debugText = "left";
    }
    else if (thisBtn == &right)
    {
        debugText = "right";
    }
    else if (thisBtn == &button)
    {
        debugText = "button";
    }
    resized();
}

//==============================================================================
void SimpleDelayAudioProcessorEditor::paint (Graphics& g)
{
    /*    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour (Colours::red);
    g.setFont (15.0f);
    Path leftTriangle;
    leftTriangle.addTriangle(10, 10, getWidth() - 10, getWidth() - 10, getHeight(), getHeight());
    g.fillPath (leftTriangle);
    g.setColour (Colours::black);
    */
    // fill the whole window white
    g.fillAll (Colours::white);
    // set the current drawing colour to black
    g.setColour (Colours::black);
    // set the font size and draw text to the screen
    g.setFont (15.0f);
    g.drawFittedText (debugText, 0, 0, getWidth(), textSize, Justification::centred, 1);
}

void SimpleDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();
    r.removeFromTop(textSize);
    button.setBounds(r.removeFromTop(randBtnSize).reduced(10));
    left.setBounds(r.removeFromLeft(lBtnSize).reduced(10));
    right.setBounds(r.removeFromLeft(rBtnSize).reduced(10));

}
