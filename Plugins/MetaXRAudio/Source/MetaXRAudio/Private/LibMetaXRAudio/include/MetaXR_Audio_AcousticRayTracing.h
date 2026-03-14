// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

/********************************************************************************/ /**
 \file      MetaXR_Audio_AcousticRayTracing.h
 \brief     OVR Audio SDK public header file - Backward compatibility wrapper
 ************************************************************************************/

#ifndef OVR_Audio_AcousticRayTracing_h
#define OVR_Audio_AcousticRayTracing_h

#include <stddef.h>
#include <stdint.h>

#include "MetaXRAudio_Types.h"
#include "MetaXR_Audio_Errors.h"

#ifndef OVR_CONTEXT_DEFINED
#define OVR_CONTEXT_DEFINED
typedef struct mxra_context_ ovrAudioContext_;
typedef ovrAudioContext_* ovrAudioContext;
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Type mappings for backward compatibility
typedef mxra_material ovrAudioMaterial;
typedef mxra_scalar_type ovrAudioScalarType;
typedef mxra_face_type ovrAudioFaceType;
typedef mxra_material_property ovrAudioMaterialProperty;
typedef mxra_mesh_vertices ovrAudioMeshVertices;
typedef mxra_mesh_indices ovrAudioMeshIndices;
typedef mxra_mesh_group ovrAudioMeshGroup;
typedef mxra_mesh ovrAudioMesh;
typedef mxra_geometry_flags ovrAudioObjectFlags;
typedef mxra_geometry ovrAudioGeometry;
typedef mxra_acoustic_map ovrAudioSceneIR;
typedef mxra_acoustic_map_status ovrAudioSceneIRStatus;
typedef mxra_acoustic_map_flags ovrAudioSceneIRFlags;
typedef mxra_progress_callback ovrAudioProgressCallback;
typedef mxra_acoustic_map_callbacks ovrAudioSceneIRCallbacks;
typedef mxra_acoustic_map_parameters ovrAudioSceneIRParameters;
typedef mxra_serializer_read_callback ovrAudioSerializerReadCallback;
typedef mxra_serializer_write_callback ovrAudioSerializerWriteCallback;
typedef mxra_serializer_seek_callback ovrAudioSerializerSeekCallback;
typedef mxra_serializer ovrAudioSerializer;
typedef mxra_control_zone ovrAudioControlZone;
typedef mxra_control_zone_property ovrAudioControlZoneProperty;
typedef mxra_mesh_flags ovrAudioMeshFlags;
typedef mxra_mesh_simplification ovrAudioMeshSimplification;

// Enum value mappings for ovrAudioScalarType
#define ovrAudioScalarType_Int8 MXRA_SCALAR_TYPE_INT8
#define ovrAudioScalarType_UInt8 MXRA_SCALAR_TYPE_UINT8
#define ovrAudioScalarType_Int16 MXRA_SCALAR_TYPE_INT16
#define ovrAudioScalarType_UInt16 MXRA_SCALAR_TYPE_UINT16
#define ovrAudioScalarType_Int32 MXRA_SCALAR_TYPE_INT32
#define ovrAudioScalarType_UInt32 MXRA_SCALAR_TYPE_UINT32
#define ovrAudioScalarType_Int64 MXRA_SCALAR_TYPE_INT64
#define ovrAudioScalarType_UInt64 MXRA_SCALAR_TYPE_UINT64
#define ovrAudioScalarType_Float16 MXRA_SCALAR_TYPE_FLOAT16
#define ovrAudioScalarType_Float32 MXRA_SCALAR_TYPE_FLOAT32
#define ovrAudioScalarType_Float64 MXRA_SCALAR_TYPE_FLOAT64

// Enum value mappings for ovrAudioFaceType
#define ovrAudioFaceType_Triangles MXRA_FACE_TYPE_TRIANGLES
#define ovrAudioFaceType_Quads MXRA_FACE_TYPE_QUADS
#define ovrAudioFaceType_COUNT MXRA_FACE_TYPE_COUNT

