#include "D3D12Renderer/D3D12Swapchain.h"
#include "D3D12Renderer/Utility/D3D12ErrorHandler.h"
#include "D3D12Renderer/Utility/DXGIUtility.h"

namespace SFM
{
	D3D12Swapchain::D3D12Swapchain() :
		m_currentBackBufferIndex(0)
	{}

	void D3D12Swapchain::Initialize(WindowHandle& window, ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandQueue> cmdQueue, uint32_t width, uint32_t height, uint32_t bufferCount)
	{
		//Creating the factory.
		ComPtr<IDXGIFactory4> dxgiFactory4;
		UINT createFactoryFlags = 0;
#if defined(_DEBUG)
		createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif	
		D3D_CHECK(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4)));
	
		//Specify multi sampling.
		DXGI_SAMPLE_DESC sampleDesc =
		{
			1,	//Count
			0	//Quality
		};

		//Creating the swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapchainDesc =
		{
			width,
			height,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			FALSE,
			sampleDesc,
			DXGI_USAGE_RENDER_TARGET_OUTPUT,
			bufferCount,
			DXGI_SCALING_STRETCH,
			DXGI_SWAP_EFFECT_FLIP_DISCARD,
			DXGI_ALPHA_MODE_UNSPECIFIED,
			DXGIUtilty::CheckTearingSupport() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0
		};

		ComPtr<IDXGISwapChain1> swapchain1;
		D3D_CHECK(dxgiFactory4->CreateSwapChainForHwnd(cmdQueue.Get(), window, &swapchainDesc, nullptr, nullptr, &swapchain1));
		D3D_CHECK(dxgiFactory4->MakeWindowAssociation(window, DXGI_MWA_NO_ALT_ENTER)); //When pressing ALT + ENTER go into borderless full screen instead of DXGI fullscreen.
		D3D_CHECK(swapchain1.As(&m_swapchain));
		
		m_currentBackBufferIndex = m_swapchain->GetCurrentBackBufferIndex();

		//Creating the descriptor heaps for the Render Target Views (RTVs).
		D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc =
		{
			D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			bufferCount,
			D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			0
		};

		D3D_CHECK(device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&m_RTVDescriptorHeap)));
	
		//Updating the RTVs using the descriptor heap.
		m_RTVDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

		for (int i = 0; i < bufferCount; ++i)
		{
			ComPtr<ID3D12Resource> backBuffer;
			D3D_CHECK(m_swapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));

			device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);
			m_backBuffers[i] = backBuffer;
			rtvHandle.Offset(m_RTVDescriptorSize);
		}

		//Creating the synchronizations objects.
		D3D_CHECK(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		m_fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		assert(m_fenceEvent && "Failed to create fence event!");

		for (int i = 0; i < 3; ++i)
		{
			m_commandAllocators[i] = CreateCommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT);
		}
		m_commandList = CreateCommandList(device, m_commandAllocators[0], D3D12_COMMAND_LIST_TYPE_DIRECT);
		m_commandList->Close();
	}

	void D3D12Swapchain::Terminate()
	{
		CloseHandle(m_fenceEvent);

		m_commandList.Reset();
		for (int i = 0; i < 3; ++i)
		{
			m_commandAllocators[i].Reset();
		}
		m_swapchain.Reset();
	}

	void D3D12Swapchain::ClearBackBuffer()
	{
		m_commandAllocators[m_currentBackBufferIndex]->Reset();
		m_commandList->Reset(m_commandAllocators[m_currentBackBufferIndex].Get(), nullptr);

		//Move the back buffer into a render target state.
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			m_backBuffers[m_currentBackBufferIndex].Get(),
			D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		m_commandList->ResourceBarrier(1, &barrier);

		//Clear the back buffer render target through the offset RTV.
		FLOAT clearColor[] = { 0.4f, 0.6f, 0.9f, 1.0f };
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(m_RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			m_currentBackBufferIndex, m_RTVDescriptorSize);
		m_commandList->ClearRenderTargetView(rtv, clearColor, 0, nullptr);
	}

	void D3D12Swapchain::Present(ComPtr<ID3D12CommandQueue> cmdQueue)
	{
		//Transition the back buffer to a presentable state.
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
			m_backBuffers[m_currentBackBufferIndex].Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		m_commandList->ResourceBarrier(1, &barrier);

		D3D_CHECK(m_commandList->Close());

		ID3D12CommandList* const commandLists[] = {
			m_commandList.Get()
		};
		cmdQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		m_frameFenceValues[m_currentBackBufferIndex] = Signal(cmdQueue, m_fence, m_fenceValue);

		UINT syncInterval = m_vsync ? 1 : 0;
		UINT presentFlags = m_tearingSupported && !m_vsync ? DXGI_PRESENT_ALLOW_TEARING : 0;
		D3D_CHECK(m_swapchain->Present(syncInterval, presentFlags));

		m_currentBackBufferIndex = m_swapchain->GetCurrentBackBufferIndex();
		WaitForFenceValue(m_fence, m_frameFenceValues[m_currentBackBufferIndex], m_fenceEvent);
	}

	ComPtr<ID3D12CommandAllocator> D3D12Swapchain::CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12CommandAllocator> commandAllocator;
		D3D_CHECK(device->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)));
		return commandAllocator;
	}

	ComPtr<ID3D12GraphicsCommandList> D3D12Swapchain::CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> cmdAllocator, D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12GraphicsCommandList> commandList;
		D3D_CHECK(device->CreateCommandList(0, type, cmdAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
		return commandList;
	}

	uint64_t D3D12Swapchain::Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue)
	{
		uint64_t fenceValueForSignal = ++fenceValue;
		D3D_CHECK(commandQueue->Signal(fence.Get(), fenceValueForSignal));
		return fenceValueForSignal;
	}

	void D3D12Swapchain::WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent)
	{
		if (fence->GetCompletedValue() < fenceValue)
		{
			D3D_CHECK(fence->SetEventOnCompletion(fenceValue, fenceEvent));
			WaitForSingleObject(fenceEvent, INFINITE);
		}
	}

	void D3D12Swapchain::Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent)
	{
		uint64_t fenceValueForSignal = Signal(commandQueue, fence, fenceValue);
		WaitForFenceValue(fence, fenceValueForSignal, fenceEvent);
	}
}
