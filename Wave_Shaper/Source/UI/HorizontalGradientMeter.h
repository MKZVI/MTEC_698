/*
  ==============================================================================

    HorizontalGradientMeter.h
    Created: 21 May 2022 10:53:33am
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
namespace Gui

{
    
    class HorizontalGradientMeter : public Component
    
    {
    public:
        
        /*%%*/
        HorizontalGradientMeter(std::function<float()>&& valueFunction) : valueSupplier(std::move(valueFunction))
        {
            
        }
        
        /*%%*/
        ~HorizontalGradientMeter()
        {
            
        }
        
        /*%%*/
        void paint(Graphics& g) override
        {
            
            const auto level = valueSupplier();
            auto bounds = getLocalBounds().toFloat();
            
            g.setColour(Colours::black);
            g.fillRect(bounds);
            g.setGradientFill(gradient);
            //const auto ScaledX =
            //jmap(level, -60.f, 6.f, 0, static_cast<float>(getWidth()));
        }
        
        
        /*%%*/
        void resized() override
        {
            
            const auto bounds = getLocalBounds().toFloat();
            
            gradient = ColourGradient {
                Colours::black,
                bounds.getBottomLeft(),
                Colours::deeppink,
                bounds.getBottomRight(),
                false
            };
            gradient.addColour(0.5, Colours::red);
        }
        
        
    private:
        
        std::function<float()> valueSupplier;
        ColourGradient gradient{};
        
    };
}
