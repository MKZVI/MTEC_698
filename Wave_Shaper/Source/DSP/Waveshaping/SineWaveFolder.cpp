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

void SineWaveFolder::setParameters(float inGain, float inLPFreq, float inHPFreq)
{
    mHighPassFilter.coefficients = mHighpassCoefficients.makeHighPass(mSampleRate, inHPFreq);
    mLowpassFilter.coefficients = mLowpassCoefficients.makeLowPass(mSampleRate, inLPFreq);
}




void SineWaveFolder::processSample(float inSample)
{
    
    float output_sample = mLowpassFilter.processSample(inSample);
    
    output_sample = std::sin(inSample * mDrive);
    
    output_sample = mHighPassFilter.processSample(output_sample);
    
    
    //inSample = output_sample;
}
