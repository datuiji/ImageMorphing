#pragma once

#include <JuceHeader.h>
#include "SliderWithLabel.h"
#include "PaintImageComponent.h"
#include "WarpingImageComponent.h"
#include "MorphingAnimationComponent.h"
#include "BlendingImageComponent.h"

class MainComponent  : public juce::Component, public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;

private:
    
    PaintImageComponent aImage;
    PaintImageComponent bImage;
    PaintImageComponent cImage;
    WarpingImageComponent aImageWarping;
    WarpingImageComponent bImageWarping;
    WarpingImageComponent cImageWarping;
    BlendingImageComponent blending;
    MorphingAnimationComponent morphingAnimation;
    
    
    juce::TextButton loadAImageButton {"Load A Image"};
    juce::TextButton loadBImageButton {"Load B Image"};
    juce::TextButton loadCImageButton {"Load C Image"};
    juce::TextButton loadPresetLinesButton {"Load Preset Lines"};
    juce::TextButton clearAllLinesButton {"Clear All Lines"};
    juce::TextButton startWarpingButton {"Start Warping"};
    juce::TextButton startBlendingButton {"Start Blending"};
    juce::TextButton startMorphingAnimationButton {"Start Morphing"};
    
    SliderWithLabel alphaSlider {"Alpha", 0.0f, 1.f, 0.5f};
    SliderWithLabel aSlider {"a", 0.0f, 1.f, 1.0f};
    SliderWithLabel bSlider {"b", 0.5f, 2.0f, 2.0f};
    SliderWithLabel pSlider {"p", 0.0f, 1.f, 0.0f};
    
    std::vector<juce::Component*> comps
    {
        &aImage,
        &bImage,
        &cImage,
        &aImageWarping,
        &bImageWarping,
        &cImageWarping,
        &blending,
        &morphingAnimation,
        
        &loadAImageButton,
        &loadBImageButton,
        &loadCImageButton,
        &loadPresetLinesButton,
        &clearAllLinesButton,
        &startWarpingButton,
        &startBlendingButton,
        &startMorphingAnimationButton,
        
        &alphaSlider,
        &aSlider,
        &bSlider,
        &pSlider
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