// Enum value mappings for ovrAudioMaterialProperty
#define ovrAudioMaterialProperty_Absorption MXRA_MATERIAL_PROPERTY_ABSORPTION
#define ovrAudioMaterialProperty_Transmission MXRA_MATERIAL_PROPERTY_TRANSMISSION
#define ovrAudioMaterialProperty_Scattering MXRA_MATERIAL_PROPERTY_SCATTERING
#define ovrAudioMaterialProperty_COUNT MXRA_MATERIAL_PROPERTY_COUNT

// Enum value mappings for ovrAudioObjectFlags (maps to mxra_geometry_flags)
#define ovrAudioObjectFlag_Enabled MXRA_GEOMETRY_FLAG_ENABLED
#define ovrAudioObjectFlag_Static MXRA_GEOMETRY_FLAG_STATIC
#define ovrAudioObjectFlag_Small MXRA_GEOMETRY_FLAG_SMALL

// Enum value mappings for ovrAudioSceneIRStatus (maps to mxra_acoustic_map_status)
#define ovrAudioSceneIRStatus_Empty MXRA_ACOUSTIC_MAP_STATUS_EMPTY
#define ovrAudioSceneIRStatus_Mapped MXRA_ACOUSTIC_MAP_STATUS_MAPPED
#define ovrAudioSceneIRStatus_Ready MXRA_ACOUSTIC_MAP_STATUS_READY

// Enum value mappings for ovrAudioSceneIRFlags (maps to mxra_acoustic_map_flags)
#define ovrAudioSceneIRFlags_None MXRA_ACOUSTIC_MAP_FLAGS_NONE
#define ovrAudioSceneIRFlag_StaticOnly MXRA_ACOUSTIC_MAP_FLAG_STATIC_ONLY
#define ovrAudioSceneIRFlag_NoFloating MXRA_ACOUSTIC_MAP_FLAG_NO_FLOATING
#define ovrAudioSceneIRFlag_MapOnly MXRA_ACOUSTIC_MAP_FLAG_MAP_ONLY
#define ovrAudioSceneIRFlag_Diffraction MXRA_ACOUSTIC_MAP_FLAG_DIFFRACTION

// Enum value mappings for ovrAudioControlZoneProperty
#define ovrAudioControlZoneProperty_RT60 MXRA_CONTROL_ZONE_PROPERTY_RT60
#define ovrAudioControlZoneProperty_ReverbLevel MXRA_CONTROL_ZONE_PROPERTY_REVERB_LEVEL
#define ovrAudioControlZoneProperty_ReflectionsLevel MXRA_CONTROL_ZONE_PROPERTY_REFLECTIONS_LEVEL
#define ovrAudioControlZoneProperty_ReflectionsTime MXRA_CONTROL_ZONE_PROPERTY_REFLECTIONS_TIME
#define ovrAudioControlZoneProperty_COUNT MXRA_CONTROL_ZONE_PROPERTY_COUNT

// Enum value mappings for ovrAudioMeshFlags
#define ovrAudioMeshFlags_None MXRA_MESH_FLAGS_NONE
#define ovrAudioMeshFlags_enableMeshSimplification MXRA_MESH_FLAGS_ENABLE_MESH_SIMPLIFICATION
#define ovrAudioMeshFlags_enableDiffraction MXRA_MESH_FLAGS_ENABLE_DIFFRACTION

// Backward compatible function mappings

OVRA_EXPORT ovrResult ovrAudio_SetPropagationQuality(ovrAudioContext context, float quality);
OVRA_EXPORT ovrResult ovrAudio_SetPropagationThreadAffinity(ovrAudioContext context, uint64_t cpuMask);

