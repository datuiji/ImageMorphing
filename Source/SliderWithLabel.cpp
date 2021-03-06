/*
  ==============================================================================

    SliderWithLabel.cpp
    Created: 18 Nov 2021 2:24:59am
    Author:  tuiji da

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SliderWithLabel.h"

//==============================================================================
SliderWithLabel::SliderWithLabel(juce::String t, float min, float max, float defaultValue): title(t)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setRange(min, max, 0.1);
    slider.setValue(defaultValue);
    slider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, slider.getTextBoxWidth(), slider.getTextBoxHeight());
    
    addAndMakeVisible(slider);
}

SliderWithLabel::~SliderWithLabel()
{
}

void SliderWithLabel::paint (juce::Graphics& g)
{
    auto bound = getLocalBounds();
    
    g.setColour(juce::Colours::white);
    g.drawFittedText(title, bound.removeFromLeft(40), juce::Justification::centred, 1);
}

void SliderWithLabel::resized()
{
    auto bound = getLocalBounds();
    bound.removeFromLeft(40);
    slider.setBounds(bound);
}
