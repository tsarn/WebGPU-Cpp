/**
 * This file is part of the "Learn WebGPU for C++" book.
 *   https://github.com/eliemichel/LearnWebGPU
 *
 * MIT License
 * Copyright (c) 2022 Elie Michel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * Exactly one of your source files must #define WEBGPU_CPP_IMPLEMENTATION
 * before including this header.
 * 
 * NB: This file has been generated by the webgpu-cpp generator
 *   (see https://github.com/eliemichel/webgpu-cpp )
 */

#pragma once

#include <webgpu.h>

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

/**
 * A namespace providing a more C++ idiomatic API to WebGPU.
 */
namespace wgpu {

struct DefaultFlag {};
constexpr DefaultFlag Default;

#define HANDLE(Type) \
class Type { \
public: \
	typedef Type S; /* S == Self */ \
	typedef WGPU ## Type W; /* W == WGPU Type */ \
	Type(const W& w) : m_raw(w) {} \
	operator W&() { return m_raw; } \
	operator bool() const { return m_raw != nullptr; } \
	friend auto operator<<(std::ostream &stream, const S& self) -> std::ostream & { \
		return stream << "<wgpu::" << #Type << " " << self.m_raw << ">"; \
	} \
private: \
	W m_raw; \
public:

#define DESCRIPTOR(Type) \
struct Type : public WGPU ## Type { \
public: \
	typedef Type S; /* S == Self */ \
	typedef WGPU ## Type W; /* W == WGPU Type */ \
	Type() : W() { nextInChain = nullptr; } \
	Type(const DefaultFlag &) : W() { setDefault(); } \
	operator W&() { return *this; } \
	friend auto operator<<(std::ostream &stream, const S&) -> std::ostream & { \
		return stream << "<wgpu::" << #Type << ">"; \
	} \
public:

#define STRUCT(Type) \
struct Type : public WGPU ## Type { \
public: \
	typedef Type S; /* S == Self */ \
	typedef WGPU ## Type W; /* W == WGPU Type */ \
	Type() : W() {} \
	Type(const DefaultFlag &) : W() { setDefault(); } \
	friend auto operator<<(std::ostream &stream, const S&) -> std::ostream & { \
		return stream << "<wgpu::" << #Type << ">"; \
	} \
public:

#define ENUM(Type) \
class Type { \
public: \
	typedef Type S; /* S == Self */ \
	typedef WGPU ## Type W; /* W == WGPU Type */ \
	Type(const W& w) : m_raw(w) {} \
	operator W() { return m_raw; } \
private: \
	W m_raw; \
public:

#define ENUM_ENTRY(Name, Value) \
	static constexpr W Name = (W)Value;

#define END };

{{begin-inject}}
HANDLE(Instance)
	Adapter requestAdapter(const RequestAdapterOptions& options);
END
HANDLE(Adapter)
	Device requestDevice(const DeviceDescriptor& descriptor);
END
STRUCT(Color)
	Color(double r, double g, double b, double a) : WGPUColor{ r, g, b, a } {}
END
STRUCT(Extent3D)
	Extent3D(uint32_t width, uint32_t height, uint32_t depthOrArrayLayers) : WGPUExtent3D{ width, height, depthOrArrayLayers } {}
END
STRUCT(Origin3D)
	Origin3D(uint32_t x, uint32_t y, uint32_t z) : WGPUOrigin3D{ x, y, z } {}
END
{{end-inject}}

{{begin-blacklist}}
wgpuBindGroupSetLabel
wgpuBindGroupLayoutSetLabel
wgpuBufferSetLabel
wgpuCommandBufferSetLabel
wgpuCommandEncoderResolveQuerySet
wgpuCommandEncoderSetLabel
wgpuCommandEncoderWriteTimestamp
wgpuComputePassEncoderBeginPipelineStatisticsQuery
wgpuComputePassEncoderEndPipelineStatisticsQuery
wgpuComputePassEncoderSetLabel
wgpuComputePipelineSetLabel
wgpuDeviceCreateComputePipelineAsync
wgpuDeviceCreateQuerySet
wgpuDeviceCreateRenderPipelineAsync
wgpuDevicePopErrorScope
wgpuDevicePushErrorScope
wgpuDeviceSetLabel
wgpuInstanceProcessEvents
wgpuPipelineLayoutSetLabel
wgpuQuerySetDestroy
wgpuQuerySetSetLabel
wgpuQueueOnSubmittedWorkDone
wgpuQueueSetLabel
wgpuRenderBundleEncoderSetLabel
wgpuRenderPassEncoderBeginOcclusionQuery
wgpuRenderPassEncoderBeginPipelineStatisticsQuery
wgpuRenderPassEncoderEndOcclusionQuery
wgpuRenderPassEncoderEndPipelineStatisticsQuery
wgpuRenderPassEncoderSetLabel
wgpuRenderPipelineSetLabel
wgpuSamplerSetLabel
wgpuShaderModuleGetCompilationInfo
wgpuShaderModuleSetLabel
wgpuTextureSetLabel
wgpuTextureViewSetLabel
{{end-blacklist}}

// Enumerations
{{enums}}

// Structs
{{structs}}

// Descriptors
{{descriptors}}

// Handles forward declarations
{{handles_decl}}

// Callback types
{{callbacks}}

// Handles detailed declarations
{{handles}}

// Non-member procedures
{{procedures}}

Instance createInstance(const InstanceDescriptor& descriptor) {
	return wgpuCreateInstance(&descriptor);
}

#ifdef WEBGPU_CPP_IMPLEMENTATION

// Handles members implementation
{{handles_impl}}

// Extra implementations
Adapter Instance::requestAdapter(const RequestAdapterOptions& options) {
	Adapter adapter = nullptr;
	bool requestEnded = false;
	
	auto onAdapterRequestEnded = [&adapter, &requestEnded](RequestAdapterStatus status, Adapter _adapter, char const * message) {
		if (status == RequestAdapterStatus::Success) {
			adapter = _adapter;
		} else {
			std::cout << "Could not get WebGPU adapter: " << message << std::endl;
		}
		requestEnded = true;
	};

	requestAdapter(options, onAdapterRequestEnded);

	assert(requestEnded);
	return adapter;
}

Device Adapter::requestDevice(const DeviceDescriptor& descriptor) {
	WGPUDevice device = nullptr;
	bool requestEnded = false;

	auto onDeviceRequestEnded = [&device, &requestEnded](RequestDeviceStatus status, Device _device, char const * message) {
		if (status == RequestDeviceStatus::Success) {
			device = _device;
		} else {
			std::cout << "Could not get WebGPU adapter: " << message << std::endl;
		}
		requestEnded = true;
	};

	requestDevice(descriptor, onDeviceRequestEnded);

	assert(requestEnded);
	return device;
}

#endif // WEBGPU_CPP_IMPLEMENTATION

#undef HANDLE
#undef DESCRIPTOR
#undef ENUM
#undef ENUM_ENTRY
#undef END

} // namespace wgpu
