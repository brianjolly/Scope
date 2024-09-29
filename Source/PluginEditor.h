/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"

//==============================================================================
/**
*/
class ScopeAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                   public juce::Slider::Listener
{
public:
    ScopeAudioProcessorEditor (ScopeAudioProcessor&);
    ~ScopeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ScopeAudioProcessor& audioProcessor;

    juce::Slider waveRepaintRateSlider;
    juce::Slider waveBufferSizeSlider;

    void sliderValueChanged (juce::Slider* slider) override
    {
        if (slider == &waveRepaintRateSlider)
        {
            audioProcessor.waveViewer.setRepaintRate(
                waveRepaintRateSlider.getValue()
            );
        } else if (slider == &waveBufferSizeSlider){
            audioProcessor.waveViewer.setBufferSize(
                waveBufferSizeSlider.getValue()
            );
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopeAudioProcessorEditor)
};
