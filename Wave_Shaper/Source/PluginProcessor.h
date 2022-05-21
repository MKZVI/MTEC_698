/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "InMemorySample.h"
#include "ParameterManager.h"
#include "PresetManager.h"
#include "ProcessorInterface.h"
#include "PropertyManager.h"

#include "SoftClipper.h"
#include "SineWaveFolder.h"

#define SIMPLE_SAMPLE_IN_STANDALONE 1

//==============================================================================
/**
*/
class WaveShaperAudioProcessor  : public juce::AudioProcessor,
                                    public ProcessorInterface
{
public:
    //==============================================================================
    WaveShaperAudioProcessor();
    ~WaveShaperAudioProcessor() override;

    //==============================================================================

    /* PRIMARY PROCESSOR RESPONSIBILITIES*/
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /* PROCESSOR INTERACE OVERRIDES*/
    ParameterManager* getParameterManager() override;
    PresetManager* getPresetManager() override;
    PropertyManager* getPropertyManager() override;
    AudioProcessor* getAudioProcessor() override;
    
    

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    /* general functions which tell the DAW information about your plugin -- you made need sometimes */
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    float getRMSValue(const int channel) const;

private:
    
    void _generateSimpleSample(AudioBuffer<float>& inBuffer);
    
    float rmsLevelLeft, rmsLevelRight;
    
    SoftClipper mClipper;
    SineWaveFolder mSinFolder;
    juce::dsp::Phaser<float> mPhaserLeft;
    juce::dsp::Phaser<float> mPhaserRight;
    
#if SIMPLE_SAMPLE_IN_STANDALONE
    InMemorySample mTestingSample;
#endif
    
    std::unique_ptr<ParameterManager> mParameterManager;
    std::unique_ptr<PresetManager> mPresetManager;
    std::unique_ptr<PropertyManager> mPropertyManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveShaperAudioProcessor)
};
