/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeel.h"
#include "UI/HorizontalMeter.h"
#include "UI/HorizontalGradientMeter.h"

//==============================================================================
/**
*/
class WaveShaperAudioProcessorEditor  : public juce::AudioProcessorEditor, public Timer
{
public:
    
    // We see our processor comes into this editor class throug it's constructor
    WaveShaperAudioProcessorEditor (WaveShaperAudioProcessor&);
    
    ~WaveShaperAudioProcessorEditor() override;

    
    /*
        The paint function is where we put our graphical code.
        
        It will be drawn when significant changes happen to the system,
     
        or manually when we call repaint() on this class.
     */
    
    void timerCallback() override;
    
    void paint (juce::Graphics&) override;
    
    /*
        The resized function is for performing layout
        
        It will be called when the size of our component changes.
     */
    void resized() override;

private:
    
    void _updatePresetComboBoxOptions();
        
    OwnedArray<Slider> mSliders;
    OwnedArray<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachments;
    
    TextButton mSavePreset;
    ComboBox mPresetOptions;
    
    Gui::HorizontalMeter mHorizontalMeterL, mHorizontalMeterR;
    //Gui::HorizontalGradientMeter mHorizontalGradientMeterL, mHorizontalGradientMeterR;

    MyLookAndFeel mLookAndFeel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveShaperAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveShaperAudioProcessorEditor)
};
