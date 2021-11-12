#include "MultiGoData.h"

/**
 ------------------------------------------------------------
 ====================================
 MARK: - MultiGo Data -
 ====================================
 ------------------------------------------------------------
 */
MultiGoData::MultiGoData(const juce::String& hostName, int targetPortNumber)
{
    /// Connect to Port
    _isConnected = _oscSender.connect(hostName, targetPortNumber);
    
    /// Resize Number of Go buttons
    setCount(4);
}


MultiGoData::~MultiGoData() {}


/**
 ====================================
 MARK: - Getters -
 ====================================
 */

const bool MultiGoData::isConnected() const
{
    return _isConnected;
}


const int MultiGoData::getNumOutputs() const
{
    return _oscGoMessages.size();
}


juce::OSCMessage* MultiGoData::getGoMessage(int index)
{
    return _oscGoMessages[index];
}


juce::OSCMessage* MultiGoData::getStopMessage(int index)
{
    return _oscStopMessages[index];
}




/**
 ====================================
 MARK: - Set Count -
 ====================================
 */

void MultiGoData::setCount(int count)
{
    resizeArray(_oscGoMessages, count, "/Go");
    resizeArray(_oscStopMessages, count, "/Stop");
    _listeners.call([](Listener& l) {l.didResizeOutputs();});
}


void MultiGoData::resizeArray(juce::OwnedArray<juce::OSCMessage>& arrayToResize, int count, const juce::String& defaultMessage)
{
    auto size = arrayToResize.size();
    if (size < count)
    {
        /// Add Elements
        for (auto i = size; i < count; i++)
        {
            arrayToResize.add(new juce::OSCMessage(defaultMessage + "/" + juce::String(i)));
        }
    }
    else if (size > count)
    {
        /// Remove Elements
        for (auto i = count; i < size; i++)
        {
            arrayToResize.removeLast();
        }
    }
    else
    {
        /// Do nothing (This else is superfluious and is only here for tutorials)
    }
}



/**
 ====================================
 MARK: - OSC Send -
 ====================================
 */

void MultiGoData::sendGO(int index)
{
    if (auto msg = _oscGoMessages[index])
    {
        _oscSender.send(*msg);
        _listeners.call([index](Listener& l) {l.sentMessageToOutput(index);});
    }
}


void MultiGoData::sendStop(int index)
{
    if (auto msg = _oscStopMessages[index])
    {
        _oscSender.send(*msg);
        _listeners.call([index](Listener& l) {l.sentMessageToOutput(index);});
    }
}
