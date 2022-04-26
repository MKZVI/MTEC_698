/*
  ==============================================================================

    SineWaveFolder.h
    Created: 18 Apr 2022 6:55:22pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once

#ifndef SineWaveFolder_h
#define SineWaveFolder_h

#include "Juceheader.h"

class SineWaveFolder
{
public:
    SineWaveFolder();
    
    ~SineWaveFolder();
    
    void initialize(float inSampleRate, int inBlockSize);
    
    void setParameters(float inGain, float inLPFreq, float inHPFreq);
    
    void processSample(float inSample);
    
    //void setDrive(float inDrive);
    
    
private:

    float mSampleRate;
    float mDrive;
    
    juce::dsp::IIR::Coefficients<float> mHighpassCoefficients;
    juce::dsp::IIR::Filter<float> mHighPassFilter;
    
    juce::dsp::IIR::Coefficients<float> mLowpassCoefficients;
    juce::dsp::IIR::Filter<float> mLowpassFilter;

};


#endif /* SineWaveFolder_h */
