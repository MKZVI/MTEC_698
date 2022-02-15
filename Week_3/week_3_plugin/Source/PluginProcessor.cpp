/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week_3_pluginAudioProcessor::Week_3_pluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Week_3_pluginAudioProcessor::~Week_3_pluginAudioProcessor()
{
}

//==============================================================================
const juce::String Week_3_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week_3_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week_3_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week_3_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week_3_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week_3_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week_3_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week_3_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week_3_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week_3_pluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Week_3_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    mCarrier.initialize(mCarrierFreq, sampleRate);
    mModulator.initialize(mModFreq, sampleRate);
    mSmoothGain.reset(sampleRate, 1.f);
    mSmoothIndex.reset(sampleRate, 1.f);
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Week_3_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week_3_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Week_3_pluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //assign channel names
    int left = 0;
    int right = 1;
    
    
    
    //FOR EACH SAMPLE IN THHE INCOMING AUDIO BUFFER
    for(int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++)
    {
        
        
       
       
        //GET NEXT OUTPUT SAMPLE
        
        mCarrierGain = mSmoothGain.getNextValue();
        mCarrier.setFrequency(mCarrierFreq);
        
        mModIndex = mSmoothGain.getNextValue();
        mModulator.setFrequency(mModFreq);
        
        float output = mCarrier.FM(mModulator);
        //mCarrier.FM(mModulator);
        //float output = mCarrier.getNextSample();
        
        
        
        output *= mCarrierGain;
        
        buffer.setSample(left, sample_index, output);
        buffer.setSample(right, sample_index, output);
    }
    
}

void Week_3_pluginAudioProcessor::setCarrierVolume(float inInputVolumeAmp)
{
    mSmoothGain.setTargetValue(inInputVolumeAmp);
    //mCarrierGain = inInputVolumeAmp;
}

void Week_3_pluginAudioProcessor::setCarrierFreq(float inInputCarrFreq)
{
    mCarrierFreq = inInputCarrFreq;
}

void Week_3_pluginAudioProcessor::setModIndex(float inInputModIndex)
{
    mSmoothIndex.setTargetValue(inInputModIndex);
    //mModIndex = inInputModIndex;
}

void Week_3_pluginAudioProcessor::setModFreq(float inInputModFreq)
{
    mModFreq = inInputModFreq;
}

//==============================================================================
bool Week_3_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week_3_pluginAudioProcessor::createEditor()
{
    return new Week_3_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Week_3_pluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Week_3_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week_3_pluginAudioProcessor();
}
