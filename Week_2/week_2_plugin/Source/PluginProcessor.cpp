/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week_2_pluginAudioProcessor::Week_2_pluginAudioProcessor()
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

Week_2_pluginAudioProcessor::~Week_2_pluginAudioProcessor()
{
}

//==============================================================================
const juce::String Week_2_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week_2_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week_2_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week_2_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week_2_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week_2_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week_2_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week_2_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week_2_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week_2_pluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Week_2_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSineWave.initialize(442, sampleRate);
    
}

void Week_2_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week_2_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Week_2_pluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    /*
    static float phase = 0;
    static float phase_lfo = 0;
    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        
        phase_lfo += 5 / getSampleRate();
        float lfo = std::sin(phase_lfo * juce::MathConstants<float>::twoPi);
        
        
        phase += 442 * lfo / getSampleRate();
        float sine_out = std::sin(phase * juce::MathConstants<float>::twoPi);
       
        
        //reset wavetables
        if (phase_lfo > 1.f)
        {
            phase_lfo -= 1.f;
        }
        
        
        if (phase > 1.f)
        {
            phase -= 1.f;
        }
        
        buffer.setSample(0, i, sine_out);
        buffer.setSample(1, i, sine_out);
        
    }
    */
    
    // Left channel = 0 in the audio buffer
    int left = 0;
    
    // Right channel = 1 in the audio buffer
    int right = 1;
    
    // FOR EACH SAMPLE IN THE INCOMING AUDIO BUFFER
    for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
        
        // GET THE NEXT SAMPLE FROM OUR SINE GENERATOR
        float output = mSineWave.getNextSample();
        output *= mSineGain;
        
        // STORE THE OUTPUT TO THE LEFT AND RIGHT CHANNELS OF THE AUDIO BUFFER
        
        // FROM JUCE:
        // void setSample (int destChannel, int destSample, Type newValue)
        
        buffer.setSample(left, sample_index, output);
        
        buffer.setSample(right, sample_index, output);
        
    }
   
}

void Week_2_pluginAudioProcessor::setSineVolume(float inInputVolumeAmp)
{
    mSineGain = inInputVolumeAmp;
}

//==============================================================================
bool Week_2_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week_2_pluginAudioProcessor::createEditor()
{
    return new Week_2_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Week_2_pluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Week_2_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week_2_pluginAudioProcessor();
}
