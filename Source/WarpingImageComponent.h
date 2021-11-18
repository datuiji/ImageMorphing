/*
  ==============================================================================

    WarpingImageComponent.h
    Created: 18 Nov 2021 2:51:36am
    Author:  tuiji da

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <thread>

//==============================================================================
/*
*/
class WarpingImageComponent  : public juce::Component
{
public:
    WarpingImageComponent();
    ~WarpingImageComponent() override;

    void paint (juce::Graphics&) override;
    
    juce::Image warping (const juce::Image& source,
                         const juce::Image& destination,
                         const std::vector<juce::Line<float>>& srcLines,
                         const std::vector<juce::Line<float>>& destLines,
                         float alpha);
    
    juce::Image blending (const juce::Image& source,
                          const juce::Image& destination,
                          const std::vector<juce::Line<float>>& srcLines,
                          const std::vector<juce::Line<float>>& destLines,
                          float alpha);
    
    void morphing (const juce::Image& aImage,
                   const juce::Image& bImage,
                   const juce::Image& cImage,
                   const std::vector<juce::Line<float>>& aLines,
                   const std::vector<juce::Line<float>>& bLines,
                   const std::vector<juce::Line<float>>& cLines);

    void generateMorphingAnimation(const juce::Image& source,
                                   const juce::Image& destination,
                                   const std::vector<juce::Line<float>>& srcLines,
                                   const std::vector<juce::Line<float>>& destLines,
                                   int start,
                                   int end);
    
    void setAlpha (float newAlpha) { alpha = newAlpha;}
    void setA (float newA) { a = newA;}
    void setB (float newB) { b = newB;}
    void setP (float newP) { p = newP;}
    
    std::vector<std::shared_ptr<std::thread>> getThreads() { return threads;}
    
    std::vector<juce::Image>& getMorphingResult() { return morphingResult; }
    
    void setWarpingImage (juce::Image img) { warpingImage = img;}


private:
    
    struct UVP
    {
        float u;
        float v;
        juce::Point<float> p;
    };
    
    juce::Point<float> interpolation(juce::Point<float> x1, juce::Point<float> x2, float t);
    
    WarpingImageComponent::UVP transform  (juce::Point<float> x,
                                           juce::Point<float> srcP,
                                           juce::Point<float> srcQ,
                                           juce::Point<float> destP,
                                           juce::Point<float> destQ);
    
    juce::Colour bilinearFilter(juce::Point<float> x, const juce::Image& source);
    
    float getWeight(juce::Point<float> x,
                   juce::Point<float> P,
                   juce::Point<float> Q,
                   float u,
                   float v);
    
    juce::Colour colorInterPolation(juce::Colour c1, juce::Colour c2, float t);
    
    juce::Image warpingImage;
    
    float alpha {0.5};
    float a {2.0};
    float b {1.0};
    float p {0.0};
    
    std::vector<std::shared_ptr<std::thread>> threads;
    std::vector<juce::Image> morphingResult;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WarpingImageComponent)
};
