/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GuidevAudioProcessorEditor::GuidevAudioProcessorEditor (GuidevAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
    
    left.setButtonText("left");
    right.setButtonText("right");

    addAndMakeVisible(button);
    addAndMakeVisible(left);
    addAndMakeVisible(right);

}

GuidevAudioProcessorEditor::~GuidevAudioProcessorEditor()
{
}

//==============================================================================
void GuidevAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour (Colours::red);
    g.setFont (15.0f);
    Path leftTriangle;
    leftTriangle.addTriangle(10, 10, getWidth() - 10, getWidth() - 10, getHeight(), getHeight());
    g.fillPath (leftTriangle);
    g.setColour (Colours::black);

}

void GuidevAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();
    button.setBounds(r.removeFromTop(150).reduced(10));
    left.setBounds(r.removeFromLeft(100).reduced(10));
    right.setBounds(r.removeFromLeft(100).reduced(10));

}
