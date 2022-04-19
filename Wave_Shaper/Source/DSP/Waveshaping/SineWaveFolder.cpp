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

void SineWaveFolder::processSample(float inSample)
{
    inSample = std::sin(inSample);
}
