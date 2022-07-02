#include "ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf.h"

typedef union ffx_fsr2_lock_pass_PermutationKey {
    struct {
        uint32_t FFX_FSR2_OPTION_USE_LANCZOS_LUT : 1;
        uint32_t FFX_FSR2_OPTION_HDR_COLOR_INPUT : 1;
        uint32_t FFX_FSR2_OPTION_LOW_RESOLUTION_MOTION_VECTORS : 1;
        uint32_t FFX_FSR2_OPTION_JITTERED_MOTION_VECTORS : 1;
        uint32_t FFX_FSR2_OPTION_INVERTED_DEPTH : 1;
        uint32_t FFX_FSR2_OPTION_APPLY_SHARPENING : 1;
    };
    uint32_t index;
} ffx_fsr2_lock_pass_PermutationKey;

typedef struct ffx_fsr2_lock_pass_PermutationInfo {
    const uint32_t       blobSize;
    const unsigned char* blobData;


    const uint32_t  numCBVResources;
    const char**    cbvResourceNames;
    const uint32_t* cbvResourceBindings;
    const uint32_t* cbvResourceCounts;
    const uint32_t* cbvResourceSpaces;

    const uint32_t  numSRVResources;
    const char**    srvResourceNames;
    const uint32_t* srvResourceBindings;
    const uint32_t* srvResourceCounts;
    const uint32_t* srvResourceSpaces;

    const uint32_t  numUAVResources;
    const char**    uavResourceNames;
    const uint32_t* uavResourceBindings;
    const uint32_t* uavResourceCounts;
    const uint32_t* uavResourceSpaces;

    const uint32_t  numSamplerResources;
    const char**    samplerResourceNames;
    const uint32_t* samplerResourceBindings;
    const uint32_t* samplerResourceCounts;
    const uint32_t* samplerResourceSpaces;

    const uint32_t  numRTAccelerationStructureResources;
    const char**    rtAccelerationStructureResourceNames;
    const uint32_t* rtAccelerationStructureResourceBindings;
    const uint32_t* rtAccelerationStructureResourceCounts;
    const uint32_t* rtAccelerationStructureResourceSpaces;
} ffx_fsr2_lock_pass_PermutationInfo;

static const uint32_t g_ffx_fsr2_lock_pass_IndirectionTable[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static const ffx_fsr2_lock_pass_PermutationInfo g_ffx_fsr2_lock_pass_PermutationInfo[] = {
    { g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_size, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_data, 1, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_CBVResourceNames, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_CBVResourceBindings, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_CBVResourceCounts, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_CBVResourceSpaces, 3, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SRVResourceNames, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SRVResourceBindings, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SRVResourceCounts, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SRVResourceSpaces, 2, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_UAVResourceNames, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_UAVResourceBindings, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_UAVResourceCounts, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_UAVResourceSpaces, 1, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SamplerResourceNames, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SamplerResourceBindings, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SamplerResourceCounts, g_ffx_fsr2_lock_pass_3f9842edd5d19eebc068430b48c767cf_SamplerResourceSpaces, 0, 0, 0, 0, 0, },
};
