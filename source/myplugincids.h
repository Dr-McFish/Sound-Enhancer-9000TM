//------------------------------------------------------------------------
// Copyright(c) 2022 Dr McFish.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

enum bypassParams : Steinberg::Vst::ParamID
{
	kIsBypassID = 102,
};
namespace McFish {
//------------------------------------------------------------------------
static const Steinberg::FUID kPlaceboProcessorUID (0x70B0E0A5, 0xBFE15E80, 0x8B1969D2, 0x48F2D461);
static const Steinberg::FUID kPlaceboControllerUID (0x574A97BB, 0x0D315AC4, 0x803F4E8C, 0xF749FD8F);

#define PlaceboVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace McFish
