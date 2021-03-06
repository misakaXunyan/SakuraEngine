﻿#include <RenderGraphWebGPU/RenderGraphWebGPU.h>

sakura::graphics::webgpu::GPUBuffer::GPUBuffer(const GpuBufferHandle handle,
	const webgpu::RenderDevice& dev, const BufferDescriptor& desc) noexcept
	:desc_(desc), handle_(handle)
{
	WGPUBufferDescriptor buffDesc = {};
	buffDesc.usage = translate(desc.usages, desc.access);
	buffDesc.size = desc_.length;
	buffer = wgpuDeviceCreateBuffer(dev.device, &buffDesc);
	if(desc.data)
	{
		wgpuQueueWriteBuffer(
			dev.default_queue, buffer, 0, desc.data, desc.length);
	}
}

sakura::graphics::webgpu::GPUBuffer::~GPUBuffer()
{
	if(buffer)
	{
		wgpuBufferDestroy(buffer);
		wgpuBufferRelease(buffer);
	}
}

sakura::graphics::RenderResourceHandle sakura::graphics::webgpu::GPUBuffer::handle() const
{
	return handle_;
}

size_t sakura::graphics::webgpu::GPUBuffer::size() const
{
	return desc_.length;
}

sakura::graphics::BufferUsages sakura::graphics::webgpu::GPUBuffer::usages() const
{
	return desc_.usages;
}

