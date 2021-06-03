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

#include "PluginProcessor.h"
#include "PluginEditor.h"

#if JUCE_INTEL
#define JUCE_SNAP_TO_ZERO(n)    if (! (n < -1.0e-8 || n > 1.0e-8)) n = 0;
#else
#define JUCE_SNAP_TO_ZERO(n)
#endif

GhostFuzzAudioProcessor::GhostFuzzAudioProcessor()
:                                                   //Initialise setup varialbes
_numChannels            (1),
_numSamples			    (1),
_sampleRate			    (1),
_lastUIWidth			(400),
_lastUIHeight			(400)

{
    Reset();                                        //Initialise plugin parameters
    // Start the circular buffer pointers at the beginning
    delayReadPosition_ = 0;
    delayWritePosition_ = 0;
}

GhostFuzzAudioProcessor::~GhostFuzzAudioProcessor()
{
}

//-----------------------------------------------------------------------------
// P R E P A R E   T O   P L A Y
void GhostFuzzAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Allocate and zero the delay buffer (size will depend on current sample rate)
    // Sanity check the result so we don't end up with any zero-length calculations
    delayBufferLength_ = (int)(2.0*sampleRate);
    if(delayBufferLength_ < 1)
        delayBufferLength_ = 1;
    delayBuffer_.setSize(2, delayBufferLength_);
    delayBuffer_.clear();
    
    // This method gives us the sample rate. Use this to figure out what the delay position
    // offset should be (since it is specified in seconds, and we need to convert it to a number
    // of samples)
    delayReadPosition_ = (int)(delayWritePosition_ - (delayLength_ * getSampleRate())
                            + delayBufferLength_) % delayBufferLength_;
                               
    // If sample rate/block size changes or straight after construction
    if (_numSamples != samplesPerBlock || _sampleRate != sampleRate)
    {
        _sampleRate  = sampleRate;
        _numSamples  = samplesPerBlock;
        _numChannels = getTotalNumInputChannels();
    }
}


