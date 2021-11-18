/*
  ==============================================================================

    PaintImageComponent.cpp
    Created: 18 Nov 2021 2:25:26am
    Author:  tuiji da

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PaintImageComponent.h"

//==============================================================================
PaintImageComponent::PaintImageComponent()
{
    
}

PaintImageComponent::~PaintImageComponent()
{
}

void PaintImageComponent::paint (juce::Graphics& g)
{
    g.drawImageAt(image, 0, 0);
    
    if (featureLine.size() != 0)
    {
        g.setColour(juce::Colours::red);
        for (auto& line : featureLine)
            g.drawArrow(line, 2.0f, 10.f, 10.f);
    }
    
}

void PaintImageComponent::mouseDown (const juce::MouseEvent& e)
{
    p1 = e.getPosition().toFloat();
}

void PaintImageComponent::mouseDrag (const juce::MouseEvent& e)
{
    p2 = e.getPosition().toFloat();
}

void PaintImageComponent::mouseUp (const juce::MouseEvent& e)
{
    if (p1 != p2)
    {
        featureLine.push_back({p1, p2});
        repaint();
    }
}

void PaintImageComponent::loadImage()
{
    chooser = std::make_unique<juce::FileChooser> ("Select a image to show...",
                                                    juce::File{});
    
    auto chooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
    {
        auto file = fc.getResult();

        if (file != juce::File{})
        {
            image = juce::ImageCache::getFromFile(file);
            repaint();
        }

    });
}

