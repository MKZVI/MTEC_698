/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week_5_pluginAudioProcessorEditor::Week_5_pluginAudioProcessorEditor (Week_5_pluginAudioProcessor& p)
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
    
    mDelayTimeSecondsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSecondsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayTimeSecondsSlider);
    
    mDelayFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayFeedbackSlider);
    
    mDelayMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayMixSlider);
    
    
    
    //mGainAmountSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                               //PARAMETER_NAMES[GAIN_AMOUNT],
                                                                                               //mGainAmountSlider));
    
    //mFMAmountSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                             //PARAMETER_NAMES[FM_AMOUNT],
                                                                                             //mFMAmountSlider));
    
    //mSineWaveCarrFreqSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                                     //PARAMETER_NAMES[CARR_FREQ],
                                                                                                     //mSineWaveCarrFreqSlider));
    
    //mSineWaveModFreqSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                                    //PARAMETER_NAMES[MOD_FREQ],
                                                                                                    //mSineWaveModFreqSlider));
                                                                                                    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    auto* value_tree = audioProcessor.getParameterManager()->getValueTree();
                                                                                                    
    mGainAmountSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[GAIN_AMOUNT], mGainAmountSlider));
    mFMAmountSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[FM_AMOUNT], mFMAmountSlider));
    mSineWaveCarrFreqSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[CARR_FREQ], mSineWaveCarrFreqSlider));
    mSineWaveModFreqSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[MOD_FREQ], mSineWaveModFreqSlider));
    
    mDelayTimeSecondsSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_TIME_SECONDS], mDelayTimeSecondsSlider));
    mDelayFeedbackSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_FEEDBACK], mDelayFeedbackSlider));
    mDelayMixSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_MIX], mDelayMixSlider));
    
    
    setSize (900, 450);
}

Week_5_pluginAudioProcessorEditor::~Week_5_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Week_5_pluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::pink);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::chartreuse);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
}

void Week_5_pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mGainAmountSlider.setBounds(sliderSize/4, 0, sliderSize, sliderSize );
    mFMAmountSlider.setBounds(getWidth()/3 + sliderSize/4, 0, sliderSize, sliderSize);
    mSineWaveCarrFreqSlider.setBounds(sliderSize/4, getHeight()/2, sliderSize, sliderSize);
    mSineWaveModFreqSlider.setBounds(getWidth()/3 + sliderSize/4, getHeight()/2, sliderSize, sliderSize);
    
    mDelayTimeSecondsSlider.setBounds(getWidth()/3 * 2 + sliderSize/4, 0, sliderSize/3 * 2, sliderSize/3 * 2);
    mDelayFeedbackSlider.setBounds(getWidth()/3 * 2 + sliderSize/4, getHeight()/3, sliderSize/3 * 2, sliderSize/3 * 2);
    mDelayMixSlider.setBounds(getWidth()/3*2 + sliderSize/4, getHeight()/3 * 2, sliderSize/3 * 2, sliderSize/3 * 2);
}
