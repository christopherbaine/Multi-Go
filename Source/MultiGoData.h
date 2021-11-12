#pragma once

#include <juce_core/juce_core.h>
#include <juce_osc/juce_osc.h>


/**
 Mulit Go Data
 This is the main class for the data model of the multi-go application
 
 TODO: Add Multiple Output Ports
 TODO: Add Output Count Text Box
 TODO: Add GO/STOP Strings For Text
 */

class MultiGoData
{
public:
    
    MultiGoData(const juce::String& hostName, int targetPortNumber);
    ~MultiGoData();
    
    /// Listener Class for our GUI to subscribe to
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void didResizeOutputs() = 0;
        virtual void sentMessageToOutput(int index) = 0; 
    };
    
    /** Getters */
    const bool isConnected() const;
    const int getNumOutputs() const;
    juce::OSCMessage* getGoMessage(int index);
    juce::OSCMessage* getStopMessage(int index);
    
    /**
     Set Number of OSC GO Buttons
     */
    void setCount(int count);
    
    /**
     Send OSC for Index
     */
    void sendGO(int index);
    void sendStop(int index);
    
    /**
     Listeners
     */
    void addListener(Listener* l) {_listeners.add(l);}
    void removeListener(Listener* l) {_listeners.remove(l);}
    
private:
    /** Private implementation to resize one of the arrays for the set count function*/
    void resizeArray(juce::OwnedArray<juce::OSCMessage>& arrayToResize, int count, const juce::String& defaultMessage);
    
private:
    
    /// OSC Data
    juce::OwnedArray<juce::OSCMessage> _oscGoMessages;
    juce::OwnedArray<juce::OSCMessage> _oscStopMessages;
    juce::OSCSender _oscSender;
    bool _isConnected = false;

    /// Listeners
    juce::ListenerList<Listener> _listeners;
};
