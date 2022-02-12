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
class Week_2_pluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week_2_pluginAudioProcessorEditor (Week_2_pluginAudioProcessor&);
    ~Week_2_pluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider mSlider;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week_2_pluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week_2_pluginAudioProcessorEditor)
};
