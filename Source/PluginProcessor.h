/*
 This code is developed from the example delay and distortion JUCE code in the
 textbook:
 Digital Audio Effects: Theory, Implementation and Application
 Joshua D. Reiss and Andrew P. McPherson
 https://www.crcpress.com/Audio-Effects-Theory-Implementation-and-Application/Reiss-McPherson/p/book/9781466560284
 
 Distortion code implementation is based on the following paper:
 Brecht De Man and Joshua D. Reiss, "Adaptive Control of Amplitude
 Distortion Effects," 53rd Conference of the Audio Engineering Society,
 2014.
 ------------------------------------------------------------------------------
 The original delay and distortion algorithms are reused and integrateed in 
 combination with custom-written code to process resulting signals independently.
 ------------------------------------------------------------------------------
 The plugin can be compiled to VST, VST3 and AU using the four source files and
 standard JUCE library modules.
 */

#ifndef __PLUGINPROCESSOR_H_88534BAA__
#define __PLUGINPROCESSOR_H_88534BAA__

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>

class GhostFuzzAudioProcessor  : public AudioProcessor
{
public:
    GhostFuzzAudioProcessor();
    ~GhostFuzzAudioProcessor();
    
    IIRFilter HighPassL, HighPassR, LowPassL, LowPassR;     //IIR Filter instances
    
    //==============================================================================
	// V S T   M E T H O D S

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
	void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    AudioProcessorEditor* createEditor();
	bool silenceInProducesSilenceOut() const;
	virtual double getTailLengthSeconds() const {return 0;};
    bool hasEditor() const;
    const String getName() const;
    int getNumParameters();
    float getParameter (int index);
    void setParameter (int index, float newValue);
    const String getParameterName (int index);
    const String getParameterText (int index);
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    bool acceptsMidi() const;
    bool producesMidi() const;
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

	//==============================================================================
	// E N U M S
    int lastUIWidth_, lastUIHeight_;
	enum Parameters
	{
        kDelayLengthParam = 0,
        kDryMixParam,
        kWetMixParam,
        kFeedbackParam,	    
        _PARAMgain,        
        _PARAMtype,
        _PARAMoutput,
        _PARAMlowCut,
        _PARAMhighCut,
		_PARAMtotalNumParams
	};
    
    
    enum Types
	{
        _softClippingExp = 0,
        _softClipping,
        _hardClipping,
        _halfWaveRectifier,
        _fullWaveRectifier,
        _numberOfTypes
	};
	
    // Adjustable parameters:
    float delayLength_; // Length of delay line in seconds
    float dryMix_;      // Mix level of original signal (0-1)
    float wetMix_;      // Mix level of delayed signal (0-1)
    float feedback_;    // Feedback level (0-just less than 1)	
    float _gainIndB;
    float _outputIndB;
    int _lowCutoff;
    int _highCutoff;
    bool _distortionBypass;
    bool _distortionSolo;
    bool _filterBypass;    

    //==============================================================================
	// M E T H O D S
    
    void Reset();

private:

	// Accessors and mutators
    inline float    GetDelay();
    inline float    GetDryMix();
    inline float    GetWetMix();
    inline float    GetFeedback();    
	inline float    GetGainIndB();
	inline float    GetOutputIndB();
	inline int      GetLowCutoff();
	inline int      GetHighCutoff();	
    inline void     SetDelay(float delay);
    inline void     SetDryMix(float dryMix);
    inline void     SetWetMix(float wetMix);
    inline void     SetFeedback(float feedback);
    inline void     SetGainIndB(float gainIndB);
    inline void     SetOutputIndB(float outputIndB);
    inline void     SetLowCutoff(int lowCutoff);
    inline void     SetHighCutoff(int highCutoff);    
    inline          GhostFuzzAudioProcessor::Types    GetType();
    inline void     SetType(Types type);

    // Global system variables
	int	_numChannels;
	int	_numSamples;
    int _sampleRate;
    
    Types _typeNumber;

	bool _isFirstFrame;

    // Circular buffer variables for implementing delay
    AudioSampleBuffer delayBuffer_;
    int delayBufferLength_;
    int delayReadPosition_, delayWritePosition_;	

	int _lastUIWidth, _lastUIHeight;
    
	friend class GhostFuzzAudioProcessorEditor;
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GhostFuzzAudioProcessor);
};

//============================================================================= 
// I N L I N E   F U N C T I O N S   C O D E   S E C T I O N 


//-----------------------------------------------------------------------------
//
inline float
GhostFuzzAudioProcessor::GetDelay()
{
    return delayLength_;
}
inline float
GhostFuzzAudioProcessor::GetDryMix()
{
    return dryMix_;
}
inline float
GhostFuzzAudioProcessor::GetWetMix()
{
    return wetMix_;
}
inline float
GhostFuzzAudioProcessor::GetFeedback()
{
    return feedback_;
}
inline float
GhostFuzzAudioProcessor::GetGainIndB()
{
	return _gainIndB;
}
inline float
GhostFuzzAudioProcessor::GetOutputIndB()
{
	return _outputIndB;
}
inline int
GhostFuzzAudioProcessor::GetLowCutoff()
{
	return _lowCutoff;
}
inline int
GhostFuzzAudioProcessor::GetHighCutoff()
{
	return _highCutoff;
}

//-----------------------------------------------------------------------------
//
inline void
GhostFuzzAudioProcessor::SetDelay(float delay)
{
    delayLength_ = delay;
}
inline void
GhostFuzzAudioProcessor::SetDryMix(float dryMix)
{
    dryMix_ = dryMix;
}
inline void
GhostFuzzAudioProcessor::SetWetMix(float wetMix)
{
    wetMix_ = wetMix;
}
inline void
GhostFuzzAudioProcessor::SetFeedback(float feedback)
{
    feedback_ = feedback;
}
inline void
GhostFuzzAudioProcessor::SetGainIndB(float gainIndB)
{
	_gainIndB = gainIndB;
}
inline void
GhostFuzzAudioProcessor::SetOutputIndB(float outputIndB)
{
	_outputIndB = outputIndB;
}
inline void
GhostFuzzAudioProcessor::SetLowCutoff(int lowCutoff)
{
	_lowCutoff = lowCutoff;
}
inline void
GhostFuzzAudioProcessor::SetHighCutoff(int highCutoff)
{
	_highCutoff = highCutoff;
}

//-----------------------------------------------------------------------------
//
inline GhostFuzzAudioProcessor::Types
GhostFuzzAudioProcessor::GetType()
{
	return _typeNumber;
}


//-----------------------------------------------------------------------------
//
inline void
GhostFuzzAudioProcessor::SetType(Types type)
{
	_typeNumber = type;
}

#endif  // __PLUGINPROCESSOR_H_88534BAA__