//-----------------------------------------------------------------------------
// P R O C E S S   B L O C K
void GhostFuzzAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // Helpful information about this block of samples:
    const int numInputChannels = getTotalNumInputChannels();    // How many input channels for our effect?
    const int numOutputChannels = getTotalNumOutputChannels();  // How many output channels for our effect?
    const int numSamples = buffer.getNumSamples();              // How many samples in the buffer for this block?
    
    // Re-check delay time and recalculate buffer length:
    delayReadPosition_ = (int)(delayWritePosition_ - (delayLength_ * getSampleRate())
                               + delayBufferLength_) % delayBufferLength_;
    
    int channel, dpr, dpw; // dpr = delay read pointer; dpw = delay write pointer
    
    // Go through each channel of audio that's passed in. In this example we apply identical
    // effects to each channel, regardless of how many input channels there are. For some effects, like
    // a stereo chorus or panner, you might do something different for each channel.
    for (channel = 0; channel < numInputChannels; ++channel)
    {
        // channelData is an array of length numSamples which contains the audio for one channel
        float* channelData = buffer.getWritePointer(channel);
        
        // delayData is the circular buffer for implementing delay on this channel
        float* delayData = delayBuffer_.getWritePointer (jmin (channel, delayBuffer_.getNumChannels() - 1));
        
        // Make a temporary copy of any state variables declared in PluginProcessor.h which need to be
        // maintained between calls to processBlock(). Each channel needs to be processed identically
        // which means that the activity of processing one channel can't affect the state variable for
        // the next channel.
        dpr = delayReadPosition_;
        dpw = delayWritePosition_;

        // DELAY PROCESSING
        for (int i = 0; i < numSamples; ++i)
        {
            const float in = channelData[i];
            float out = 0.0;
            
            if (!_distortionBypass)
            {
                //DISTORTION PROCESSING             
                //Scale each sample in the delay buffer according to the input gain
                float gain = powf(10.0f, _gainIndB/20.f);                
                delayData[dpr] *= gain;
                
                // Apply selectd distortion type to each sample in the delay buffer
                switch (_typeNumber) {
                    case _hardClipping:
                    {
                        float threshold = 0.5f; 
                        if(delayData[dpr]  > threshold) // positive hard clipping
                        {
                            delayData[dpr] = threshold;
                        }
                        else
                        {
                            if(delayData[dpr]  < - threshold) // negative hard clipping
                            {
                                delayData[dpr] = - threshold;
                            }
                        }
                        break;
                    }                      
                    case _softClipping:
                    {
                        float threshold1 = 1.0f/3.0f;
                        float threshold2 = 2.0f/3.0f;                       
                        if(delayData[dpr]  > threshold1)
                        {
                            if(delayData[dpr] > threshold2) // positive clipping
                            {
                                delayData[dpr] = 1.0f;
                            }
                            else // soft knee (positive)
                            {
                                delayData[dpr] = (3.0f - (2.0f - 3.0f*delayData[dpr])*(2.0f - 3.0f*delayData[dpr]))/3.0f;
                            }
                        }
                        else
                        {
                            if(delayData[dpr]  < -threshold1)
                            {
                                if(delayData[dpr] < -threshold2) // negative clipping
                                {
                                    delayData[dpr] = -1.0f;
                                }
                                else // soft knee (negative)
                                {
                                    delayData[dpr] = - (3.0f - (2.0f + 3.0f*delayData[dpr])*(2.0f + 3.0f*delayData[dpr]))/3.0f;
                                }
                            }
                            else // linear region (-1/3..1/3)
                            {
                                delayData[dpr] *= 2.0f;
                            }
                        }                       
                        delayData[dpr] /= 2.0f; // divide all by 2 to compensate for extra 6 dB gain boost                        
                        break;
                    }                        
                    case _softClippingExp:
                    {
                        
                        if (delayData[dpr] > 0.0f) // positive
                        {
                            delayData[dpr] = 1.0f - expf(-delayData[dpr]);
                        }
                        else // negative
                        {
                            delayData[dpr] = - 1.0f + expf(delayData[dpr]);
                        }
                        break;
                    }                       
                    case _fullWaveRectifier:
                    {                        
                        {
                            delayData[dpr] = fabs(delayData[dpr]);                            
                            break;
                        }
                    }
                    case _halfWaveRectifier:
                    {
                        {
                            delayData[dpr] = 0.5f*(fabs(delayData[dpr])+delayData[dpr]);
                            break;
                        }
                    }
                    default:
                        break;
                }
                
                // In this example, the output is the input plus the contents of the delay buffer (weighted by delayMix)
                // The last term implements a tremolo (variable amplitude) on the whole thing.                
                float outputLevel = powf(10.0f, _outputIndB/20.f);
                delayData[dpr] *= outputLevel;
            }
                
            // If the distrotion is not soloed, play back the dry and wet mix together 
            if(!_distortionSolo)
            {
            out = (dryMix_ / 100 * in + wetMix_ / 100 * delayData[dpr]);
            }
            // Otherwise, just play the wet mix
            else
            {
                out = (wetMix_ / 100 * delayData[dpr]);
            }
            
            // Store the current information in the delay buffer. delayData[dpr] is the delay sample we just read,
            // i.e. what came out of the buffer. delayData[dpw] is what we write to the buffer, i.e. what goes in
            delayData[dpw] = in + (delayData[dpr] * feedback_ / 100);
            
            //Make sure pointers return to zero when they reach the end of the buffer
            if (++dpr >= delayBufferLength_)
                dpr = 0;
            if (++dpw >= delayBufferLength_)
                dpw = 0;
            
            // Store the output sample in the buffer, replacing the input
            channelData[i] = out;
        }
        
        //If the filter is not bypassed, process the buffer with the HPFs and LPFs
        if (!_filterBypass)
        {
            if(channel==0)              // for the first channel
            {
                HighPassL.setCoefficients(juce::IIRCoefficients::makeHighPass(_sampleRate,_lowCutoff));
                HighPassL.processSamples(delayBuffer_.getWritePointer(0),delayBufferLength_);
                LowPassL.setCoefficients(juce::IIRCoefficients::makeLowPass(_sampleRate,_highCutoff));
                LowPassL.processSamples(delayBuffer_.getWritePointer(0),delayBufferLength_);
                
            }
            else if(channel==1)         // for the second channel (if present)
            {
                HighPassR.setCoefficients(juce::IIRCoefficients::makeHighPass(_sampleRate,_lowCutoff));
                HighPassR.processSamples(delayBuffer_.getWritePointer(1),delayBufferLength_);
                LowPassR.setCoefficients(juce::IIRCoefficients::makeLowPass(_sampleRate,_highCutoff));
                LowPassR.processSamples(delayBuffer_.getWritePointer(1),delayBufferLength_);
                
            }
        }
    }
    
    // Having made a local copy of the state variables for each channel, now transfer the result
    // back to the main state variable so they will be preserved for the next call of processBlock()  
    delayReadPosition_ = dpr;
    delayWritePosition_ = dpw;
    
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = numInputChannels; i < numOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}




//-----------------------------------------------------------------------------
// R E S E T  M E T H O D
void GhostFuzzAudioProcessor::Reset()
{
    // Set default values for the buffer and all plugin parameters:
    delayBufferLength_ = 1;
    
    delayLength_ = 0.5;
    dryMix_ = 100;
    wetMix_ = 0;
    feedback_ = 0;
    
    _gainIndB   = 0.0f;
    _outputIndB = 0.0f;    
    _typeNumber = _hardClipping;
    _distortionBypass = false;
    _distortionSolo = false;    
    _lowCutoff = 100;
    _highCutoff = 15000;
    _filterBypass = false;    
}




//-----------------------------------------------------------------------------
// S A V E  S T A T E

void GhostFuzzAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // SAVE STATE INFO
    XmlElement xml("GhostFuzz_XML");
    
    // Knobs
    xml.setAttribute("delayLength_", delayLength_);
    xml.setAttribute("feedback_", feedback_);
    xml.setAttribute("dryMix_", dryMix_);
    xml.setAttribute("wetMix_", wetMix_);
    xml.setAttribute("_gainIndB", _gainIndB);
    xml.setAttribute("_output", _outputIndB);
    xml.setAttribute("_lowCutoff", _lowCutoff);
    xml.setAttribute("_highCutoff", _highCutoff);    
    
    // Combo box
    xml.setAttribute("_type"       ,(int) _typeNumber);
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary(xml, destData);
}

