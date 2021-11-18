/*
  ==============================================================================

    MorphingAnimationComponent.h
    Created: 18 Nov 2021 2:25:47am
    Author:  tuiji da

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MorphingAnimationComponent  : public juce::Component, public juce::Timer
{
public:
    MorphingAnimationComponent();
    ~MorphingAnimationComponent() override;

    void paint (juce::Graphics&) override;
    
    void setMorphingAnimation (std::vector<juce::Image> a) { animation = a;}
    
    void timerCallback() override;
    
private:
    std::vector<juce::Image> animation;
    int index {0};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MorphingAnimationComponent)
};
