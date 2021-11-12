#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    didResizeOutputs();
    _dataModel.addListener(this);
}

MainComponent::~MainComponent()
{
    _dataModel.removeListener(this);
}


/**
 ====================================
 MARK: - Component Overrides -
 ====================================
 */
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}


void MainComponent::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Px = juce::Grid::Px;
    juce::Grid grid;
    
    auto bounds = getLocalBounds().reduced(10);
    auto count = _dataModel.getNumOutputs();
    grid.autoFlow = juce::Grid::AutoFlow::row;
    grid.setGap(Px(5));
    
    auto buttonSize = juce::jmin(bounds.getHeight() / 2,
                                 bounds.getWidth() / count - ((count - 1)));
    
    /// Add Rows
    grid.templateRows.add(Track(Px(buttonSize)));
    grid.templateRows.add(Track(Px(buttonSize)));
    
    /// Add Columns
    for (auto i = 0; i < count; i++)
        grid.templateColumns.add(Track(Px(buttonSize)));
    
    /// Add The Items to the grid
    grid.items.addArray(_goButtons);
    grid.items.addArray(_stopButtons);
    
    /// Perform the layout of the items
    grid.performLayout(bounds);
}




/**
 ====================================
 MARK: - Listeners -
 ====================================
 */

void MainComponent::didResizeOutputs()
{
    DBG("Did Resize Outputs: " << _dataModel.getNumOutputs());
    auto count = _dataModel.getNumOutputs();
    resizeButtons(_goButtons, count, "Go");
    resizeButtons(_stopButtons, count, "Stop");
    
    /// Set Callbacks for Go Buttons
    for (auto i = 0; i < _goButtons.size(); i++)
        if (auto button = _goButtons[i])
            button->onClick = [i, this] {sendGo(i);};
    
    /// Set Callbacks for Stop Buttons
    for (auto i = 0; i < _stopButtons.size(); i++)
        if (auto button = _stopButtons[i])
            button->onClick = [i, this] {sendStop(i);};

    /// Resize all the buttons on the grid.
    resized();
}


void MainComponent::sentMessageToOutput(int index)
{
    DBG("Sent Message: " << index);
}





/**
 ====================================
 MARK: - Button Callbacks -
 ====================================
 */

void MainComponent::sendGo(int index)
{
    _dataModel.sendGO(index);
}


void MainComponent::sendStop(int index)
{
    _dataModel.sendStop(index);
}




/**
 ====================================
 MARK: - Resize Buttons -
 ====================================
 */

void MainComponent::resizeButtons(juce::OwnedArray<juce::TextButton>& buttonArray, int count, const juce::String& buttonName)
{
    auto size = buttonArray.size();
    if (size < count)
    {
        /// Add Elements
        for (auto i = size; i < count; i++)
        {
            auto button = buttonArray.add(new juce::TextButton(buttonName));
            addAndMakeVisible(button);
        }
    }
    else if (size > count)
    {
        /// Remove Elements
        for (auto i = count; i < size; i++)
        {
            buttonArray.removeLast();
        }
    }
    else
    {
        /// Do nothing (This else is superfluious and is only here for tutorials)
    }
}
