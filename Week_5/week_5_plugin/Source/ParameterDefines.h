/*
  ==============================================================================

    ParameterDefines.h
    Created: 27 Feb 2022 2:07:14pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once

#ifndef ParameterDefines_h
#define ParameterDefines_h

#include "JuceHeader.h"

// Plugin Parameter Defines

enum {
    GAIN_AMOUNT = 0,
    FM_AMOUNT,
    CARR_FREQ,
    MOD_FREQ,
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Gain Amount",
    "FM Amount",
    "Carrier Hz",
    "Modulator Hz"
};

/* the normaliseable range class will be helpful in the future when working with
 more complicated ranges (ones which aren't 0-1)
 */
static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    // start value, end value, interval, skew/curve
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 10.f, 0.f, 1.f),
    juce::NormalisableRange<float>(40.f, 2000.f, 0.f, 1.f),
    juce::NormalisableRange<float>(05.f, 2000.f, 0.f, 1.f),
};

#endif /* ParameterDefines_h */
