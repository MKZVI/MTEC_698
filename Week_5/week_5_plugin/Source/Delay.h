/*
  =============================================================================

    Delay.
    Created: 27 Feb 2022 2:08:00p
    Author:  Micah Keren-Zv

  =============================================================================
*

#pragma onc

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
    void initialize(float inSampleRate);
    
    /* */
    void setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix);
    
    /* */
    void processBlock(float* inBuffer, int inNumSamples);
    
    /* */
    void processSample(float& inSample);
    
private:
    
    float mTimeInSeconds = 0;
    float mFeedbackAmount = 0;
    float mMix = 0;
    
    float mWriteHead = 0;
    float mFeedbackSample = 0;
    
    juce::AudioBuffer<float> mCircularBuffer;
   juce::LinearSmoothedValue<float> mSmoothedTimeInSeconds;
    
    //using LinearInterpolator = juce::Interpolators::Linear;
 
     
    float mSampleRate;
        
 
};

#endif /* Delay_h */

