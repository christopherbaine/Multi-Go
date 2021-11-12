#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "MultiGoData.h"


class MainComponent  : public juce::Component, public MultiGoData::Listener
{
public:
    MainComponent();
    ~MainComponent() override;
    
private:
    /// Component Overrides
    void paint (juce::Graphics&) override;
    void resized() override;

    /// Listener
    void didResizeOutputs() override;
    void sentMessageToOutput(int index) override;

    /// Button Callbacks
    void sendGo(int index);
    void sendStop(int index);
    
    /// Resize Buttons
    void resizeButtons(juce::OwnedArray<juce::TextButton>& buttonArray, int count, const juce::String& buttonName);
    
private:
    
    /// Data
    MultiGoData _dataModel {"127.0.0.1", 8000};
    
    /// Buttons
    juce::OwnedArray<juce::TextButton> _goButtons;
    juce::OwnedArray<juce::TextButton> _stopButtons;
    
    /// Utility
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
