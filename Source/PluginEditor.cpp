/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "PluginEditor.h"

//==============================================================================
ScopeAudioProcessorEditor::ScopeAudioProcessorEditor (ScopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));

    addAndMakeVisible(waveRepaintRateSlider);
    waveRepaintRateSlider.setRange (2, 2048);
    waveRepaintRateSlider.setValue (2);
    waveRepaintRateSlider.addListener (this);

    addAndMakeVisible(waveBufferSizeSlider);
    waveBufferSizeSlider.setRange (2, 2048);
    waveBufferSizeSlider.setValue (512);
    waveBufferSizeSlider.addListener (this);

    setSize (400, 300);
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

    flexBox.items.add(juce::FlexItem (waveBufferSizeSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    flexBox.items.add(juce::FlexItem (waveRepaintRateSlider).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    flexBox.items.add(juce::FlexItem (audioProcessor.waveViewer).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));

    flexBox.performLayout(bounds);
}