OVRA_EXPORT ovrResult ovrAudio_CreateAudioGeometry(ovrAudioContext context, ovrAudioGeometry* geometry);
OVRA_EXPORT ovrResult ovrAudio_DestroyAudioGeometry(ovrAudioGeometry geometry);
OVRA_EXPORT ovrResult ovrAudio_AudioGeometrySetObjectFlag(ovrAudioGeometry geometry, ovrAudioObjectFlags flag, int32_t enabled);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryUploadMesh(
    ovrAudioGeometry geometry,
    const ovrAudioMesh* mesh /*, const ovrAudioMeshSimplificationParameters* simplification*/);
OVRA_EXPORT ovrResult ovrAudio_AudioGeometryUploadMeshArrays(
    ovrAudioGeometry geometry,
    const void* vertices,
    size_t verticesByteOffset,
    size_t vertexCount,
    size_t vertexStride,
    ovrAudioScalarType vertexType,
    const void* indices,
    size_t indicesByteOffset,
    size_t indexCount,
    ovrAudioScalarType indexType,
    const ovrAudioMeshGroup* groups,
    size_t groupCount /*, const ovrAudioMeshSimplificationParameters* simplification*/);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometrySetTransform(ovrAudioGeometry geometry, const float matrix4x4[16]);
OVRA_EXPORT ovrResult ovrAudio_AudioGeometryGetTransform(const ovrAudioGeometry geometry, float matrix4x4[16]);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryWriteMeshFile(const ovrAudioGeometry geometry, const char* filePath);
OVRA_EXPORT ovrResult ovrAudio_AudioGeometryReadMeshFile(ovrAudioGeometry geometry, const char* filePath);
OVRA_EXPORT ovrResult ovrAudio_AudioGeometryReadMeshMemory(ovrAudioGeometry geometry, const int8_t* data, uint64_t dataLength);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryWriteMeshFileObj(const ovrAudioGeometry geometry, const char* filePath);
/** \brief If the geometry is a mesh, copy the mesh vertices/indices into the output pointers.
 *
 * This function should be used by first calling it with vertices/indices == nullptr, and with
 * valid locations for numVertices/numTriangles. The function will write the size of the required
 * arrays to numVertices/numTriangles. Then, after allocating storage (3*numVertices*sizeof(float) + 3*numTriangles*sizeof(uint32_t)),
 * call the function again, passing in the pointers to the mesh storage, as well as the size of the
 * storage arrays. The function will copy the mesh data to the arrays.
 */
OVRA_EXPORT ovrResult ovrAudio_AudioGeometryGetSimplifiedMesh(
    const ovrAudioGeometry geometry,
    float* vertices,
    uint32_t* numVertices,
    uint32_t* indices,
    uint32_t* numTriangles);

/** \brief This function is the same as ovrAudio_AudioGeometryGetSimplifiedMesh, but it also returns the material indices for each triangle.
 * materialIndices is an array of length numTriangles, and is populated with the material indices for each triangle.
 * Go to ovrAudio_AudioGeometryGetSimplifiedMesh for more details:
 * \see ovrAudio_AudioGeometryGetSimplifiedMesh
 */
OVRA_EXPORT ovrResult ovrAudio_AudioGeometryGetSimplifiedMeshWithMaterials(
    const ovrAudioGeometry geometry,
    float* vertices,
    uint32_t* numVertices,
    uint32_t* indices,
    uint32_t* materialIndices,
    uint32_t* numTriangles);

OVRA_EXPORT ovrResult ovrAudio_CreateAudioMaterial(ovrAudioContext context, ovrAudioMaterial* material);
OVRA_EXPORT ovrResult ovrAudio_DestroyAudioMaterial(ovrAudioMaterial material);

