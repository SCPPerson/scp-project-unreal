// This file is part of the FidelityFX Super Resolution 2.0 Unreal Engine Plugin.
//
// Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#pragma once

#include "FSR2Include.h"
#include "RHIResources.h"
#include "RendererInterface.h"
#include "RenderGraphDefinitions.h"
#include "RenderGraphBuilder.h"

//-------------------------------------------------------------------------------------
// The maximum number of resources that can be allocated.
//-------------------------------------------------------------------------------------
#ifndef FSR2_MAX_RESOURCE_COUNT
#define FSR2_MAX_RESOURCE_COUNT 64
#endif

//-------------------------------------------------------------------------------------
// State data for the FSR2 backend that manages mapping resources between UE & FSR2.
//-------------------------------------------------------------------------------------
struct FFSR2BackendState
{
	struct Resource
	{
		FRHIResource* Resource;
		FfxResourceDescription Desc;
		TRefCountPtr<IPooledRenderTarget>* RT;
		FRDGTexture* RDG;
		TRefCountPtr<FRDGPooledBuffer>* PooledBuffer;
	} Resources[FSR2_MAX_RESOURCE_COUNT];
	FfxRenderJobDescription Jobs[FSR2_MAX_RESOURCE_COUNT];
	uint64 ResourceMask;
	uint64 DynamicMask;
	uint32 NumJobs;

	uint32 AddResource(FRHIResource* Resource, FfxResourceType Type, TRefCountPtr<IPooledRenderTarget>* RT, FRDGTexture* RDG, TRefCountPtr<FRDGPooledBuffer>* PooledBuffer);

	FRHIResource* GetResource(uint32 Index);

	FRDGTextureRef GetOrRegisterExternalTexture(FRDGBuilder& GraphBuilder, uint32 Index);

	FRDGTexture* GetRDGTexture(FRDGBuilder& GraphBuilder, uint32 Index);

	FRDGBufferRef GetRDGBuffer(FRDGBuilder& GraphBuilder, uint32 Index);

	TRefCountPtr<IPooledRenderTarget> GetPooledRT(uint32 Index);

	FfxResourceType GetType(uint32 Index);

	void RemoveResource(uint32 Index);
};

//-------------------------------------------------------------------------------------
// FSR2-style functions for the RHI backend to help setup the FSR2 library.
//-------------------------------------------------------------------------------------
extern FfxErrorCode ffxFsr2GetInterfaceUE(FfxFsr2Interface* outInterface, class FFSR2TemporalUpscaler const* Upscaler, void* scratchBuffer, size_t scratchBufferSize);
extern size_t ffxFsr2GetScratchMemorySize();
extern FfxResource ffxGetResourceFromUEResource(FfxFsr2Interface* backendInterface, FRDGTexture* rdgRes, FfxResourceStates state = FFX_RESOURCE_STATE_COMPUTE_READ);
