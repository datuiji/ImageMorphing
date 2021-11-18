#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 1000);
    for (auto& comp : comps)
        addAndMakeVisible(comp);
    
    alphaSlider.getSlider().addListener(this);
    aSlider.getSlider().addListener(this);
    bSlider.getSlider().addListener(this);
    pSlider.getSlider().addListener(this);
    
    
    loadAImageButton.onClick = [this]()
    {
        aImage.loadImage();
    };
    
    loadBImageButton.onClick = [this]()
    {
        bImage.loadImage();
    };

    loadCImageButton.onClick = [this]()
    {
        cImage.loadImage();
    };
    
    clearAllLinesButton.onClick = [this]()
    {
        aImage.getFeatureLines().clear();
        aImage.repaint();
        bImage.getFeatureLines().clear();
        bImage.repaint();
        cImage.getFeatureLines().clear();
        cImage.repaint();
    };
    
    loadPresetLinesButton.onClick = [this]()
    {
        aImage.setFeatureLines(aImage.a_prestLines);
        aImage.repaint();
        bImage.setFeatureLines(bImage.b_prestLines);
        bImage.repaint();
        cImage.setFeatureLines(cImage.c_prestLines);
        cImage.repaint();
    };
    
    startWarpingButton.onClick = [this]()
    {
        auto aw = aImageWarping.warping(aImage.getImage(),
                              bImage.getImage(),
                              aImage.getFeatureLines(),
                              bImage.getFeatureLines(),
                              alphaSlider.getSlider().getValue());
        aImageWarping.setWarpingImage(aw);
        aImageWarping.repaint();
        
        auto bw = bImageWarping.warping(bImage.getImage(),
                              aImage.getImage(),
                              bImage.getFeatureLines(),
                              aImage.getFeatureLines(),
                              alphaSlider.getSlider().getValue());
        bImageWarping.setWarpingImage(bw);
        bImageWarping.repaint();
        
        auto cw = cImageWarping.warping(cImage.getImage(),
                              aImage.getImage(),
                              cImage.getFeatureLines(),
                              aImage.getFeatureLines(),
                              alphaSlider.getSlider().getValue());
        cImageWarping.setWarpingImage(cw);
        cImageWarping.repaint();


    };
    
    startBlendingButton.onClick = [&]()
    {
        auto img = aImageWarping.blending(aImage.getImage(),
                                          bImage.getImage(),
                                          aImage.getFeatureLines(),
                                          bImage.getFeatureLines(),
                                          alphaSlider.getSlider().getValue());
        
        blending.setBlendingResult(img);
        blending.repaint();
    };
    
    startMorphingAnimationButton.onClick = [&]()
    {
        aImageWarping.morphing(aImage.getImage(),
                               bImage.getImage(),
                               cImage.getImage(),
                               aImage.getFeatureLines(),
                               bImage.getFeatureLines(),
                               cImage.getFeatureLines());
        
        auto threads = aImageWarping.getThreads();
        
        for (auto& thread : threads)
            thread->join();
        
        morphingAnimation.setMorphingAnimation(aImageWarping.getMorphingResult());
    };

}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    
    g.setColour(juce::Colours::white);
    for (auto& comp : comps)
        g.drawRect(comp->getBounds());
}

void MainComponent::resized()
{
    auto rowFlexBoxHelper = [&](std::vector<juce::Component*> comps)
    {
        juce::FlexBox flexbox;
        flexbox.flexDirection = juce::FlexBox::Direction::row;
        flexbox.justifyContent = juce::FlexBox::JustifyContent::center;
        flexbox.flexWrap = juce::FlexBox::Wrap::noWrap;
        
        for (auto& comp : comps)
            flexbox.items.add(juce::FlexItem(*comp).withFlex(1.0).withMargin(4));
        
        return flexbox;
    };
    
    auto columnFlexBoxHelper = [&](std::vector<juce::Component*> comps)
    {
        juce::FlexBox flexbox;
        flexbox.flexDirection = juce::FlexBox::Direction::column;
        flexbox.justifyContent = juce::FlexBox::JustifyContent::center;
        flexbox.flexWrap = juce::FlexBox::Wrap::noWrap;
        
        for (auto& comp : comps)
            flexbox.items.add(juce::FlexItem(*comp).withFlex(1.0).withMargin(4));
        
        return flexbox;
    };

    
    auto firstRow = rowFlexBoxHelper({&aImage, &bImage, &cImage});
    auto secondRow = rowFlexBoxHelper({&aImageWarping, &bImageWarping, &cImageWarping});
    auto thirdRow = rowFlexBoxHelper({&blending, &morphingAnimation});
    
    juce::FlexBox left;
    left.flexDirection = juce::FlexBox::Direction::column;
    left.justifyContent = juce::FlexBox::JustifyContent::center;
    left.flexWrap = juce::FlexBox::Wrap::noWrap;
    
    left.items.addArray(
    {
        juce::FlexItem(firstRow).withFlex(0.42f).withMargin(4),
        juce::FlexItem(secondRow).withFlex(0.42f).withMargin(4),
        juce::FlexItem(thirdRow).withFlex(1.0f).withMargin(4)
    });
    
    
    auto sliderAndButtons = columnFlexBoxHelper(
    {
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
    });
    
    juce::FlexBox globalControl;
    globalControl.flexDirection = juce::FlexBox::Direction::row;
    globalControl.justifyContent = juce::FlexBox::JustifyContent::center;
    globalControl.flexWrap = juce::FlexBox::Wrap::noWrap;
    
    globalControl.items.add(juce::FlexItem(left).withFlex(4.0), juce::FlexItem(sliderAndButtons).withFlex(1.0));
    
    globalControl.performLayout(getLocalBounds());
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &alphaSlider.getSlider())
    {
        aImageWarping.setAlpha(alphaSlider.getSlider().getValue());
        bImageWarping.setAlpha(alphaSlider.getSlider().getValue());
        cImageWarping.setAlpha(alphaSlider.getSlider().getValue());
    }
    else if (slider == &aSlider.getSlider())
    {
        aImageWarping.setA(aSlider.getSlider().getValue());
        bImageWarping.setA(aSlider.getSlider().getValue());
        cImageWarping.setA(aSlider.getSlider().getValue());
    }
    else if (slider == &bSlider.getSlider())
    {
        aImageWarping.setB(bSlider.getSlider().getValue());
        bImageWarping.setB(bSlider.getSlider().getValue());
        cImageWarping.setB(bSlider.getSlider().getValue());
    }
    else if (slider == &pSlider.getSlider())
    {
        aImageWarping.setP(pSlider.getSlider().getValue());
        bImageWarping.setP(pSlider.getSlider().getValue());
        cImageWarping.setP(pSlider.getSlider().getValue());
    }

}
