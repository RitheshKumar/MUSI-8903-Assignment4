/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Vibrato2pluginAudioProcessor::Vibrato2pluginAudioProcessor() : amplParam(nullptr),
                                                               freqParam(nullptr),
                                                               pVibrato(0),
                                                               isBypass(false)
{
    addParameter (amplParam  = new AudioParameterFloat ("ampl",  "VibratoAmplitude", 0.0f, 0.1f, 0.01f));
    addParameter (freqParam = new AudioParameterFloat ("freq", "VibratoFrequency", 0.0f, 50.0f, 5.0f));
    
    //Call the constructor of vibrato class
    CVibrato::createInstance(pVibrato);
}

Vibrato2pluginAudioProcessor::~Vibrato2pluginAudioProcessor()
{
    CVibrato::destroyInstance(pVibrato);
}

//==============================================================================
const String Vibrato2pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Vibrato2pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Vibrato2pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double Vibrato2pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Vibrato2pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Vibrato2pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Vibrato2pluginAudioProcessor::setCurrentProgram (int index)
{
}

const String Vibrato2pluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void Vibrato2pluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Vibrato2pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    if (getTotalNumInputChannels() <= 0) {
        iNumChannel = 2;
    } else {
        iNumChannel = getTotalNumInputChannels();
    }
    pVibrato->initInstance(3.0f, (float)sampleRate, iNumChannel);
    
}

void Vibrato2pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void Vibrato2pluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
//    if (isSliderParamChange) {
        pVibrato->setParam(CVibrato::kParamModFreqInHz, *freqParam);
        pVibrato->setParam(CVibrato::kParamModWidthInS, *amplParam);
//    }
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    if (!isBypass) {
        pVibrato->setParam(CVibrato::kParamModFreqInHz, *freqParam);
        pVibrato->setParam(CVibrato::kParamModWidthInS, *amplParam);
        
    }
    else {
        pVibrato->setParam(CVibrato::kParamModFreqInHz, 0.f);
        pVibrato->setParam(CVibrato::kParamModWidthInS, 0.f);
        //Hello!
//        std::cout<<"Hello from bypassing\n";
    }
    pVibrato->process( buffer.getArrayOfReadPointers(), buffer.getArrayOfWritePointers(), buffer.getNumSamples());
    
}

void Vibrato2pluginAudioProcessor::processBlockBypassed(AudioSampleBuffer& buffer, MidiBuffer& midiMessage) {
//    float** writePointer = buffer.getArrayOfWritePointers();
//    pVibrato->process(buffer.getArrayOfReadPointers(), buffer.getArrayOfWritePointers(), buffer.getNumSamples());
}

//==============================================================================
bool Vibrato2pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Vibrato2pluginAudioProcessor::createEditor()
{
    return new Vibrato2pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Vibrato2pluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Vibrato2pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Vibrato2pluginAudioProcessor();
}

// get the information of bypass
bool Vibrato2pluginAudioProcessor:: getBypass() {
    return isBypass;
}

// set the condition of bypass
void Vibrato2pluginAudioProcessor::setBypass(bool bypass) {
    isBypass = bypass;
}

void Vibrato2pluginAudioProcessor::setVibratoParam(CVibrato::VibratoParam_t eParam, float fParamValue) {

    switch (eParam)
    {
        case CVibrato::kParamModFreqInHz:
            fFreqValue = *freqParam;
            break;
        case CVibrato::kParamModWidthInS:
            fAmpValue = *amplParam;
            break;
        case CVibrato::kNumVibratoParams: //Just break if it is either default or the lastEnum
        default:
            break;
            
    }

}



float Vibrato2pluginAudioProcessor::getParameter(int parameterIndex) {
    switch (parameterIndex) {
        case 0:
            return *amplParam;
            break;
        case 1:
            return *freqParam;
            break;
        default:
            return 0;
            break;
    }
}

void Vibrato2pluginAudioProcessor::setParameterNotifyingHost (int parameterIndex, float newValue) {
    switch (parameterIndex) {
        case 0:
            *amplParam = newValue;
            break;
        case 1:
            *freqParam = newValue;
            break;
        default:
            break;
    }

}