/*
  ==============================================================================

    VerticalGradientMeter.h
    Created: 20 May 2022 5:45:34pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#include "Juceheader.h"

namespace Gui

{

class VerticalGradientMeter : public Component

{
public:
    
    /*%%*/
    VerticalGradientMeter();
    
    /*%%*/
    ~VerticalGradientMeter();
    
    /*%%*/
    void paint(Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        
        g.setColour(Colours::black);
        g.fillRect(bounds);
    }
    
    
    /*%%*/
    void resized() override
    {
       
        const auto bounds = getLocalBounds().toFloat();
        
        gradient = ColourGradient {
            Colours::black,
            bounds.getBottomLeft(),
            Colours::deeppink,
            bounds.getTopLeft(),
            false
        };
    }
    
    
private:
    
    ColourGradient gradient
    {};
    
  };
}
