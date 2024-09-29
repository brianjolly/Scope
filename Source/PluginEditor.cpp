/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ScopeAudioProcessorEditor::ScopeAudioProcessorEditor (ScopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), waveViewer(2)
{
    waveViewer.setRepaintRate(45);
    waveViewer.setBufferSize(512);
    waveViewer.setSamplesPerBlock(4);
    waveViewer.setColours(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
    addAndMakeVisible(waveViewer);

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
    flexBox.items.add(juce::FlexItem (waveViewer).withMinHeight(50.0f).withMinWidth(50.0f).withFlex(1));
    flexBox.performLayout(bounds);
}
