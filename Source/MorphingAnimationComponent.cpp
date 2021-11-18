/*
  ==============================================================================

    MorphingAnimationComponent.cpp
    Created: 18 Nov 2021 2:25:47am
    Author:  tuiji da

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MorphingAnimationComponent.h"

//==============================================================================
MorphingAnimationComponent::MorphingAnimationComponent()
{
    startTimerHz(30);
}

MorphingAnimationComponent::~MorphingAnimationComponent()
{
    stopTimer();
}

void MorphingAnimationComponent::paint (juce::Graphics& g)
{
    if (animation.size() != 0)
    {
        g.drawImage(animation[index++ % animation.size()], getLocalBounds().toFloat(), juce::RectanglePlacement::centred);
    }
}

void MorphingAnimationComponent::timerCallback()
{
    repaint();
}
