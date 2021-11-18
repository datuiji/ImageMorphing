/*
  ==============================================================================

    BlendingImageComponent.cpp
    Created: 18 Nov 2021 2:26:07am
    Author:  tuiji da

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BlendingImageComponent.h"

//==============================================================================
BlendingImageComponent::BlendingImageComponent()
{
}

BlendingImageComponent::~BlendingImageComponent()
{
}

void BlendingImageComponent::paint (juce::Graphics& g)
{
    g.drawImage(image, getLocalBounds().toFloat(), juce::RectanglePlacement::centred);
}
