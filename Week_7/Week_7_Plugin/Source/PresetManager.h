/*
  ==============================================================================

    PresetManager.h
    Created: 12 Mar 2022 12:34:37pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#ifndef PresetManager_h
#define PresetManager_h

#include "JuceHeader.h"
using namespace juce;

class ProcessorInterface;

class PresetManager {
public:

    /* */
    PresetManager(ProcessorInterface* inInterface);

    /* */
    ~PresetManager();
    
    /* */
    void loadPreset(int inListIndex);
    
    /* */
    StringArray getCurrentPresetNames();
    
    /* */
    void saveCurrentPreset(String inPresetName);

private:
    
    /* */
    void _constructPresetFilesArray();
    
    Array<File> mPresetFiles;
    
    ProcessorInterface* mProcessorInterface;
};

#endif /* PresetManager_h */
