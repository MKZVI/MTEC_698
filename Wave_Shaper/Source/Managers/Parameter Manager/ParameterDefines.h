//
//  ParameterDefines.h
//  Wave Shaper
//
//  Created by Jacob Penn on 2/15/22.
//

#ifndef ParameterDefines_h
#define ParameterDefines_h

#include "JuceHeader.h"

// Wave Shaper Parameter Defines

enum {
    DRIVE,
    RATE,
    DEPTH,
    CTRHZ,
    FDBK,
    MIX,
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Drive",
    "Rate",
    "Depth",
    "Center_Frequency",
    "Feedback",
    "Mix"
    
};

/* RANGES
 */
static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
     //DRIVE
    juce::NormalisableRange<float>(1.f, 100.f, 0.f, 0.35f),
    // RATE
    juce::NormalisableRange<float>(0.01f, 18.f, 0.f, 0.4f),
    // DEPTH
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    // CENTRE_FREQ
    juce::NormalisableRange<float>(100.f, 2000.f, 0.f, 0.7f),
    // FEEDBACK
    juce::NormalisableRange<float>(-0.9f, 0.9f, 0.f, 1.f),
    // MIX
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f)
};

/* DEFAULT VALUES
 */
static const juce::Array<float> PARAMETER_DEFAULTS {
    // DRIVE
    1.f,
    // RATE
    0.1f,
    // DEPTH
    0.5f,
    // CENTRE_FREQ
    400.f,
    // FB
    0.5f,
    // MIX
    0.5f
    
};

#endif /* ParameterDefines_h */
