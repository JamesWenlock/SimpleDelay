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
    return (processor.seed % RNG) / (float) RNG * range + lo;
}

void SimpleDelayAudioProcessorEditor::buttonClicked(Button * thisBtn)
{
    if (thisBtn == &left)
    {
        debugText.setText("left", dontSendNotification);
    }
    else if (thisBtn == &right)
    {
        calcParamVals();
    }
}

void SimpleDelayAudioProcessorEditor::calcParamVals()
{
    processor.seed = rand();
    
    processor.mix.updateParam(processor.seed);
    processor.cutoff.updateParam(processor.seed);
    processor.gCross.updateParam(processor.seed);
    processor.g.updateParam(processor.seed);
    processor.modFreq.updateParam(processor.seed);
    processor.modWidth.updateParam(processor.seed);
    processor.curDelay.updateParam(processor.seed);
    
    debugText.setText("lCurDelay: " + (String) processor.curDelay.get(0) + " | rCurDelay: " + (String) processor.curDelay.get(1)
                      + "\nlModWidth: " + (String) processor.modWidth.get(0) + " | rModWidth: " + (String) processor.modWidth.get(1)
                      + "\nlModFreq: " + (String) processor.modFreq.get(0) + " | rModFreq: " + (String) processor.modFreq.get(1)
                      + "\nlG: " + (String) processor.g.get(0) + " | rG: " + (String) processor.g.get(1)
                      + "\nlGCross: " + (String) processor.gCross.get(0) + " | rGCross: " + (String) processor.gCross.get(1)
                      + "\nlCutoff: " + (String) processor.cutoff.get(0) + " | rCutoff: " + (String) processor.cutoff.get(1)
                      + "\nmix: " + (String) processor.mix.get(0)
                      , dontSendNotification);
}

bool SimpleDelayAudioProcessorEditor::isSync(int rng, float likelihood) {
    return getRNG(rng, 0, 1) > likelihood;
}

/*
 float mapExp(float input) {
    var base = 4;
    return pow(base, (input + 1)) * (1 / (base * (base - 1)))
 }

 float mapBi(float input) {
    if (input > likelihood)
    {
        return 1;
    }
    else
    {
        return 0
    }
 }
 
 float map(float input) {
    var range = hi - lo;
    var output = input;
    switch(curve)
    {
        case "exp" : output = mapExp(input);
        break;
        case "bi" : output = mapBi(input)
        break;
    }
    output = output * range + lo;
 }
 */

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
