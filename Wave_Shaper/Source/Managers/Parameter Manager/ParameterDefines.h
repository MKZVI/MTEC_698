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
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Drive"
};

/* RANGES
 */
static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    // DRIVE
    juce::NormalisableRange<float>(1.f, 40.f, 0.f, 1.f),
};

/* DEFAULT VALUES
 */
static const juce::Array<float> PARAMETER_DEFAULTS {
    // DRIVE
    1.f,
};

#endif /* ParameterDefines_h */
