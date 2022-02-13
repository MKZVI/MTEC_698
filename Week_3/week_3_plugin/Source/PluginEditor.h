/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Week_3_pluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week_3_pluginAudioProcessorEditor (Week_3_pluginAudioProcessor&);
    ~Week_3_pluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider mCarrierVol;
    juce::Slider mCarrierFreq;
    juce::Slider mCarrierPhase;
    juce::Slider mModIndex;
    juce::Slider mModFreq;
    juce::Slider mModPhase;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week_3_pluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week_3_pluginAudioProcessorEditor)
};
