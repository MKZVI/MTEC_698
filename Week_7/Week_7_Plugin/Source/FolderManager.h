/*
  ==============================================================================

    FolderManager.h
    Created: 12 Mar 2022 12:32:44pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#ifndef FolderManager_h
#define FolderManager_h

#include "JuceHeader.h"
using namespace juce;

class FolderManager {
public:
    
    /* constructor */
    FolderManager();
    
    /* destructor */
    ~FolderManager();
    
    /* returns the company root folder
        THIS FOLDER MUST BE CREATED MANUALLY OR VIA INSTALLER
     */
    static File getRootFolder();
    
    /* returns the folder for the current app */
    static File getAppFolder();
    
    /* returns the preset folder for the current app */
    static File getPresetsFolder();
    
};

#endif /* MKUFolderManager_hpp */
