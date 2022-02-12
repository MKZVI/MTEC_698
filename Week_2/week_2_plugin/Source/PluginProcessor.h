/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/* THIS IS A BASIC SINEWAVE CLASS */

class SineWave {
    
    // Public indicates that these methods will be available to the outside program
    
    // ex SineWave.initialize(554, 44100)
public:
    
    /* CONSTRUCTOR
     
     A constructor is called when a class is created, it can be used to allocate memory
     or setup various internal data of the class
     
     */
    SineWave() {
        // EMPTY
    }
    
    
    /* DECONSTRUCTOR
     
     A deconstructor is called when a class is delete, it can be used to free memory
     or delete things we'll no longer be using in the application
     
     */
    ~SineWave() {
        // EMPTY
    }
    
    /* INITALIZE
     
     We call this initialze function from our prepare to play method to get our
     SineWave ready for playback
     
     */
    void initialize(float inFrequencyHz, float inSampleRate) {
        
        // Set our desired frequency in HZ
        //mFreqHz = inFrequencyHz; (redundant?)
        
        setFrequency(inFrequencyHz);
        
        // Set our samplerate for math calculations
        mSampleRate = inSampleRate;
    }
    
    void setFrequency(float newFrequencyHz) {
        
        mFreqHz = newFrequencyHz;
        
    }
    
    void setPhaseOffset(float newPhase) {
        
        mPhaseOffset = newPhase * (juce::MathConstants<float>::twoPi);
        
    }
    
    
    /* */
    float getNextSample() {
        
        // calculate our sine function output -- using a sin call scaled to repete between 0 - 1 on the input
        float output = std::sin(juce::MathConstants<float>::twoPi * mPhase);
        
        // move our phase forward in the sign table by a single step determined by our desired samplerate & playback hz
        mPhase += mFreqHz / mSampleRate;
        
        // add offset
        mPhase += mPhaseOffset;
        
        // if we go passed 1 -- lets loop back around the sine wave
        if (mPhase > 1.f) {
            mPhase -= 1.f;
        }
        
        // return the output to the caller
        return output;
    }
    
    
    // Private means these are not accessible to the outside world
    
    // ex: SineWave.mFreqHz <- Illegal and impossible to access a private member variable
private:
    
    // These are member variables of the class (internal data)
    float mFreqHz = 442;
    float mSampleRate = 44100;
    float mPhase = 0;
    float mPhaseOffset = 0;
    
};


//==============================================================================
/**
*/
class Week_2_pluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Week_2_pluginAudioProcessor();
    ~Week_2_pluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    /*
    
     This is a function for the editor in order to update value of sinewave
     
     */
    
    void setSineVolume(float inInputVolumeAmp);

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    SineWave mSineWave;
    SineWave mModulator;
    
    float mSineGain = 1.f;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week_2_pluginAudioProcessor)
};
