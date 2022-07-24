#pragma once
#include <RenderCore/IGraphicsAPI.h>
#include <ApplicationCore/Window/WindowEventArgs.h>
#include "D3D12Renderer/Utility/D3D12ErrorHandler.h"
#include "D3D12Renderer/D3D12Swapchain.h"
#include "D3D12Renderer/D3D12Fence.h"

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class D3D12Module final : public IGraphicsAPI
	{
	public:
		D3D12Module();
		~D3D12Module() = default;

		void Initialize(GraphicsAPICreateInfo&& info) override;
		void Terminate() override;

		void OnFrameBufferResize(const WindowResizeEventArgs& e) override;
		
		void Render() override;

	private:
		ComPtr<IDXGIAdapter4> QueryOptimalAdapter(bool useWarp);
		ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> physicalDevice);
		ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);

		bool CheckTearingSupport();

		D3D12ErrorHandler m_errorHandler; //Must be constructed on module construction.
		std::weak_ptr<Engine> m_engine;

		bool m_useWARP; //Windows Advanced Rasterizer Platform

		ComPtr<IDXGIAdapter4> m_physicalDevice;

		ComPtr<ID3D12Device2> m_device;
		ComPtr<ID3D12CommandQueue> m_commandQueue;

		D3D12Swapchain m_swapchain;
	};
}