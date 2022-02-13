/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week_3_pluginAudioProcessorEditor::Week_3_pluginAudioProcessorEditor (Week_3_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    //set up carrier volume control
    mCarrierVol.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mCarrierVol.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mCarrierVol.setRange(0.f, 1.f);
    addAndMakeVisible(mCarrierVol);
    
    mCarrierVol.onValueChange = [this]()
    {
        audioProcessor.setCarrierVolume(mCarrierVol.getValue());
    };
    
    //set up carrier freq control
    mCarrierFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mCarrierFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mCarrierFreq.setRange(100.f, 2000.f);
    addAndMakeVisible(mCarrierFreq);
    
    //setup carrier phase offset control
    mCarrierPhase.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mCarrierPhase.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mCarrierPhase.setRange(0.f, 1.f);
    addAndMakeVisible(mCarrierPhase);
    
    //set up mod index
    mModIndex.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mCarrierPhase.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mCarrierPhase.setRange(0.f, 10.f);
    addAndMakeVisible(mModIndex);
    
    //set up mod freq
    mModFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mModFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mModFreq.setRange(20.f, 4000.f);
    addAndMakeVisible(mModFreq);
    
    //set up mod phase offset
    mModPhase.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mModPhase.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mModPhase.setRange(0.f, 1.f);
    addAndMakeVisible(mModPhase);
    
    
    
    setSize (800, 600);
}

Week_3_pluginAudioProcessorEditor::~Week_3_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Week_3_pluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Week_3_pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //top row
    mCarrierVol.setBounds(0, 0, getWidth()/3, getHeight()/2);
    mCarrierFreq.setBounds(getWidth()/3, 0, getWidth()/3, getHeight()/2);
    mCarrierPhase.setBounds((getWidth()/3)*2, 0, getWidth()/3, getHeight()/2);
    
    //bottom row
    mModFreq.setBounds(0, getHeight()/2, getWidth()/3, getHeight()/2 );
    mModIndex.setBounds(getWidth()/3, getHeight()/2, getWidth()/3, getHeight()/2);
    mModPhase.setBounds((getWidth()/3)*2, getHeight()/2, getWidth()/3, getHeight()/2);
    
}
