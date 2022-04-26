/*
  ==============================================================================

    LowPassFilter.h
    Created: 25 Apr 2022 6:52:47pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once



#ifndef LowPassFilter_h
#define LowPassFilter_h

#include "Juceheader.h"

class LowPassFilter

{
public:
    LowPassFilter();
    
    ~LowPassFilter();
    
    void initialize (float inSampleRate, int BlockSize);
    
    void setParameters(float LPFreq);
    
    void processSample(float inSample);
    
private:
    
    float mSampleRate;
    
};



#endif /* LowPassFilter */
