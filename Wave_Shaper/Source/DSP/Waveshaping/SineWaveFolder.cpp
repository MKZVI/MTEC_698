/*
  ==============================================================================

    SineWaveFolder.cpp
    Created: 18 Apr 2022 6:55:22pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#include "SineWaveFolder.h"

SineWaveFolder::SineWaveFolder()
{
    
}

SineWaveFolder::~SineWaveFolder()
{
    
}

void SineWaveFolder::initialize(float inSampleRate, int inBlockSize)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inBlockSize;
    spec.numChannels = 1;
    
    mHighPassFilter.prepare(spec);
    mLowpassFilter.prepare(spec);
    mDrive = 1.f;
    
}

void SineWaveFolder::setParameters(float inGain, float inHPFreq, float inLPFreq)
{
    mHighPassFilter.coefficients = mHighpassCoefficients.makeHighPass(mSampleRate, inHPFreq);
    mLowpassFilter.coefficients = mLowpassCoefficients.makeLowPass(mSampleRate, inLPFreq);
    inGain = mDrive;
}




void SineWaveFolder::processSample(float inSample)
{
    
    float output_sample = mHighPassFilter.processSample(inSample);
    
    output_sample = std::tanh(std::sin(inSample * mDrive));
    
    output_sample = mLowpassFilter.processSample(output_sample);
    
    
    
}
