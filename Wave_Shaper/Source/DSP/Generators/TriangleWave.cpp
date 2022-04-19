/*
  ==============================================================================

    TriangleWave.cpp
    Created: 19 Apr 2022 8:29:06am
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#include "TriangleWave.h"


TriangleWave::TriangleWave()
{
    
}

TriangleWave::~TriangleWave()
{
    
}

void TriangleWave::initialize(float inFrequencyHz, float inSampleRate)
{
    mFreqHz = inFrequencyHz;
    
    mSampleRate = inSampleRate;
    
    mSmoothedGain.reset(inSampleRate, 0.1);
}

float TriangleWave::getNextSample()
{
    float output = 0.f;
    
    float fullPeriodTime = 0.1f/mFreqHz;
    
    float localTime = fmod(mPhase, fullPeriodTime);
    
    float value = localTime / fullPeriodTime;
    
    mPhase += mFreqHz / mSampleRate;
    
    if (value < 0.25f)
    {
        output = value * 4.f;
    }
    else if (value < 0.75f)
    {
        output = 2.f - (value * 4.f);
    }
    else
    {
        output = value * 4 - 4.f;
    }
    
    return output * mSmoothedGain.getNextValue();
}

void TriangleWave::setParameters(float inFreq, float inGain)
{
    mFreqHz = inFreq;
    mSmoothedGain.setTargetValue(inGain);
}