OVRA_EXPORT ovrResult
ovrAudio_AudioMaterialSetFrequency(ovrAudioMaterial material, ovrAudioMaterialProperty property, float frequency, float value);
OVRA_EXPORT ovrResult
ovrAudio_AudioMaterialGetFrequency(const ovrAudioMaterial material, ovrAudioMaterialProperty property, float frequency, float* value);
OVRA_EXPORT ovrResult ovrAudio_AudioMaterialReset(ovrAudioMaterial material, ovrAudioMaterialProperty property);

OVRA_EXPORT ovrResult ovrAudio_CreateAudioSceneIR(ovrAudioContext context, ovrAudioSceneIR* sceneIR);
OVRA_EXPORT ovrResult ovrAudio_DestroyAudioSceneIR(ovrAudioSceneIR sceneIR);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRSetEnabled(ovrAudioSceneIR sceneIR, int enabled);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRGetEnabled(ovrAudioSceneIR sceneIR, int* enabled);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRGetStatus(ovrAudioSceneIR sceneIR, ovrAudioSceneIRStatus* status);
OVRA_EXPORT ovrResult ovrAudio_InitializeAudioSceneIRParameters(ovrAudioSceneIRParameters* parameters);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRCompute(ovrAudioSceneIR sceneIR, ovrAudioSceneIRParameters* parameters);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRComputeCustomPoints(
    ovrAudioSceneIR sceneIR,
    const float* points,
    size_t pointCount,
    ovrAudioSceneIRParameters* parameters);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRGetPointCount(ovrAudioSceneIR sceneIR, size_t* pointCount);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRGetPoints(ovrAudioSceneIR sceneIR, float* points, size_t maxPointCount);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRSetTransform(ovrAudioSceneIR sceneIR, const float matrix4x4[16]);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRGetTransform(const ovrAudioSceneIR sceneIR, float matrix4x4[16]);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRWriteFile(ovrAudioSceneIR sceneIR, const char* filePath);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRReadFile(ovrAudioSceneIR sceneIR, const char* filePath);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRReadMemory(ovrAudioSceneIR sceneIR, const int8_t* data, uint64_t dataLength);
OVRA_EXPORT ovrResult ovrAudio_AudioSceneIRWriteMeshFileObj(const ovrAudioSceneIR sceneIR, const char* filePath);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryWriteMeshData(const ovrAudioGeometry geometry, const ovrAudioSerializer* serializer);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryReadMeshData(ovrAudioGeometry geometry, const ovrAudioSerializer* serializer);

/** \brief Create a new audio control Zone handle with the default initial state. */
OVRA_EXPORT ovrResult ovrAudio_CreateControlZone(ovrAudioContext context, ovrAudioControlZone* control);

/** \brief Destroy an audio control Zone handle. The control Zone must not be referenced by a scene when it is destroyed. */
OVRA_EXPORT ovrResult ovrAudio_DestroyControlZone(ovrAudioControlZone control);

/** \brief Set whether or not the control Zone is enabled. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneSetEnabled(ovrAudioControlZone control, int enabled);

/** \brief Get whether or not the control Zone is enabled. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneGetEnabled(const ovrAudioControlZone control, int* enabled);

/** \brief Set a 4x4 column-major matrix encoding the homogeneous coordinate transformation from control Zone-local-space to world space.
 */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneSetTransform(ovrAudioControlZone control, const float matrix4x4[16]);
/** \brief Get a 4x4 column-major matrix encoding the homogeneous coordinate transformation from control Zone-local-space to world space.
 */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneGetTransform(const ovrAudioControlZone control, float matrix4x4[16]);

/** \brief Set the local size of the control Zone box along each axis. The box is centered at the local origin. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneSetBox(ovrAudioControlZone control, float sizeX, float sizeY, float sizeZ);

/** \brief Get the local size of the control Zone box along each axis. The box is centered at the local origin. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneGetBox(const ovrAudioControlZone control, float* sizeX, float* sizeY, float* sizeZ);

/** \brief Set the distance margin that is used to fade out the Zone's influence near its boundaries. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneSetFadeDistance(ovrAudioControlZone control, float fadeX, float fadeY, float fadeZ);

/** \brief Get the distance margin that is used to fade out the Zone's influence near its boundaries. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneGetFadeDistance(const ovrAudioControlZone control, float* fadeX, float* fadeY, float* fadeZ);

/** \brief Set the value of a frequency-dependent control Zone property at a specific frequency. If there is a previous value at that
 * frequency it is replaced. */
