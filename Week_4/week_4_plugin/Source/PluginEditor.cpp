/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week_4_pluginAudioProcessorEditor::Week_4_pluginAudioProcessorEditor (Week_4_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    mGainAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mGainAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mGainAmountSlider);
    
    mFMAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFMAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mFMAmountSlider);
    
    mSineWaveCarrFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSineWaveCarrFreqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 150, 20);
    addAndMakeVisible(mSineWaveCarrFreqSlider);
    
    mSineWaveModFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSineWaveModFreqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 150, 20);
    addAndMakeVisible(mSineWaveModFreqSlider);
    
    mGainAmountSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                               PARAMETER_NAMES[GAIN_AMOUNT],
                                                                                               mGainAmountSlider));
    
    mFMAmountSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                             PARAMETER_NAMES[FM_AMOUNT],
                                                                                             mFMAmountSlider));
    
    mSineWaveCarrFreqSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                                     PARAMETER_NAMES[CARR_FREQ],
                                                                                                     mSineWaveCarrFreqSlider));
    
    mSineWaveModFreqSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                                    PARAMETER_NAMES[MOD_FREQ],
                                                                                                    mSineWaveModFreqSlider));
    
    
    setSize (600, 450);
}

Week_4_pluginAudioProcessorEditor::~Week_4_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Week_4_pluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Week_4_pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mGainAmountSlider.setBounds(sliderSize/4, 0, sliderSize, sliderSize );
    mFMAmountSlider.setBounds(getWidth()/2 + sliderSize/4, 0, sliderSize, sliderSize);
    mSineWaveCarrFreqSlider.setBounds(sliderSize/4, getHeight()/2, sliderSize, sliderSize);
    mSineWaveModFreqSlider.setBounds(getWidth()/2 + sliderSize/4, getHeight()/2, sliderSize, sliderSize);
}
