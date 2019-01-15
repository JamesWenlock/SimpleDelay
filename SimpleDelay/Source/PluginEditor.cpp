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
    
    processor.mix = getRNG(processor.MIX_RNG, processor.mixLo, processor.mixHi);
    
    for (int channel = 0; channel < processor.NUM_CHANNELS; channel++) {
        
        int curDelayRNGInd = isSync(processor.CUR_DELAY_RNG[processor.SYNC_INDEX], processor.curDelaySync) ? 0 : channel;
        processor.curDelay[channel] = getRNG(processor.CUR_DELAY_RNG[curDelayRNGInd],
                                             processor.curDelayLo,
                                             processor.curDelayHi);
        
        int modWidthRNGInd = isSync(processor.MOD_WIDTH_RNG[processor.SYNC_INDEX], processor.modWidthSync) ? 0 : channel;
        processor.modWidth[channel] = getRNG(processor.MOD_WIDTH_RNG[modWidthRNGInd],
                                             processor.modWidthLo,
                                             processor.modWidthHi);
        
        int modFreqRNGInd = isSync(processor.MOD_FREQ_RNG[processor.SYNC_INDEX], processor.modFreqSync) ? 0 : channel;
        processor.modFreq[channel] = getRNG(processor.MOD_FREQ_RNG[modFreqRNGInd],
                                            processor.modFreqLo,
                                            processor.modFreqHi);
        
        int gRNGInd = isSync(processor.G_RNG[processor.SYNC_INDEX], processor.gSync) ? 0 : channel;
        processor.g[channel] = getRNG(processor.G_RNG[gRNGInd],
                                            processor.gLo,
                                            processor.gHi);
        
        int gCrossRNGInd = isSync(processor.G_CROSS_RNG[processor.SYNC_INDEX], processor.gCrossSync) ? 0 : channel;
        processor.gCross[channel] = getRNG(processor.G_CROSS_RNG[gCrossRNGInd],
                                            processor.gCrossLo,
                                            processor.gCrossHi);
        
        int cutoffRNGInd = isSync(processor.CUTOFF_RNG[processor.SYNC_INDEX], processor.cutoffSync) ? 0 : channel;
        processor.cutoff[channel] = getRNG(processor.CUTOFF_RNG[cutoffRNGInd],
                                            processor.cutoffLo,
                                            processor.cutoffHi);

        processor.cutoff[channel] = (int) getRNG(processor.CUTOFF_RNG[channel], 1, 21);
    }
    
    debugText.setText("lCurDelay: " + (String) processor.curDelay[0] + " | rCurDelay: " + (String) processor.curDelay[1]
                      + "\nlModWidth: " + (String) processor.modWidth[0] + " | rModWidth: " + (String) processor.modWidth[1]
                      + "\nlModFreq: " + (String) processor.modFreq[0] + " | rModFreq: " + (String) processor.modFreq[1]
                      + "\nlG: " + (String) processor.g[0] + " | rG: " + (String) processor.g[1]
                      + "\nlGCross: " + (String) processor.gCross[0] + " | rGCross: " + (String) processor.gCross[1]
                      + "\nlCutoff: " + (String) processor.cutoff[0] + " | rCutoff: " + (String) processor.cutoff[1]
                      + "\nmix: " + (String) processor.mix
                      , dontSendNotification);
}

bool SimpleDelayAudioProcessorEditor::isSync(int rng, float likelihood) {
    return getRNG(rng, 0, 1) > likelihood;
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
