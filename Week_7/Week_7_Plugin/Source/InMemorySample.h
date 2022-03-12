/*
  ==============================================================================

    InMemorySample.h
    Created: 12 Mar 2022 12:35:45pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

//#pragma once

#ifndef InMemorySample_h
#define InMemorySample_h

#include "SampleBase.h"

class InMemorySample : public SampleBase
{
public:
    
    /* */
    InMemorySample();
    
    /* */
    ~InMemorySample();
    
    /* */
    void readerInitialized() override;
    
    /* */
    void getSample(int64 inPosition, std::vector<float>& inResults) override;
    
    /* */
    void getSample(int64 inPositionLeft, int64 inPositionRight, std::vector<float>& inResults) override;
    
    /* */
    AudioBuffer<float>* getBuffer();
    
private:
    
    std::unique_ptr<AudioBuffer<float>> mInMemoryBuffer;

};

#endif /* InMemorySample_h */