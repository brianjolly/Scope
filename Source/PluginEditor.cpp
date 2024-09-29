/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "PluginEditor.h"

//==============================================================================
ScopeAudioProcessorEditor::ScopeAudioProcessorEditor (ScopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
    //audioProcessor.waveViewer.setTransform(juce::AffineTransform::rotation(90.f));

    addAndMakeVisible(waveRepaintRateSlider);
    waveRepaintRateSlider.setRange (2, 2048);
    waveRepaintRateSlider.setValue (2);
    waveRepaintRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    waveRepaintRateSlider.addListener (this);

    addAndMakeVisible(waveBufferSizeSlider);
    waveBufferSizeSlider.setRange (2, 2048);
    waveBufferSizeSlider.setValue (512);
    waveBufferSizeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    waveBufferSizeSlider.addListener (this);

    setSize (500, 500);
}

ScopeAudioProcessorEditor::~ScopeAudioProcessorEditor()
{
}

//==============================================================================
void ScopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ScopeAudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    juce::FlexBox flexBox;

    const int border = 120;

    waveRepaintRateSlider.setBounds(border, 20, getWidth() - border, 20);
    waveBufferSizeSlider.setBounds(border, 50, getWidth() - border, 50);
    //flexBox.items.add(juce::FlexItem (waveBufferSizeSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    //flexBox.items.add(juce::FlexItem (waveRepaintRateSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    flexBox.items.add(juce::FlexItem (audioProcessor.waveViewer).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));

    flexBox.performLayout(bounds);
}
