/*
  ==============================================================================

    ParameterManager.h
    Created: 27 Feb 2022 2:06:54pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#ifndef ParameterManager_h
#define ParameterManager_h

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ParameterManager {
public:
    
    /* */
    ParameterManager(juce::AudioProcessor* inAudioProcessor);
    
    /* */
    ~ParameterManager();
    
    /* */
    float getCurrentValue(int inParameterID);
    
    /* */
    juce::AudioProcessorValueTreeState* getValueTree();
    
private:
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
};

#endif /* ParameterManager_h */
