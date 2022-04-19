/*
  ==============================================================================

    TriangleWave.h
    Created: 19 Apr 2022 8:29:06am
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#ifndef TriangleWave_h
#define TriangleWave_h

#include "JuceHeader.h"

class TriangleWave
{
public:
    
    TriangleWave();
    
    ~TriangleWave();
    
    void initialize(float inFrequencyHz, float inSampleRate);
    
    float getNextSample();
    
    void setParameters(float inFreq, float inGain);
    
    
private:
    
    float mFreqHz = 442;
    
    float mSampleRate = 44100;
    
    float mPhase = 0;
    
    juce::LinearSmoothedValue<float> mSmoothedGain;
    
};


#endif /* TriangleWave_h */
