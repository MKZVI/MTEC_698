/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week_2_pluginAudioProcessorEditor::Week_2_pluginAudioProcessorEditor (Week_2_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mSlider.setRange(0.f, 1.f);
    addAndMakeVisible(mSlider);
    
    mSlider.onValueChange = [this]()
    {
        DBG(mSlider.getValue());
        audioProcessor.setSineVolume(mSlider.getValue());
    };
    
    setSize(400, 300);
}

Week_2_pluginAudioProcessorEditor::~Week_2_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Week_2_pluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Week_2_pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mSlider.setBounds(0, 0, 150, 150);
}
