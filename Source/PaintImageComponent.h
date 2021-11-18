/*
  ==============================================================================

    PaintImageComponent.h
    Created: 18 Nov 2021 2:25:26am
    Author:  tuiji da

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PaintImageComponent  : public juce::Component
{
public:
    PaintImageComponent();
    ~PaintImageComponent() override;

    void paint (juce::Graphics&) override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;
    
    std::vector<juce::Line<float>>& getFeatureLines() { return featureLine; }
    
    juce::Image& getImage() { return image;}
    
    void setFeatureLines(std::vector<juce::Line<float>>& line) { featureLine = line; }
    
    void showFeatureLine ()
    {
        for (auto line : featureLine)
        {
            DBG("juce::Line<float> (" << line.getStart().toString() << ", " << line.getEnd().toString() << ")");
        }
    }
    
    std::vector<juce::Line<float>> a_prestLines
    {
        juce::Line<float> (116, 38, 115, 94),
        juce::Line<float> (60, 25, 97, 33),
        juce::Line<float> (130, 34, 172, 29),
        juce::Line<float> (62, 47, 95, 50),
        juce::Line<float> (135, 49, 167, 48),
        juce::Line<float> (90, 133, 138, 132),
        juce::Line<float> (40, 64, 55, 133),
        juce::Line<float> (60, 146, 72, 182),
        juce::Line<float> (187, 69, 173, 136),
        juce::Line<float> (168, 148, 167, 176),
    };
    
    std::vector<juce::Line<float>> b_prestLines
    {
        juce::Line<float> (128, 31, 126, 125),
        juce::Line<float> (31, 11, 78, 15),
        juce::Line<float> (178, 21, 221, 14),
        juce::Line<float> (30, 19, 75, 29),
        juce::Line<float> (178, 33, 218, 23),
        juce::Line<float> (81, 175, 171, 176),
        juce::Line<float> (8, 59, 7, 136),
        juce::Line<float> (7, 154, 7, 172),
        juce::Line<float> (250, 56, 251, 121),
        juce::Line<float> (251, 137, 251, 166),
    };
    
    std::vector<juce::Line<float>> c_prestLines
    {
        juce::Line<float> (129, 27, 129, 77),
        juce::Line<float> (87, 21, 111, 28),
        juce::Line<float> (145, 28, 162, 18),
        juce::Line<float> (86, 36, 105, 40),
        juce::Line<float> (146, 41, 164, 36),
        juce::Line<float> (112, 110, 142, 108),
        juce::Line<float> (78, 37, 87, 76),
        juce::Line<float> (88, 84, 97, 103),
        juce::Line<float> (182, 39, 174, 76),
        juce::Line<float> (171, 84, 161, 103),
    };
    
    void loadImage();


private:
    std::vector<juce::Line<float>> featureLine;
    juce::Point<float> p1;
    juce::Point<float> p2;
    
    std::unique_ptr<juce::FileChooser> chooser;
    juce::Image image;
    
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PaintImageComponent)
};
