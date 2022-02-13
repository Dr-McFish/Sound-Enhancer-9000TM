//------------------------------------------------------------------------
// Copyright(c) 2022 Dr McFish.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

using namespace Steinberg;

namespace McFish {
//------------------------------------------------------------------------
// PlaceboProcessor
//------------------------------------------------------------------------
PlaceboProcessor::PlaceboProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kPlaceboControllerUID);
}

//------------------------------------------------------------------------
PlaceboProcessor::~PlaceboProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instanciated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::terminate ()
{
	// Here the Plug-in will be de-instanciated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    /*if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
				}
			}
		}
	}*/
	

	//-- Flush case: no processing possible
	if (data.numInputs == 0 || data.numSamples == 0)
		return kResultOk;

	// Here you have to implement your processing
	
	int32 numChannels = data.inputs[0].numChannels;

	//get audio buffers using helper-functions
	uint32 sampleFramesSize = Vst::getSampleFramesSizeInBytes(processSetup, data.numSamples);
	void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
	void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

	// Here could check the silent flags
	if (data.inputs[0].silenceFlags != 0) {
		for (int32 i = 0; i < numChannels; i++) 
			if (in[i] != out[i])
				memset(out[i], 0, sampleFramesSize);

		data.outputs[0].silenceFlags = ((uint64)1<< numChannels) -1;
		return kResultTrue;
	}
	
	/*/if (bBypass)
	{
		for (int32 i = 0; i < numChannels; i++)
		{
			// do not need to be copied if the buffers are the same
			if (in[i] != out[i])
			{
				memcpy(out[i], in[i], sampleFramesSize);
			}
		}
		// the input silence flags has to be forward to the output here!
		// very important for the host in order to inform next plug-in in the processing chain
		data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;
	}
	else
	{//*/
	const float gain = 1.1;
	// for each channel (left and right)
	for (int32 i = 0; i < numChannels; i++)
	{
		int32 samples = data.numSamples;
		Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
		Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
		Vst::Sample32 tmp;
		// for each sample in this channel
		while (--samples >= 0)
		{
			// apply gain
			tmp = (*ptrIn++) * gain;
			(*ptrOut++) = tmp;
		}
	}
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API PlaceboProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace McFish