OVRA_EXPORT ovrResult
ovrAudio_ControlZoneSetFrequency(ovrAudioControlZone control, ovrAudioControlZoneProperty property, float frequency, float value);

/** \brief Remove all frequency data points from the specified control Zone property. */
OVRA_EXPORT ovrResult ovrAudio_ControlZoneReset(ovrAudioControlZone control, ovrAudioControlZoneProperty property);

/** \brief Set the value of a frequency-dependent Room control property at a specific frequency. If there is a previous value at that
 * frequency it is replaced. */
OVRA_EXPORT ovrResult
ovrAudio_SetRoomControlValue(ovrAudioContext Context, ovrAudioControlZoneProperty property, float frequency, float value);

OVRA_EXPORT ovrResult ovrAudio_ResetRoomControl(ovrAudioContext Context, ovrAudioControlZoneProperty property);

/// The strength of the occlusion when the source is not directly visible, in the range [0,1].
///
/// \param context[in] context to use
/// \param sound[in] index of sound (0..NumSources-1)
/// \param value[in] A value of 1 means full effect (realistic occlusion), while 0 means no occlusion occurs.
///
OVRA_EXPORT ovrResult ovrAudio_SetSourceOcclusionIntensity(ovrAudioContext context, int sound, float value);

/// The strength of the occlusion when the source is not directly visible, in the range [0,1].
///
/// \param context[in] context to use
/// \param sound[in] index of sound (0..NumSources-1)
/// \param value[in] A value of 1 means full effect (realistic occlusion), while 0 means no occlusion occurs.
///
OVRA_EXPORT ovrResult ovrAudio_GetSourceOcclusionIntensity(ovrAudioContext context, int sound, float* value);

/// Gets an audio sources diffracted position
/// \param Context context to use
/// \param Sound index of sound (0..NumSources-1)
/// \param pX address of position of sound on X axis
/// \param pY address of position of sound on Y axis
/// \param pZ address of position of sound on Z axis
/// \return ovrError_AudioInvalidParam if the context is null or the specified sound index
/// is < 0 or greater than the number of available sources. ovrError_AudioUninitialized if
/// the context has yet to be initialized. ovrSuccess if query was successful.
OVRA_EXPORT ovrResult
ovrAudio_GetAudioSourceDiffractedPosition(ovrAudioContext Context, int Sound, float* PositionX, float* PositionY, float* PositionZ);

/// Set the diffraction order to trade off between diffraction quality and resource usage
///
/// \param value[in] The number of diffraction events that can occur along a single sound propagation path
///
OVRA_EXPORT ovrResult ovrAudio_SetDiffractionOrder(ovrAudioContext context, int value);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryUploadSimplifiedMesh(
    ovrAudioGeometry geometry,
    const ovrAudioMesh* mesh,
    const ovrAudioMeshSimplification* simplification);

OVRA_EXPORT ovrResult ovrAudio_AudioGeometryUploadSimplifiedMeshArrays(
    ovrAudioGeometry geometry,
    const void* vertices,
    size_t verticesByteOffset,
    size_t vertexCount,
    size_t vertexStride,
    ovrAudioScalarType vertexType,
    const void* indices,
    size_t indicesByteOffset,
    size_t indexCount,
    ovrAudioScalarType indexType,
    const ovrAudioMeshGroup* groups,
    size_t groupCount,
    const ovrAudioMeshSimplification* simplification);

#ifdef __cplusplus
}
#endif

#endif // OVR_Audio_AcousticRayTracing_h
