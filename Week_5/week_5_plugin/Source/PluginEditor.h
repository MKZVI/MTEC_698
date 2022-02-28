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
class Week_5_pluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week_5_pluginAudioProcessorEditor (Week_5_pluginAudioProcessor&);
    ~Week_5_pluginAudioProcessorEditor() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
    int sliderSize = 200;
    
    /*======= SLIDER 1 ======= */
    
    /* The Slider Member For Our UI */
    juce::Slider mGainAmountSlider;
    /* This is a helpful juce class to attach our slider to our value tree */
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainAmountSliderAttachment;
    
    /* The Slider Member For Our UI */
    juce::Slider mFMAmountSlider;
    /* This is a helpful juce class to attach our slider to our value tree */
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFMAmountSliderAttachment;
    
    /* SineWaveCarr Frequency Slider */
    juce::Slider mSineWaveCarrFreqSlider;
    /*********************************/
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSineWaveCarrFreqSliderAttachment;
    
    /* SineWaveMod Frequency Slider */
    juce::Slider mSineWaveModFreqSlider;
    /********************************/
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSineWaveModFreqSliderAttachment;
    
    juce::Slider mDelayTimeSecondsSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayTimeSecondsSliderAttachment;
    
    juce::Slider mDelayFeedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayFeedbackSliderAttachment;
    
    juce::Slider mDelayMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayMixSliderAttachment;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week_5_pluginAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week_5_pluginAudioProcessorEditor)
};
