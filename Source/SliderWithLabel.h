/*
  ==============================================================================

    SliderWithLabel.h
    Created: 18 Nov 2021 2:24:59am
    Author:  tuiji da

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SliderWithLabel  : public juce::Component
{
public:
    SliderWithLabel(juce::String, float min, float max, float defaultValue);
    ~SliderWithLabel() override;

    void paint (juce::Graphics&) override;
    
    void resized() override;
    
    juce::Slider& getSlider() { return slider;}

private:
    juce::Slider slider;
    juce::String title;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderWithLabel)
};
