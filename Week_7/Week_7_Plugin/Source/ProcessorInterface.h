/*
  =============================================================================
    ProcessorInterface
    Created: 12 Mar 2022 12:33:16
    Author:  Micah Keren-Zv
  ============================================================================
*/

#pragma on
#ifndef ProcessorInterface_h
#define ProcessorInterface_h

#include "JuceHeader.h"

class ParameterManager;
class PresetManager;

class ProcessorInterface {
    
public:
    
    virtual ~ProcessorInterface() {};
    
    virtual ParameterManager* getParameterManager() = 0;
    
    virtual PresetManager* getPresetManager() = 0;
    
    virtual juce::AudioProcessor* getAudioProcessor() = 0;
        
};

#endif /* ProcessorInterface_h */

