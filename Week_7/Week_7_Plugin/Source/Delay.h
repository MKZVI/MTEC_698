/*
  ==============================================================================

    Delay.h
    Created: 12 Mar 2022 12:35:15pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once

#ifndef Delay_h
#define Delay_h

#include "JuceHeader.h"

class Delay {
    
public:
    
    /* */
    Delay();
    
    /* */
    ~Delay();
    
    /* */
    void initialize(float inSampleRate, int inBlocksize);
    
    /* */
    void setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix, float inLPFreq, float inHPFreq);
    
    /* */
    void processBlock(float* inBuffer, int inNumSamples);
    
    /* */
    void processSample(float& inSample);
    
private:
    
    juce::LinearSmoothedValue<float> mTimeInSeconds;
    float mFeedbackAmount = 0;
    float mMix = 0;
    
    float mWriteHead = 0;
    float mFeedbackSample = 0;
    
    juce::AudioBuffer<float> mCircularBuffer;
    
    float mSampleRate;
    
    juce::dsp::IIR::Coefficients<float> mHighpassCoefficients;
    juce::dsp::IIR::Filter<float> mHighPassFilter;
    
    juce::dsp::IIR::Coefficients<float> mLowpassCoefficients;
    juce::dsp::IIR::Filter<float> mLowpassFilter;
};

#endif /* Delay_h */