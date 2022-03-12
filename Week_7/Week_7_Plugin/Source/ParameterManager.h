/*
  ==============================================================================

    ParameterManager.h
    Created: 12 Mar 2022 12:33:50pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#ifndef ParameterManager_h
#define ParameterManager_h

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ProcessorInterface;

class ParameterManager {
public:
    
    /* */
    ParameterManager(ProcessorInterface* inInterface);
    
    /* */
    ~ParameterManager();
    
    /* */
    float getCurrentValue(int inParameterID);
    
    /* */
    juce::AudioProcessorValueTreeState* getValueTree();
    
private:
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    
    ProcessorInterface* mProcessorInterface;
};

#endif /* ParameterManager_h */