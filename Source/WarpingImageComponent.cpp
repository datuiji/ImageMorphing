/*
  ==============================================================================

    WarpingImageComponent.cpp
    Created: 18 Nov 2021 2:51:36am
    Author:  tuiji da

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WarpingImageComponent.h"

//==============================================================================
WarpingImageComponent::WarpingImageComponent()
{
    threads.resize(10);
    morphingResult.resize(300);
}

WarpingImageComponent::~WarpingImageComponent()
{
}

void WarpingImageComponent::paint (juce::Graphics& g)
{
    g.drawImageAt(warpingImage, 0, 0);
}

juce::Image WarpingImageComponent::warping(const juce::Image& source,
                                           const juce::Image& destination,
                                           const std::vector<juce::Line<float>>& srcLines,
                                           const std::vector<juce::Line<float>>& destLines,
                                           float alpha)
{
    auto width = source.getWidth();
    auto height = source.getHeight();
    juce::Image result (juce::Image::PixelFormat::RGB, width, height, true);
    
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            juce::Point<float> x {(float)i, (float)j};
            juce::Point<float> DSum {0, 0};
            float weightSum = 0;
            for (int lx = 0; lx < srcLines.size(); lx++)
            {
                juce::Point<float> P = interpolation(srcLines.at(lx).getStart(), destLines.at(lx).getStart(), alpha);
                juce::Point<float> Q = interpolation(srcLines.at(lx).getEnd(), destLines.at(lx).getEnd(), alpha);
                
                auto srcP = srcLines.at(lx).getStart();
                auto srcQ = srcLines.at(lx).getEnd();
                auto uvp = transform(x, srcP, srcQ, P, Q);
                
                juce::Point<float> D {uvp.p - x};
                auto weight = getWeight(x, P, Q, uvp.u, uvp.v);
                
                DSum += D * weight;
                weightSum += weight;
            }
            
            juce::Point<float> _x = x + DSum / weightSum;
            
            if (_x.x < 0)
            {
                _x.x = 0;
            }
            else if (_x.x > width - 2)
            {
                _x.x = width - 1;
            }
            
            if (_x.y < 0)
            {
                _x.y = 0;
            }
            else if (_x.y > height - 2)
            {
                _x.y = height - 1;
            }
            
            juce::Colour finalColor = bilinearFilter(_x, source);
            result.setPixelAt(i, j, finalColor);
        }
    }
    
    return result;
}

juce::Point<float> WarpingImageComponent::interpolation(juce::Point<float> x1, juce::Point<float> x2, float t)
{
    juce::Point<float> p;
    p = x1 + (x2 - x1) * t;
    return p;
}

WarpingImageComponent::UVP WarpingImageComponent::transform (juce::Point<float> x,
                                                             juce::Point<float> srcP,
                                                             juce::Point<float> srcQ,
                                                             juce::Point<float> destP,
                                                             juce::Point<float> destQ)
{
    juce::Point<float> p;
    juce::Point<float> PX = {x - destP};
    juce::Point<float> PQ = {destQ - destP};
    juce::Point<float> perpendicularQP = {-PQ.y, PQ.x};

    float u = PX.getDotProduct(PQ) / PQ.getDistanceSquaredFromOrigin();
    float v = PX.getDotProduct(perpendicularQP) / PQ.getDistanceFromOrigin();
    
    juce::Point<float> _PQ {srcQ - srcP};
    juce::Point<float> perpendicular_PQ = {-_PQ.y, PQ.x};
    
    p = srcP + u * _PQ + (v * perpendicular_PQ) / _PQ.getDistanceFromOrigin();
    
    return {u, v, p};
}


float WarpingImageComponent::getWeight (juce::Point<float> x,
                                       juce::Point<float> P,
                                       juce::Point<float> Q,
                                       float u,
                                       float v)
{
    float dist;
    if (u < 0)
    {
        dist = P.getDistanceFrom(x);
    }
    else if (u > 1)
    {
        dist = Q.getDistanceFrom(x);
    }
    else
    {
        dist = std::abs(v);
    }
    
    return std::powf(std::powf(P.getDistanceFrom(Q), p) / (a + dist), b);
}

juce::Colour WarpingImageComponent::colorInterPolation(juce::Colour c1, juce::Colour c2, float t)
{
    auto r = c1.getRed() + (c2.getRed() - c1.getRed()) * t;
    auto g = c1.getGreen() + (c2.getGreen() - c1.getGreen()) * t;
    auto b = c1.getBlue() + (c2.getBlue() - c1.getBlue()) * t;
    
    return juce::Colour(r, g, b);
}

juce::Colour WarpingImageComponent::bilinearFilter(juce::Point<float> _x, const juce::Image& source)
{
    juce::Point<float> topLeft = {std::floor(_x.x), std::floor(_x.y)};
    juce::Point<float> topRight = {std::ceil(_x.x), std::floor(_x.y)};
    juce::Point<float> bottomLeft = {std::floor(_x.x), std::ceil(_x.y)};
    juce::Point<float> bottomRight = {std::ceil(_x.x), std::ceil(_x.y)};
    
    juce::Colour tlColor, trColor, blColor, brColor;
    
    tlColor = source.getPixelAt(topLeft.x, topLeft.y);
    trColor = source.getPixelAt(topRight.x, topRight.y);
    blColor = source.getPixelAt(bottomLeft.x, bottomLeft.y);
    brColor = source.getPixelAt(bottomRight.x, bottomRight.y);
    
    auto x_diff = _x.x - topLeft.x;
    auto y_diff = _x.y - topLeft.y;
    
    juce::Colour c1 (colorInterPolation(tlColor, trColor, x_diff));
    juce::Colour c2 (colorInterPolation(blColor, brColor, x_diff));
    juce::Colour c3 (colorInterPolation(c1, c2, y_diff));
    
    return c3;
}

juce::Image WarpingImageComponent::blending ( const juce::Image& source,
                                              const juce::Image& destination,
                                              const std::vector<juce::Line<float>>& srcLines,
                                              const std::vector<juce::Line<float>>& destLines,
                                              float alpha)
{
    auto img1 = warping(source, destination, srcLines, destLines, alpha);
    auto img2 = warping(destination, source, destLines, srcLines, 1 - alpha);
    
    juce::Image result (juce::Image::PixelFormat::RGB, source.getWidth(), source.getHeight(), true);
    
    for (int i = 0; i < result.getWidth(); i++)
    {
        for (int j = 0; j < result.getHeight(); j++)
        {
            auto color = colorInterPolation(img1.getPixelAt(i, j), img2.getPixelAt(i, j),alpha);
            result.setPixelAt(i, j, color);
        }
    }
    
    return result;
}

void WarpingImageComponent::morphing ( const juce::Image& aImage,
                                       const juce::Image& bImage,
                                       const juce::Image& cImage,
                                       const std::vector<juce::Line<float>>& aLines,
                                       const std::vector<juce::Line<float>>& bLines,
                                       const std::vector<juce::Line<float>>& cLines)
{
    for (int i = 0 ; i < threads.size(); i++)
    {
        if (i < 10)
        {
            threads[i] = std::make_shared<std::thread>(&WarpingImageComponent::generateMorphingAnimation,
                                                       this,
                                                       aImage,
                                                       bImage,
                                                       aLines,
                                                       bLines,
                                                       i * morphingResult.size() / threads.size(),
                                                       (i + 1) * morphingResult.size() / threads.size());
        }
        else if (i >= 10 && i < 20)
        {
            threads[i] = std::make_shared<std::thread>(&WarpingImageComponent::generateMorphingAnimation,
                                                       this,
                                                       bImage,
                                                       cImage,
                                                       bLines,
                                                       cLines,
                                                       i * morphingResult.size() / threads.size(),
                                                       (i + 1) * morphingResult.size() / threads.size());
        }
        else
        {
            threads[i] = std::make_shared<std::thread>(&WarpingImageComponent::generateMorphingAnimation,
                                                       this,
                                                       cImage,
                                                       aImage,
                                                       cLines,
                                                       aLines,
                                                       i * morphingResult.size() / threads.size(),
                                                       (i + 1) * morphingResult.size() / threads.size());
        }
    }
}



void WarpingImageComponent::generateMorphingAnimation( const juce::Image& source,
                                                       const juce::Image& destination,
                                                       const std::vector<juce::Line<float>>& srcLines,
                                                       const std::vector<juce::Line<float>>& destLines,
                                                       int start,
                                                       int end)
{
    for (int i = start; i < end; i++)
    {
        float t = (float)(i % 100) / 100;
        auto image = blending(source, destination, srcLines, destLines, t);
        morphingResult[i] = image;
    }
}
