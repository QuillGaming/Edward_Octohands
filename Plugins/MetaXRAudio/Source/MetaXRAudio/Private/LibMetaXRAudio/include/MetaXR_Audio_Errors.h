// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

/********************************************************************************/ /**
 \file      MetaXR_Audio_Errors.h
 \brief     OVR Audio SDK public header file containing return codes
 ************************************************************************************/

#ifndef OVR_Audio_Errors_h
#define OVR_Audio_Errors_h

#include <stdint.h>

#include "MetaXRAudio_Types.h"

/// Result type used by the Audio SDK
#ifdef OVR_RESULT_DEFINED
#error "duplicate ovrResult definition"
#else
#define OVR_RESULT_DEFINED
typedef mxra_result ovrResult;

// Error code constants for backward compatibility
#define ovrSuccess MXRA_SUCCESS
#define ovrError_AudioUnknown MXRA_ERROR_UNKNOWN
#define ovrError_AudioInvalidParam MXRA_ERROR_INVALID_PARAM
#define ovrError_AudioBadSampleRate MXRA_ERROR_BAD_SAMPLE_RATE
#define ovrError_AudioMissingDLL MXRA_ERROR_MISSING_DLL
#define ovrError_AudioBadAlignment MXRA_ERROR_BAD_ALIGNMENT
#define ovrError_AudioUninitialized MXRA_ERROR_UNINITIALIZED
#define ovrError_AudioHRTFInitFailure MXRA_ERROR_HRTF_INIT_FAILURE
#define ovrError_AudioBadVersion MXRA_ERROR_BAD_VERSION
#define ovrError_AudioSymbolNotFound MXRA_ERROR_SYMBOL_NOT_FOUND
#define ovrError_SharedReverbDisabled MXRA_ERROR_SHARED_REVERB_DISABLED
#define ovrError_AudioBadAlloc MXRA_ERROR_BAD_ALLOC
#define ovrError_AudioNoAvailableAmbisonicInstance MXRA_ERROR_NO_AVAILABLE_AMBISONIC_INSTANCE
#define ovrError_AudioMemoryAllocFailure MXRA_ERROR_MEMORY_ALLOC_FAILURE
#define ovrError_AudioUnsupportedFeature MXRA_ERROR_UNSUPPORTED_FEATURE
#define ovrError_AudioInvalidAudioContext MXRA_ERROR_INVALID_AUDIO_CONTEXT
#define ovrError_AudioBadMesh MXRA_ERROR_BAD_MESH
#endif

#ifndef OVRA_EXPORT
#define OVRA_EXPORT MXRA_EXPORT
#endif

#endif // OVR_Audio_Errors_h
