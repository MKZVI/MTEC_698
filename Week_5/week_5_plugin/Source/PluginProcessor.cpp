/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Week_5_pluginAudioProcessor::Week_5_pluginAudioProcessor()
: AudioProcessor (BusesProperties()
                 .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    
    mParameterManager.reset(new ParameterManager(this));
    
   
}

Week_5_pluginAudioProcessor::~Week_5_pluginAudioProcessor()
{
}

//==============================================================================
const juce::String Week_5_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week_5_pluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Week_5_pluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Week_5_pluginAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double Week_5_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week_5_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Week_5_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week_5_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week_5_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week_5_pluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Week_5_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSineWave1.initialize(442, sampleRate);
    mSineWave1FMOperator.initialize(442, sampleRate);
    mDelayLeft.initialize(sampleRate);
    mDelayRight.initialize(sampleRate);
}

void Week_5_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week_5_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

float mtof(float n)
{
    return 440.f * pow(2.f, (n - 69.f)/12.f);
}


void Week_5_pluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //mtof formula
    //440.0 * pow(2.0, (midi note - 69)/12)
    
    mSineWave1FMOperator.setParameters(mParameterManager->getCurrentValue(MOD_FREQ),
                                       mParameterManager->getCurrentValue(FM_AMOUNT));
    
    mSineWave1.setParameters(mParameterManager->getCurrentValue(CARR_FREQ),
                             mParameterManager->getCurrentValue(GAIN_AMOUNT));
    
    mDelayLeft.setParameters(mParameterManager->getCurrentValue(DELAY_TIME_SECONDS),
                             mParameterManager->getCurrentValue(DELAY_FEEDBACK),
                             mParameterManager->getCurrentValue(DELAY_MIX));
    
    mDelayRight.setParameters(mParameterManager->getCurrentValue(DELAY_TIME_SECONDS),
                              mParameterManager->getCurrentValue(DELAY_FEEDBACK),
                              mParameterManager->getCurrentValue(DELAY_MIX));
    
    for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
        
        float fm_operator = mSineWave1FMOperator.getNextSample();
        float output = mSineWave1.getNextSampleWithFM(fm_operator);
        
        buffer.setSample(0, sample_index, output);
        buffer.setSample(1, sample_index, output);
    }
    
    mDelayLeft.processBlock(buffer.getWritePointer(0), buffer.getNumSamples());
    mDelayRight.processBlock(buffer.getWritePointer(1), buffer.getNumSamples());
}

    

ParameterManager* Week_5_pluginAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}



//==============================================================================
bool Week_5_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week_5_pluginAudioProcessor::createEditor()
{
    return new Week_5_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Week_5_pluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto tree_state = mParameterManager->getValueTree()->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
    
    /* */
    DBG(xml->toString());
    
    /* store as binary */
    copyXmlToBinary(*xml, destData);
}

void Week_5_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get()) {
        
        DBG(xmlState->toString());
        
        juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*xmlState);
        mParameterManager->getValueTree()->replaceState(parameter_tree);
        
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week_5_pluginAudioProcessor();
}
