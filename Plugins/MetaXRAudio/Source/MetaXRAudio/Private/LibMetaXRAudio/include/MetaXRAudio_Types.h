// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

/********************************************************************************/ /**
  \file      MetaXRAudio_Types.h
  \brief     Meta XR Audio SDK shared types header file
  ************************************************************************************/

#ifndef MetaXRAudio_Types_h
#define MetaXRAudio_Types_h

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1) // Make sure all structs are packed for consistency with Unity Integration.

#ifndef MXRA_EXPORT
#ifdef _WIN32
#define MXRA_EXPORT __declspec(dllexport)
#elif defined(__ANDROID__)
#define MXRA_EXPORT __attribute__((visibility("default")))
#elif defined __APPLE__
#define MXRA_EXPORT __attribute__((visibility("default")))
#elif defined __linux__
#define MXRA_EXPORT __attribute__((visibility("default")))
#elif defined(__HEXAGON_ARCH__) || defined(__hexagon__)
#define MXRA_EXPORT __attribute__((visibility("default")))
#else
#error not implemented
#endif
#endif

#ifndef FUNC_NAME
#ifdef _WIN32
#define FUNC_NAME __FUNCTION__
#elif defined(__ANDROID__)
#define FUNC_NAME __func__
#elif defined __APPLE__
#define FUNC_NAME __func__
#elif defined __linux__
#define FUNC_NAME __func__
#elif defined(__HEXAGON_ARCH__) || defined(__hexagon__)
#define FUNC_NAME __func__
#else
#error not implemented
#endif
#endif

//-----------------------------------------------------------------------------------
// ***** OVR_ALIGNAS
//
#if !defined(OVR_ALIGNAS)
#if defined(__GNUC__) || defined(__clang__)
#define OVR_ALIGNAS(n) __attribute__((aligned(n)))
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
#define OVR_ALIGNAS(n) __declspec(align(n))
#elif defined(__CC_ARM)
#define OVR_ALIGNAS(n) __align(n)
#else
#error Need to define OVR_ALIGNAS
#endif
#endif

// Error codes
#if defined(__cplusplus) && (__cplusplus >= 201703)
#define MXRA_NO_DISARD_RESULT_TYPE
#endif

