/*
  ==============================================================================

    ParameterDefines.h
    Created: 12 Mar 2022 12:34:02pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#ifndef ParameterDefines_h
#define ParameterDefines_h

#include "JuceHeader.h"

// Course Plugin Parameter Defines

enum {
    DELAY_TIME_SECONDS,
    DELAY_FEEDBACK,
    DELAY_MIX,
    DELAY_FEEDBACK_LOWPASS,
    DELAY_FEEDBACK_HIGHPASS,
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Delay Time Seconds",
    "Delay Feedback",
    "Delay Mix",
    "Delay LP",
    "Delay HP"
};

/* RANGES
 */
static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    // DELAY_TIME_SECONDS
    juce::NormalisableRange<float>(0.001f, 1.f, 0.f, 1.f),
    // DELAY_FEEDBACK
    juce::NormalisableRange<float>(0.f, .99f, 0.f, 1.f),
    // DELAY_MIX
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    // DELAY_FEEDBACK_LOWPASS
    juce::NormalisableRange<float>(30.f, 22050.f, 0.f, .25f),
    // DELAY_FEEDBACK_HIGHPASS
    juce::NormalisableRange<float>(30.f, 22050.f, 0.f, .25f),
};

/* DEFAULT VALUES
 */
static const juce::Array<float> PARAMETER_DEFAULTS {
    // DELAY_TIME_SECONDS
    0.05f,
    // DELAY_FEEDBACK
    0.25f,
    // DELAY_MIX
    0.5f,
    // DELAY_FEEDBACK_LOWPASS
    22050.f,
    // DELAY_FEEDBACK_HIGHPASS
    30.f
};

#endif /* ParameterDefines_h */