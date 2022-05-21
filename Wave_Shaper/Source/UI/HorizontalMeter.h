/*
  ==============================================================================

    HorizontalMeter.h
    Created: 21 May 2022 11:48:35am
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

namespace Gui {
    class HorizontalMeter : public Component
    {
    public:
        void paint(Graphics& g) override
        {
            auto bounds = getLocalBounds().toFloat();
            
            g.setColour(Colours::black.withBrightness(0.6f));
            g.fillRoundedRectangle(bounds, 5.f);
            
            g.setColour(Colours::pink.withBrightness(0.8f));
            // map level from -60.f to 6.f to dimensions of meter
            const auto scaledX =
            jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getWidth()));
            g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.f);
        }
        
        void setLevel(const float value) { level = value; }
    
    private:
        float level = -60.f;
    };
}