/// Enumerates error codes that can be returned by Audio SDK
#ifdef MXRA_NO_DISARD_RESULT_TYPE
typedef enum [[nodiscard]] mxra_result : int32_t {
#else
typedef enum {
#endif
  MXRA_SUCCESS = 0,
  MXRA_ERROR_UNKNOWN = 2000, ///< An unknown error has occurred.
  MXRA_ERROR_INVALID_PARAM = 2001, ///< An invalid parameter, e.g. NULL pointer or out of range variable, was passed
  MXRA_ERROR_BAD_SAMPLE_RATE = 2002, ///< An unsupported sample rate was declared
  MXRA_ERROR_MISSING_DLL = 2003, ///< The DLL or shared library could not be found
  MXRA_ERROR_BAD_ALIGNMENT = 2004, ///< Buffers did not meet 16b alignment requirements
  MXRA_ERROR_UNINITIALIZED = 2005, ///< audio function called before initialization
  MXRA_ERROR_HRTF_INIT_FAILURE = 2006, ///< HRTF provider initialization failed
  MXRA_ERROR_BAD_VERSION = 2007, ///< Mismatched versions between header and libs
  MXRA_ERROR_SYMBOL_NOT_FOUND = 2008, ///< Couldn't find a symbol in the DLL
  MXRA_ERROR_SHARED_REVERB_DISABLED = 2009, ///< Late reverberation is disabled
  MXRA_ERROR_BAD_ALLOC = 2016,
  MXRA_ERROR_NO_AVAILABLE_AMBISONIC_INSTANCE = 2017, /// < Ran out of ambisonic sources
  MXRA_ERROR_MEMORY_ALLOC_FAILURE = 2018, ///< out of memory (fatal)
  MXRA_ERROR_UNSUPPORTED_FEATURE = 2019, ///< Unsupported feature
  MXRA_ERROR_INVALID_AUDIO_CONTEXT = 2020,
  MXRA_ERROR_BAD_MESH = 2021,
  MXRA_ERROR_INTERNAL_END = 2099, ///< Internal errors used by Audio SDK defined down towards public errors
                                  ///< NOTE: Since we do not define a beginning range for Internal codes, make sure
                                  ///< not to hard-code range checks (since that can vary based on build)
} mxra_result;

/// A 3D vector with float components.
typedef struct OVR_ALIGNAS(4) mxra_vector_3f_ {
  float x, y, z;
} mxra_vector_3f;

/// 3D Pose structure (position + orientation)
typedef struct {
  mxra_vector_3f position;
  mxra_vector_3f forward;
  mxra_vector_3f up;
} mxra_pose;

#define MXRA_REVERB_BAND_COUNT (4)
#define OVRA_REVERB_BAND_COUNT (4) // For backwards compatibility

const int kReverbBandCount = MXRA_REVERB_BAND_COUNT;
const int kReverbShCoefCount = 4;
typedef float mxra_bands[MXRA_REVERB_BAND_COUNT];

typedef void (*MXRA_RAYCAST_CALLBACK)(
    mxra_vector_3f origin,
    mxra_vector_3f direction,
    mxra_vector_3f* hit,
    mxra_vector_3f* normal,
    mxra_bands reflectionBands,
    void* pctx);

#ifndef OVR_CAPI_h
typedef struct ovrPosef_ ovrPosef;
typedef struct ovrPoseStatef_ ovrPoseStatef;
#endif

/// Audio context initialization flags
typedef enum {
  MXRA_INIT_FLAG_DEFAULT = 0x0000,
  MXRA_INIT_FLAG_THREAD_UNSAFE = 0x0010, /// < Skip mutex locks, thread safety becomes caller responsibility
  MXRA_INIT_FLAG_LAZY_ALLOCATIONS = 0x0020, /// < Dynamicly allocate memory on demand rather than preallocating
} mxra_init_flags;

/// Global features that can be turned on or off for the context
/// Global boolean flags
typedef enum {
  MXRA_CONTEXT_FEATURE_NONE = 0, ///< None
  MXRA_CONTEXT_FEATURE_EARLY_REFLECTIONS = 2, ///< Enable/disable early reflections globally. Default: disabled
  MXRA_CONTEXT_FEATURE_LATE_REVERBERATION = 3, ///< Late reverbervation, requires simple room modeling enabled. Default: disabled
  MXRA_CONTEXT_FEATURE_RANDOMIZE_REVERB = 4, ///< Randomize reverbs to diminish artifacts. Default: enabled
  MXRA_CONTEXT_FEATURE_DIFFRACTION = 6, ///< Enable Diffraction. Default: disabled
  MXRA_CONTEXT_FEATURE_SOURCE_PRIORITIZATION = 7, ///< If enable, de-prioritized sources will be rendered via ambisonics. Default: disabled

  MXRA_CONTEXT_FEATURE_COUNT
} mxra_context_feature;

/// Float parameters that can be adjusted for the global context
typedef enum {
  MXRA_CONTEXT_PARAM_UNIT_SCALE = 0,
  MXRA_CONTEXT_PARAM_ACOUSTICS_LEVEL = 1,
  MXRA_CONTEXT_PARAM_HEAD_RADIUS = 2,
  MXRA_CONTEXT_PARAM_PRIORITY_SOURCE_COUNT = 3,

  MXRA_CONTEXT_PARAM_COUNT
} mxra_context_param;

/// Boolean flags that can be toggled for an individual audio source
typedef enum {
  MXRA_SOURCE_ENABLE_NONE = 0x0000,
  MXRA_SOURCE_DISABLE_ACOUSTICS = 0x0100, ///< Enable reflections and reverb for a single AudioSource
  MXRA_SOURCE_ENABLE_DIRECTIVITY = 0x0400, ///< Source directivity enable
  MXRA_SOURCE_ENABLE_AMBI_DIRECT = 0x0800, // Sum direct path into shared ambisonics instead of processing binarual
  MXRA_SOURCE_ENABLE_MEDIUM_ABSORPTION = 0x4000, ///< Frequency specific medium absorption over distance
  MXRA_SOURCE_DISABLE_DIRECT_SOUND = 0x1000, // Disable direct sound and only send sound to reverb/reflections if enabled

  MXRA_SOURCE_FEATURE_COUNT
} mxra_source_feature;

/// Float parameters that can be adjusted for an individual audio source
typedef enum {
  MXRA_SOURCE_PARAM_GAIN = 0,
  MXRA_SOURCE_PARAM_ACOUSTICS_SEND_LEVEL = 4,
  MXRA_SOURCE_PARAM_REFLECTIONS_SEND_LEVEL = 5,
  MXRA_SOURCE_PARAM_VOLUMETRIC_RADIUS = 6,
  MXRA_SOURCE_PARAM_REVERB_REACH = 7,
  MXRA_SOURCE_PARAM_DIRECTIVITY_INTENSITY = 8,
  MXRA_SOURCE_PARAM_HRTF_INTENSITY = 9,
  MXRA_SOURCE_PARAM_OCCLUSION_INTENSITY = 10,

  MXRA_SOURCE_PARAM_COUNT
} mxra_source_param;

/// Audio source attenuation mode
typedef enum {
  MXRA_ATTENUATION_MODE_NONE = 0, ///< Sound is not attenuated, e.g. middleware handles attenuation
  MXRA_ATTENUATION_MODE_FIXED = 1, ///< Sound has fixed attenuation (passed to ovrAudio_SetAudioSourceAttenuationMode)
  MXRA_ATTENUATION_MODE_INVERSE_SQUARE = 2, ///< Sound uses internally calculated attenuation based on inverse square

  MXRA_ATTENUATION_MODE_COUNT

} mxra_attenuation_mode;

/// Explicit override to select reflection and reverb system
typedef enum {
  MXRA_ACOUSTIC_MODEL_AUTOMATIC = -1, ///< Automatically select highest quality (if geometry is set the propagation system will be
                                      ///< active, otherwise fallback to the Room Acoustics)
  MXRA_ACOUSTIC_MODEL_NONE = 0, ///< Disable all acoustics features
  MXRA_ACOUSTIC_MODEL_SHOEBOX = 1, ///< Room controlled by ovrAudioBoxRoomParameters
  MXRA_ACOUSTIC_MODEL_ACOUSTIC_RAY_TRACING = 3, ///< Sound propgated using game geometry
  MXRA_ACOUSTIC_MODEL_COUNT
} mxra_acoustic_model;

/// Status mask returned by spatializer APIs
typedef enum {
  MXRA_SPATIALIZATION_STATUS_NONE = 0x00, ///< Nothing to report
  MXRA_SPATIALIZATION_STATUS_FINISHED = 0x01, ///< Buffer is empty and sound processing is finished
  MXRA_SPATIALIZATION_STATUS_WORKING = 0x02, ///< Data still remains in buffer (e.g. reverberation tail)

} mxra_spatialization_status;

/// Ambisonic formats
typedef enum {
  MXRA_AMBISONIC_FORMAT_FUMA, ///< standard B-Format, channel order = WXYZ (W channel is -3dB)
  MXRA_AMBISONIC_FORMAT_AMBIX ///< ACN/SN3D standard, channel order = WYZX
} mxra_ambisonic_format;

/// Ambisonic rendering modes
typedef enum {
  MXRA_AMBISONIC_RENDER_MODE_SPHERICAL_HARMONICS = -1, ///< (default) Uses a spherical harmonic representation of HRTF
  MXRA_AMBISONIC_RENDER_MODE_MONO = -2 ///< Plays the W (omni) channel through left and right with no spatialization
} mxra_ambisonic_render_mode;

/// Opaque type definitions for audio source and context
typedef struct mxra_context_* mxra_context;
typedef struct mxra_ambisonic_stream_* mxra_ambisonic_stream;
typedef void* mxra_spectrum_analyzer;

/** \brief A function pointer that allocates the specified number of bytes and returns a pointer to the memory. Return null if allocation
 * fails. */
typedef void* (*mxra_allocate_callback)(size_t align, size_t size);
/** \brief A function pointer that deallocates a pointer previously returned from the allocation function. */
typedef void (*mxra_deallocate_callback)(size_t align, void* data);

/// Audio context configuration structure
typedef struct _mxra_context_config {
  uint32_t acc_Size; ///< set to size of the struct
  uint32_t acc_MaxNumSources; ///< maximum number of audio sources to support
  uint32_t acc_SampleRate; ///< sample rate (16000 to 48000, but 44100 and 48000 are recommended for best quality)
  uint32_t acc_BufferLength; ///< number of samples in mono input buffers passed to spatializer
  uint32_t acc_InitFlags; ///< initialization flags
  uint32_t acc_AmbisonicOrderMax; ///< highest supported ambisonic order (1-8)
  uint32_t acc_MaxNumStereoSources; ///< maximum number of stereo source IDs to support
} mxra_context_config;

/// Shoebox parameters used by mxra_shoebox_set_params
typedef struct _mxra_shoebox_params {
  uint32_t size; ///< Size of struct
  int lock_to_listener_position; ///< Whether box is centered on listener
  mxra_bands reflect_left, reflect_right; ///< Reflection bands (0 - 1.0)
  mxra_bands reflect_up, reflect_down; ///< Reflection bands (0 - 1.0)
  mxra_bands reflect_behind, reflect_front; ///< Reflection bands (0 - 1.0)
  mxra_vector_3f dimensions; ///< Size of box in meters
  mxra_vector_3f position; ///< Where the origin of the shoebox is located
  mxra_bands clutter_factor; ///< Clutter factor (0 - 1.0)
} mxra_shoebox_params;

typedef struct _mxra_shoebox_zone_params {
  uint32_t struct_size;
  mxra_vector_3f position;
  float radius;
  float zone_size;
  mxra_bands material;
  float rt60;
  float reverb_level;
  float clutter_factor;
} mxra_shoebox_zone_params;

typedef struct _mxra_shoebox_zone_params* mxra_shoebox_zone_handle;

typedef enum {
  MXRA_MATERIAL_PRESET_ACOUSTIC_TILE = 0,
  MXRA_MATERIAL_PRESET_BRICK,
  MXRA_MATERIAL_PRESET_BRICK_PAINTED,
  MXRA_MATERIAL_PRESET_CARDBOARD,
  MXRA_MATERIAL_PRESET_CARPET,
  MXRA_MATERIAL_PRESET_CARPET_HEAVY,
  MXRA_MATERIAL_PRESET_CARPET_HEAVY_PADDED,
  MXRA_MATERIAL_PRESET_CERAMIC_TILE,
  MXRA_MATERIAL_PRESET_CONCRETE,
  MXRA_MATERIAL_PRESET_CONCRETE_ROUGH,
  MXRA_MATERIAL_PRESET_CONCRETE_BLOCK,
  MXRA_MATERIAL_PRESET_CONCRETE_BLOCK_PAINTED,
  MXRA_MATERIAL_PRESET_CURTAIN,
  MXRA_MATERIAL_PRESET_FOLIAGE,
  MXRA_MATERIAL_PRESET_GLASS,
  MXRA_MATERIAL_PRESET_GLASS_HEAVY,
  MXRA_MATERIAL_PRESET_GRASS,
  MXRA_MATERIAL_PRESET_GRAVEL,
  MXRA_MATERIAL_PRESET_GYPSUM_BOARD,
  MXRA_MATERIAL_PRESET_MARBLE,
  MXRA_MATERIAL_PRESET_MUD,
  MXRA_MATERIAL_PRESET_PLASTER_ON_BRICK,
  MXRA_MATERIAL_PRESET_PLASTER_ON_CONCRETE_BLOCK,
  MXRA_MATERIAL_PRESET_RUBBER,
  MXRA_MATERIAL_PRESET_SOIL,
  MXRA_MATERIAL_PRESET_SOUND_PROOF,
  MXRA_MATERIAL_PRESET_SNOW,
  MXRA_MATERIAL_PRESET_STEEL,
  MXRA_MATERIAL_PRESET_STONE,
  MXRA_MATERIAL_PRESET_VENT,
  MXRA_MATERIAL_PRESET_WATER,
  MXRA_MATERIAL_PRESET_WOOD_THIN,
  MXRA_MATERIAL_PRESET_WOOD_THICK,
  MXRA_MATERIAL_PRESET_WOOD_FLOOR,
  MXRA_MATERIAL_PRESET_WOOD_ON_CONCRETE,
  MXRA_MATERIAL_PRESET_META_DEFAULT,
  MXRA_MATERIAL_PRESET_COUNT
} mxra_material_preset;

/// Get reflection bands for a material preset
inline mxra_result mxra_get_reflection_bands(mxra_material_preset Preset, mxra_bands Bands) {
  if (Preset >= MXRA_MATERIAL_PRESET_COUNT || Bands == NULL) {
    return MXRA_ERROR_INVALID_PARAM;
  }

  switch (Preset) {
    case MXRA_MATERIAL_PRESET_ACOUSTIC_TILE:
      Bands[0] = 0.488168418f;
      Bands[1] = 0.361475229f;
      Bands[2] = 0.339595377f;
      Bands[3] = 0.498946249f;
      break;
    case MXRA_MATERIAL_PRESET_BRICK:
      Bands[0] = 0.975468814f;
      Bands[1] = 0.972064495f;
      Bands[2] = 0.949180186f;
      Bands[3] = 0.930105388f;
      break;
    case MXRA_MATERIAL_PRESET_BRICK_PAINTED:
      Bands[0] = 0.975710571f;
      Bands[1] = 0.983324170f;
      Bands[2] = 0.978116691f;
      Bands[3] = 0.970052719f;
      break;
    case MXRA_MATERIAL_PRESET_CARDBOARD:
      Bands[0] = 0.590000f;
      Bands[1] = 0.435728f;
      Bands[2] = 0.251650f;
      Bands[3] = 0.208000f;
      break;
    case MXRA_MATERIAL_PRESET_CARPET:
      Bands[0] = 0.987633705f;
      Bands[1] = 0.905486643f;
      Bands[2] = 0.583110571f;
      Bands[3] = 0.351053834f;
      break;
    case MXRA_MATERIAL_PRESET_CARPET_HEAVY:
      Bands[0] = 0.977633715f;
      Bands[1] = 0.859082878f;
      Bands[2] = 0.526479602f;
      Bands[3] = 0.370790422f;
      break;
    case MXRA_MATERIAL_PRESET_CARPET_HEAVY_PADDED:
      Bands[0] = 0.910534739f;
      Bands[1] = 0.530433178f;
      Bands[2] = 0.294055820f;
      Bands[3] = 0.270105422f;
      break;
    case MXRA_MATERIAL_PRESET_CERAMIC_TILE:
      Bands[0] = 0.990000010f;
      Bands[1] = 0.990000010f;
      Bands[2] = 0.982753932f;
      Bands[3] = 0.980000019f;
      break;
    case MXRA_MATERIAL_PRESET_CONCRETE:
      Bands[0] = 0.990000010f;
      Bands[1] = 0.983324170f;
      Bands[2] = 0.980000019f;
      Bands[3] = 0.980000019f;
      break;
    case MXRA_MATERIAL_PRESET_CONCRETE_ROUGH:
      Bands[0] = 0.989408433f;
      Bands[1] = 0.964494646f;
      Bands[2] = 0.922127008f;
      Bands[3] = 0.900105357f;
      break;
    case MXRA_MATERIAL_PRESET_CONCRETE_BLOCK:
      Bands[0] = 0.635267377f;
      Bands[1] = 0.652230680f;
      Bands[2] = 0.671053469f;
      Bands[3] = 0.789051592f;
      break;
    case MXRA_MATERIAL_PRESET_CONCRETE_BLOCK_PAINTED:
      Bands[0] = 0.902957916f;
      Bands[1] = 0.940235913f;
      Bands[2] = 0.917584062f;
      Bands[3] = 0.919947326f;
      break;
    case MXRA_MATERIAL_PRESET_CURTAIN:
      Bands[0] = 0.686494231f;
      Bands[1] = 0.545859993f;
      Bands[2] = 0.310078561f;
      Bands[3] = 0.399473131f;
      break;
    case MXRA_MATERIAL_PRESET_FOLIAGE:
      Bands[0] = 0.518259346f;
      Bands[1] = 0.503568292f;
      Bands[2] = 0.578688800f;
      Bands[3] = 0.690210819f;
      break;
    case MXRA_MATERIAL_PRESET_GLASS:
      Bands[0] = 0.655915797f;
      Bands[1] = 0.800631821f;
      Bands[2] = 0.918839693f;
      Bands[3] = 0.923488140f;
      break;
    case MXRA_MATERIAL_PRESET_GLASS_HEAVY:
      Bands[0] = 0.827098966f;
      Bands[1] = 0.950222731f;
      Bands[2] = 0.974604130f;
      Bands[3] = 0.980000019f;
      break;
    case MXRA_MATERIAL_PRESET_GRASS:
      Bands[0] = 0.881126285f;
      Bands[1] = 0.507170796f;
      Bands[2] = 0.131893098f;
      Bands[3] = 0.0103688836f;
      break;
    case MXRA_MATERIAL_PRESET_GRAVEL:
      Bands[0] = 0.729294717f;
      Bands[1] = 0.373122454f;
      Bands[2] = 0.255317450f;
      Bands[3] = 0.200263441f;
      break;
    case MXRA_MATERIAL_PRESET_GYPSUM_BOARD:
      Bands[0] = 0.721240044f;
      Bands[1] = 0.927690148f;
      Bands[2] = 0.934302270f;
      Bands[3] = 0.910105407f;
      break;
    case MXRA_MATERIAL_PRESET_MARBLE:
      Bands[0] = 0.990000f;
      Bands[1] = 0.990000f;
      Bands[2] = 0.982754f;
      Bands[3] = 0.980000f;
      break;
    case MXRA_MATERIAL_PRESET_MUD:
      Bands[0] = 0.844084f;
      Bands[1] = 0.726577f;
      Bands[2] = 0.794683f;
      Bands[3] = 0.849737f;
      break;
    case MXRA_MATERIAL_PRESET_PLASTER_ON_BRICK:
      Bands[0] = 0.975696504f;
      Bands[1] = 0.979106009f;
      Bands[2] = 0.961063504f;
      Bands[3] = 0.950052679f;
      break;
    case MXRA_MATERIAL_PRESET_PLASTER_ON_CONCRETE_BLOCK:
      Bands[0] = 0.881774724f;
      Bands[1] = 0.924773932f;
      Bands[2] = 0.951497555f;
      Bands[3] = 0.959947288f;
      break;
    case MXRA_MATERIAL_PRESET_RUBBER:
      Bands[0] = 0.950000f;
      Bands[1] = 0.916621f;
      Bands[2] = 0.936230f;
      Bands[3] = 0.950000f;
      break;
    case MXRA_MATERIAL_PRESET_SOIL:
      Bands[0] = 0.844084203f;
      Bands[1] = 0.634624243f;
      Bands[2] = 0.416662872f;
      Bands[3] = 0.400000036f;
      break;
    case MXRA_MATERIAL_PRESET_SOUND_PROOF:
      Bands[0] = 0.000000000f;
      Bands[1] = 0.000000000f;
      Bands[2] = 0.000000000f;
      Bands[3] = 0.000000000f;
      break;
    case MXRA_MATERIAL_PRESET_SNOW:
      Bands[0] = 0.532252669f;
      Bands[1] = 0.154535770f;
      Bands[2] = 0.0509644151f;
      Bands[3] = 0.0500000119f;
      break;
    case MXRA_MATERIAL_PRESET_STEEL:
      Bands[0] = 0.793111682f;
      Bands[1] = 0.840140402f;
      Bands[2] = 0.925591767f;
      Bands[3] = 0.979736567f;
      break;
    case MXRA_MATERIAL_PRESET_STONE:
      Bands[0] = 0.980000f;
      Bands[1] = 0.978740f;
      Bands[2] = 0.955701f;
      Bands[3] = 0.950000f;
      break;
    case MXRA_MATERIAL_PRESET_VENT:
      Bands[0] = 0.847042f;
      Bands[1] = 0.620450f;
      Bands[2] = 0.702170f;
      Bands[3] = 0.799473f;
      break;
    case MXRA_MATERIAL_PRESET_WATER:
      Bands[0] = 0.970588267f;
      Bands[1] = 0.971753478f;
      Bands[2] = 0.978309572f;
      Bands[3] = 0.970052719f;
      break;
    case MXRA_MATERIAL_PRESET_WOOD_THIN:
      Bands[0] = 0.592423141f;
      Bands[1] = 0.858273327f;
      Bands[2] = 0.917242289f;
      Bands[3] = 0.939999998f;
      break;
    case MXRA_MATERIAL_PRESET_WOOD_THICK:
      Bands[0] = 0.812957883f;
      Bands[1] = 0.895329595f;
      Bands[2] = 0.941304684f;
      Bands[3] = 0.949947298f;
      break;
    case MXRA_MATERIAL_PRESET_WOOD_FLOOR:
      Bands[0] = 0.852366328f;
      Bands[1] = 0.898992121f;
      Bands[2] = 0.934784114f;
      Bands[3] = 0.930052698f;
      break;
    case MXRA_MATERIAL_PRESET_WOOD_ON_CONCRETE:
      Bands[0] = 0.959999979f;
      Bands[1] = 0.941232264f;
      Bands[2] = 0.937923789f;
      Bands[3] = 0.930052698f;
      break;
    case MXRA_MATERIAL_PRESET_META_DEFAULT:
      Bands[0] = 0.9f;
      Bands[1] = 0.9f;
      Bands[2] = 0.9f;
      Bands[3] = 0.9f;
      break;
    case MXRA_MATERIAL_PRESET_COUNT:
    default:
      Bands[0] = 0.000000000f;
      Bands[1] = 0.000000000f;
      Bands[2] = 0.000000000f;
      Bands[3] = 0.000000000f;
      return MXRA_ERROR_INVALID_PARAM;
  };

  return MXRA_SUCCESS;
}

/***********************************************************************************/
/* Acoustic Ray Tracing Types */

/** \brief A handle to a material that applies filtering to reflected and transmitted sound. 0/NULL/nullptr represent an invalid handle. */
typedef struct ovrAudioMaterial_* mxra_material;

/** \brief A handle to geometry that sound interacts with. 0/NULL/nullptr represent an invalid handle. */
typedef struct ovrAudioGeometry_* mxra_geometry;

/** \brief A handle to an Acoustic Map. 0/NULL/nullptr represent an invalid handle.  */
typedef struct ovrAudioSceneIR_* mxra_acoustic_map;

/** \brief A handle to a zone that overrides or modifies the Acoustic Map within. 0/NULL/nullptr represent an invalid handle.  */
typedef struct ovrAudioControlZone_* mxra_control_zone;

/** \brief An enumeration of the scalar types supported for geometry data. */
typedef enum {
  MXRA_SCALAR_TYPE_INT8,
  MXRA_SCALAR_TYPE_UINT8,
  MXRA_SCALAR_TYPE_INT16,
  MXRA_SCALAR_TYPE_UINT16,
  MXRA_SCALAR_TYPE_INT32,
  MXRA_SCALAR_TYPE_UINT32,
  MXRA_SCALAR_TYPE_INT64,
  MXRA_SCALAR_TYPE_UINT64,
  MXRA_SCALAR_TYPE_FLOAT16,
  MXRA_SCALAR_TYPE_FLOAT32,
  MXRA_SCALAR_TYPE_FLOAT64,
} mxra_scalar_type;

/** \brief The type of mesh face that is used to define geometry.
 *
 * For all face types, the vertices should be provided such that they are in counter-clockwise
 * order when the face is viewed from the front. The vertex order is used to determine the
 * surface normal orientation.
 */
typedef enum {
  /** \brief A face type that is defined by 3 vertex indices. */
  MXRA_FACE_TYPE_TRIANGLES = 0,
  /** \brief A face type that is defined by 4 vertex indices. The vertices are assumed to be coplanar. */
  MXRA_FACE_TYPE_QUADS = 1,
  MXRA_FACE_TYPE_COUNT
} mxra_face_type;

/** \brief The properties for audio materials. All properties are frequency dependent. */
typedef enum {
  /** \brief The fraction of sound arriving at a surface that is absorbed by the material.
   *
   * This value is in the range 0 to 1, where 0 indicates a perfectly reflective material, and
   * 1 indicates a perfectly absorptive material. Absorption is inversely related to the reverberation time,
   * and has the strongest impact on the acoustics of an environment. The default absorption is 0.1.
   */
  MXRA_MATERIAL_PROPERTY_ABSORPTION = 0,
  /** \brief The fraction of sound arriving at a surface that is transmitted through the material.
   *
   * This value is in the range 0 to 1, where 0 indicates a material that is acoustically opaque,
   * and 1 indicates a material that is acoustically transparent.
   * To preserve energy in the simulation, the following condition must hold: (1 - absorption + transmission) <= 1
   * If this condition is not met, the transmission and absorption coefficients will be modified to
   * enforce energy conservation. The default transmission is 0.
   */
  MXRA_MATERIAL_PROPERTY_TRANSMISSION = 1,
  /** \brief The fraction of sound arriving at a surface that is scattered.
   *
   * This property in the range 0 to 1 controls how diffuse the reflections are from a surface,
   * where 0 indicates a perfectly specular reflection and 1 indicates a perfectly diffuse reflection.
   * The default scattering is 0.5.
   */
  MXRA_MATERIAL_PROPERTY_SCATTERING = 2,
  MXRA_MATERIAL_PROPERTY_COUNT
} mxra_material_property;

/** \brief A struct that is used to provide the vertex data for a mesh. */
typedef struct {
  /** \brief A pointer to a buffer of vertex data with the format described in this structure. This cannot be null. */
  const void* vertices;
  /** \brief The offset in bytes of the 0th vertex within the buffer. */
  size_t byteOffset;
  /** \brief The number of vertices that are contained in the buffer. */
  size_t vertexCount;
  /** \brief If non-zero, the stride in bytes between consecutive vertices. */
  size_t vertexStride;
  /** \brief The primitive type of vertex coordinates. Each vertex is defined by 3 consecutive values of this type. */
  mxra_scalar_type vertexType;
} mxra_mesh_vertices;

/** \brief A struct that is used to provide the index data for a mesh. */
typedef struct {
  /** \brief A pointer to a buffer of index data with the format described in this structure. This cannot be null. */
  const void* indices;
  /** \brief The offset in bytes of the 0th index within the buffer. */
  size_t byteOffset;
  /** \brief The total number of indices that are contained in the buffer. */
  size_t indexCount;
  /** \brief The primitive type of the indices in the buffer. This must be an integer type. */
  mxra_scalar_type indexType;
} mxra_mesh_indices;

/** \brief A struct that defines a grouping of mesh faces and the material that should be applied to the faces. */
typedef struct {
  /** \brief The offset in the index buffer of the first index in the group. */
  size_t indexOffset;
  /** \brief The number of faces that this group uses from the index buffer.
   *
   * The number of bytes read from the index buffer for the group is determined by the formula:
   * (faceCount)*(verticesPerFace)*(bytesPerIndex)
   */
  size_t faceCount;
  /** \brief The type of face that the group uses. This determines how many indices are needed to define a face. */
  mxra_face_type faceType;
  /** \brief A handle to the material that should be assigned to the group. If equal to 0/NULL/nullptr, a default material is used instead.
   */
  mxra_material material;
} mxra_mesh_group;

/** \brief A struct that completely defines an audio mesh. */
typedef struct {
  /** \brief The vertices that the mesh uses. */
  mxra_mesh_vertices vertices;
  /** \brief The indices that the mesh uses. */
  mxra_mesh_indices indices;
  /** \brief A pointer to an array of mxra_mesh_group that define the material groups in the mesh.
   *
   * The size of the array must be at least groupCount. This cannot be null.
   */
  const mxra_mesh_group* groups;
  /** \brief The number of groups that are part of the mesh. */
  size_t groupCount;
} mxra_mesh;

/** \brief The boolean flags for an Acoustic Geometry. */
typedef enum {
  /** \brief If set, the geometry is used within the simulation and impacts the computed acoustics. */
  MXRA_GEOMETRY_FLAG_ENABLED = (1 << 0),
  /** \brief If set, the geometry is assumed to never move or change geometry. The context may use this flag as a hint to optimize the
   simulation. */
  MXRA_GEOMETRY_FLAG_STATIC = (1 << 1),
} mxra_geometry_flags;

/** \brief Flags describing the status an audio scene IR. */
typedef enum {
  /** \brief A status flag indicating the IR has no data (i.e. was just created). */
  MXRA_ACOUSTIC_MAP_STATUS_EMPTY = 0,
  /** \brief A status flag indicating the scene has been spatially mapped (but IR not necessarily computed). */
  MXRA_ACOUSTIC_MAP_STATUS_MAPPED = (1 << 0),
  /** \brief A status flag indicating the IR is ready for use in a runtime simulation (i.e. has been mapped and computed). */
  MXRA_ACOUSTIC_MAP_STATUS_READY = (1 << 1) | MXRA_ACOUSTIC_MAP_STATUS_MAPPED,
} mxra_acoustic_map_status;

/** \brief The boolean flags for an audio scene IR. */
typedef enum {
  /** \brief The flag value when no flags are set. */
  MXRA_ACOUSTIC_MAP_FLAGS_NONE = 0,
  /** \brief If set, only objects that have the MXRA_GEOMETRY_FLAG_STATIC flag set will be considered for the computation. */
  MXRA_ACOUSTIC_MAP_FLAG_STATIC_ONLY = (1 << 0),
  /** \brief If set, no IRs will be calculated for points that are floating far above the floor (as determined by gravity vector). */
  MXRA_ACOUSTIC_MAP_FLAG_NO_FLOATING = (1 << 1),
  /** \brief If set, no IRs will be calculated. The scene will be mapped but not simulated. */
  MXRA_ACOUSTIC_MAP_FLAG_MAP_ONLY = (1 << 2),
  /** \brief If set, the scene will be preprocessed to support runtime diffraction. */
  MXRA_ACOUSTIC_MAP_FLAG_DIFFRACTION = (1 << 3),
} mxra_acoustic_map_flags;

/** \brief A function pointer that provides information about the current progress on a long-running operation.
 *
 * This function will be called periodically by long-running operations to report progress to the GUI.
 * The progress value is in the range [0,1] and indicates the approximate fraction of the operation
 * that has been performed so far, and could be used to display a progress bar.
 * The string is a NULL-terminated ASCII description of the current task.
 * The return value indicates whether or not to continue processing (non-zero -> continue, zero -> cancel).
 */
typedef uint32_t (*mxra_progress_callback)(void* userData, const char* string, float progress);

/** \brief A struct containing callback functions used when computing a scene IR. */
typedef struct {
  /** \brief A pointer to arbitrary user data that is passed into the callback functions. */
  void* userData;
  /** \brief A pointer to function that reports the computation progress to a GUI. */
  mxra_progress_callback progress;
} mxra_acoustic_map_callbacks;

/** \brief A struct that describes how an Acoustic Map is computed. */
typedef struct {
  /** \brief A value that should be set to the size in bytes of the mxra_acoustic_map_parameters structure.
   * This is used for backward/forward compatibility.
   */
  size_t thisSize; /* = sizeof(mxra_acoustic_map_parameters) */
  /** \brief A struct containing callback functions that receive notifications during computation. */
  mxra_acoustic_map_callbacks callbacks;
  /** \brief The number of threads that should be used for doing the computation.
   * A value of 0 means to use the same number of threads as CPUs.
   * A value of 1 indicates that all work is done on the calling thread (no threads created).
   * This number will be clamped to no more than the number of CPUs.
   */
  size_t threadCount; /* = 0 */
  /** \brief The number of early reflections that should be stored in the Acoustic Map.
   * Increasing this value increases the size of the Acoustic Map data, as well as the quality.
   */
  size_t reflectionCount; /* = 6 */
  /** \brief Flags that describe how an Acoustic Map should be computed. */
  mxra_acoustic_map_flags flags; /* = mxra_acoustic_map_flags_NoFloating */
  /** \brief The minimum point placement resolution, expressed in meters.
   * This determines the smallest spacing of points in the scene, as well as
   * the smallest space that will be considered as part of the precomputation.
   * This should be a little bit smaller than the smallest possible space
   * that the listener can traverse.
   * Note that decreasing this value doesn't necessarily result in more densely-sampled points -
   * the number of points is more clostly related to the number of distinct acoustic spaces
   * in the scene.
   */
  float minResolution; /* = 1.0f */
  /** \brief The maximum point placement resolution, expressed in meters.
   * This determines the largest spacing of points in the scene.
   * Decreasing this value improves the quality for large open scenes,
   * but also increases the precomputation time and storage required.
   */
  float maxResolution; /* = 10.0f */
  /** \brief The typical height in meters of the listener's head above floor surfaces.
   * This is used to determine where to vertically place probe points in the scene.
   * The quality will be best for sources and listeners that are around this height.
   */
  float headHeight; /* = 1.5f */
  /** \brief The maximum height in meters of a probe point above floor surfaces.
   * Increase this value to include more points floating in the air.
   */
  float maxHeight; /* = 3.0f */
  /** \brief A 3D unit vector indicating the downward direction in the scene.
   * This is used to cull probe points that are irrelevant because they are too high
   * above the floor surface.
   * In a Y-up world, this should be {0,-1,0}, while Z-up would be {0,0,-1}.
   */
  float gravityVector[3]; /* = { 0, -1, 0 } */

} mxra_acoustic_map_parameters;

/** \brief A function pointer that reads bytes from an arbitrary source and places them into the output byte array.
 *
 * The function should return the number of bytes that were successfully read, or 0 if there was an error.
 */
typedef size_t (*mxra_serializer_read_callback)(void* userData, void* bytes, size_t byteCount);
/** \brief A function pointer that writes bytes to an arbitrary destination.
 *
 * The function should return the number of bytes that were successfully written, or 0 if there was an error.
 */
typedef size_t (*mxra_serializer_write_callback)(void* userData, const void* bytes, size_t byteCount);
/** \brief A function pointer that seeks within the data stream.
 *
 * The function should seek by the specified signed offset relative to the current stream position.
 * The function should return the actual change in stream position. Return 0 if there is an error or seeking is not supported.
 */
typedef int64_t (*mxra_serializer_seek_callback)(void* userData, int64_t seekOffset);

/** \brief A structure that contains function pointers to reading/writing data to an arbitrary source/sink. */
typedef struct {
  /** \brief A function pointer that reads bytes from an arbitrary source. This pointer may be null if only writing is required. */
  mxra_serializer_read_callback read;
  /** \brief A function pointer that writes bytes to an arbitrary destination. This pointer may be null if only reading is required. */
  mxra_serializer_write_callback write;
  /** \brief A function pointer that seeks within the data stream. This pointer may be null if seeking is not supported. */
  mxra_serializer_seek_callback seek;
  /** \brief A pointer to user-defined data that will be passed in as the first argument to the serialization functions. */
  void* userData;
} mxra_serializer;

/** \brief The properties of an audio control Zone. */
typedef enum {
  /** \brief A frequency-dependent property describing the reverberation time adjustment in the Zone.
   *
   * The value represents a signed additive adjustment to the simulated reverb time (units: seconds).
   */
  MXRA_CONTROL_ZONE_PROPERTY_RT60,
  /** \brief A frequency-dependent property describing the reverberation level adjustment in the Zone.
   *
   * The value represents a signed additive adjustment to the simulated reverb level (units: decibels).
   */
  MXRA_CONTROL_ZONE_PROPERTY_REVERB_LEVEL,
  /** \brief A frequency-dependent property describing the early reflection level adjustment in the Zone.
   *
   * The value represents a signed additive adjustment to the simulated early reflection level (units: decibels).
   */
  MXRA_CONTROL_ZONE_PROPERTY_REFLECTIONS_LEVEL,
  /** \brief A scalar (broadband) property describing the early reflections time adjustment in the Zone.
   *
   * The value represents a unitless linear scale factor which is multiplied with the simulated reflection delays.
   */
  MXRA_CONTROL_ZONE_PROPERTY_REFLECTIONS_TIME,
  MXRA_CONTROL_ZONE_PROPERTY_COUNT
} mxra_control_zone_property;

/** \brief Flags to describe how to render a mesh */
typedef enum {
  MXRA_MESH_FLAGS_NONE = 0,
  /** \brief Turning on Mesh Simplification will reduce the resource usage of geometry propagation at the cost of audio quality. */
  MXRA_MESH_FLAGS_ENABLE_MESH_SIMPLIFICATION = (1 << 0),
  /** \brief If diffraction is enabled, the geometry will support real-time diffraction. Note, if this is disabled and you try
   * to turn on real time diffraction, you won't hear a difference as the geometry did not render to support geometry. */
  MXRA_MESH_FLAGS_ENABLE_DIFFRACTION = (1 << 1),
} mxra_mesh_flags;

/** \brief A struct that describes how a mesh should be simplified. */
typedef struct {
  /** The size of this structure. You must set this equal to sizeof(mxra_mesh_simplification) This will ensure version compatibility */
  size_t thisSize;
  mxra_mesh_flags flags;
  /** \brief The local unit scale factor for the mesh (the factor that converts from mesh-local coordinates to coordinates in meters).
   * The other length quantities in this struct are converted to mesh-local coordinates using this value. */
  float unitScale; /* = 1.0f */
  /** \brief The maximum allowed error due to simplification, expressed as a distance in meters. */
  float maxError; /* = 0.1f */
  /** \brief The minimum angle (degrees) that there must be between two adjacent face normals for their edge to be marked as diffracting. */
  float minDiffractionEdgeAngle; /* = 1.0f */
  /** \brief The minimum length in meters that an edge should have for it to be marked as diffracting. */
  float minDiffractionEdgeLength; /* = 0.01f */
  /** \brief The maximum distance in meters that a diffraction flag extends out from the edge. */
  float flagLength; /* = 1.0f */
  /** \brief The number of threads that should be used for processing the mesh.
   * A value of 0 means to use the same number of threads as CPUs.
   * A value of 1 indicates that all work is done on the calling thread (no threads created).
   * This number will be clamped to no more than the number of CPUs.
   */
  size_t threadCount; /* = 0 */
} mxra_mesh_simplification;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // MetaXRAudioTypes_h