//-----------------------------------------------------------------------------
// R E C A L L  S T A T E
void GhostFuzzAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // LOAD STATE INFO
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    // make sure that it's actually our type of XML object..
    if(xmlState->hasTagName("GhostFuzz_XML"))
    {
        
        // Knobs
        delayLength_    = (float)xmlState->getDoubleAttribute("delayLength_", delayLength_);
        feedback_       = (float)xmlState->getDoubleAttribute("feedback_", feedback_);
        dryMix_         = (float)xmlState->getDoubleAttribute("dryMix_", dryMix_);
        wetMix_         = (float)xmlState->getDoubleAttribute("wetMix_", wetMix_);  
        _gainIndB       = (float)xmlState->getDoubleAttribute("_gainIndB", _gainIndB);
        _outputIndB     = (float)xmlState->getDoubleAttribute("_outputIndB", _outputIndB);
        _lowCutoff      = (float)xmlState->getDoubleAttribute("lowCutoff", _lowCutoff);
        _highCutoff     = (float)xmlState->getDoubleAttribute("highCutoff", _highCutoff);        
        
        //Combo box
        _typeNumber     = (GhostFuzzAudioProcessor::Types) xmlState->getIntAttribute("_type",true);
    }
}


//==============================================================================
// S T A N D A R D  J U C E  M E T H O D S
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GhostFuzzAudioProcessor();
}


void GhostFuzzAudioProcessor::releaseResources()
{
    // When playback stops, you can use this to free up any spare memory, etc.
}


bool GhostFuzzAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GhostFuzzAudioProcessor::createEditor()
{
    return new GhostFuzzAudioProcessorEditor (this);
}

const String GhostFuzzAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GhostFuzzAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

int GhostFuzzAudioProcessor::getNumParameters()
{
    return _PARAMtotalNumParams;
}

float GhostFuzzAudioProcessor::getParameter (int index) // externally accessible
{
    switch (index)
    {
        case kDryMixParam:          return (GetDryMix());
        case kWetMixParam:          return (GetWetMix());
        case kFeedbackParam:        return (GetFeedback());
        case kDelayLengthParam:     return (GetDelay());
            

        case _PARAMgain:            return (GetGainIndB());
        case _PARAMtype:            return (GetType());        
        case _PARAMoutput:          return (GetOutputIndB());
        case _PARAMlowCut:          return (GetLowCutoff());        
        case _PARAMhighCut:         return (GetHighCutoff());
        default:					return 0.0f;
    }
}

void GhostFuzzAudioProcessor::setParameter (int index, float newValue) // externally accessible
{
    switch (index)
    {
        case kDryMixParam:
            dryMix_ = newValue;
            break;
        case kWetMixParam:
            wetMix_ = newValue;
            break;
        case kFeedbackParam:
            feedback_ = newValue;
            break;
        case kDelayLengthParam:
            delayLength_ = newValue;
            delayReadPosition_ = (int)(delayWritePosition_ - (delayLength_ * getSampleRate())
                                       + delayBufferLength_) % delayBufferLength_;
            break;
        case _PARAMgain:
            SetGainIndB(newValue);
            break;
        case _PARAMtype:
            SetType((GhostFuzzAudioProcessor::Types) roundFloatToInt(newValue*_numberOfTypes));
            break;
        case _PARAMoutput:
            SetOutputIndB(newValue);
            break;
        case _PARAMlowCut:
            SetLowCutoff(newValue);
            break;            
        case _PARAMhighCut:
            SetHighCutoff(newValue);
            break;                  
        default:
            break;
    }
}

const String GhostFuzzAudioProcessor::getParameterName (int index) // externally accessible
{
    switch (index)
    {
        case kDryMixParam:     return "Dry Mix";
        case kWetMixParam:     return "Wet Mix";
        case kFeedbackParam:   return "Feedback";
        case kDelayLengthParam:return "Delay (secs)";
            
        case _PARAMgain:            return "Gain (dB)";        
        case _PARAMtype:            return "Type";
        case _PARAMoutput:          return "Output (dB)";
        case _PARAMlowCut:          return "Low Cut (Hz)";
        case _PARAMhighCut:         return "High Cut (Hz)";
        default:					break;
    }
    return String::empty;
}

const String GhostFuzzAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

const String GhostFuzzAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String GhostFuzzAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool GhostFuzzAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool GhostFuzzAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool GhostFuzzAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool GhostFuzzAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

int GhostFuzzAudioProcessor::getNumPrograms()
{
    return 0;
}

int GhostFuzzAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GhostFuzzAudioProcessor::setCurrentProgram (int index)
{
}

const String GhostFuzzAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void GhostFuzzAudioProcessor::changeProgramName (int index, const String& newName)
{
}
