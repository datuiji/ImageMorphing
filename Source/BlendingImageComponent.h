/*
  ==============================================================================

    BlendingImageComponent.h
    Created: 18 Nov 2021 2:26:07am
    Author:  tuiji da

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BlendingImageComponent  : public juce::Component
{
public:
    BlendingImageComponent();
    ~BlendingImageComponent() override;

    void paint (juce::Graphics&) override;
    
    void setBlendingResult (juce::Image& img) { image = img;}

private:
    juce::Image image;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlendingImageComponent)
};
