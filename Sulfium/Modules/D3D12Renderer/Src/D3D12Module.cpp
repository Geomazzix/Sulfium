#include "D3D12Renderer/D3D12Module.h"
#include "RenderCore/DLLDefines.h"
#include "D3D12Renderer/Utility/DXGIUtility.h"

namespace SFM
{
	D3D12Module::D3D12Module() :
		m_useWARP(false)
	{}

	void D3D12Module::Initialize(GraphicsAPICreateInfo&& info)
	{
		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("D3D12 module boot info:\n");

		m_engine = info.Engine;
		m_GraphicsAPI_Name = "D3D12Renderer";

		m_physicalDevice = QueryOptimalAdapter(m_useWARP);
		m_device = CreateDevice(m_physicalDevice);
		m_commandQueue = CreateCommandQueue(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT);

		m_swapchain.Initialize(info.Window, m_device, m_commandQueue, info.FrameBufferWidth, info.FrameBufferHeight, 3);

		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("D3D12 module successfully initialized!");
		SFM_LOGINFO("==========================================");
	}

	void D3D12Module::Terminate()
	{
		//#TODO: Should flush before termination.
		m_swapchain.Terminate();
		m_commandQueue.Reset();
		m_device.Reset();

		SFM_LOGINFO("D3D12 module successfully terminated!");
	}

	void D3D12Module::OnFrameBufferResize(const WindowResizeEventArgs& e)
	{
		SFM_LOGINFO("Window resized!");
	}

	void D3D12Module::Render()
	{
		m_swapchain.ClearBackBuffer();
		m_swapchain.Present(m_commandQueue);
	}

	ComPtr<IDXGIAdapter4> D3D12Module::QueryOptimalAdapter(bool useWarp)
	{
		ComPtr<IDXGIFactory4> dxgiFactory;
		UINT createFactoryFlags = 0;
#if defined(_DEBUG)
		createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif
		D3D_CHECK(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));

		ComPtr<IDXGIAdapter1> dxgiAdapter1;
		ComPtr<IDXGIAdapter4> dxgiAdapter4;

		//Retrieve the optimal dxgiadapter1 and cast this to a dxgiadapter4.
		if (useWarp)
		{
			D3D_CHECK(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
			D3D_CHECK(dxgiAdapter1.As(&dxgiAdapter4));
		}
		else
		{
			SIZE_T foundDedicatedVideoMemory = 0;
			for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
			{
				DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
				dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

				if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
					SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
					dxgiAdapterDesc1.DedicatedVideoMemory > foundDedicatedVideoMemory)
				{
					foundDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
					D3D_CHECK(dxgiAdapter1.As(&dxgiAdapter4));
				}
			}
		}

		return dxgiAdapter4;
	}

	ComPtr<ID3D12Device2> D3D12Module::CreateDevice(ComPtr<IDXGIAdapter4> physicalDevice)
	{
		ComPtr<ID3D12Device2> d3d12Device2;
		D3D_CHECK(D3D12CreateDevice(physicalDevice.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&d3d12Device2)));
	
#if defined(_DEBUG)
		ComPtr<ID3D12InfoQueue> infoQueue;
		if (SUCCEEDED(d3d12Device2.As(&infoQueue)))
		{
			infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
			infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
			infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

			// Suppress whole categories of messages
			//D3D12_MESSAGE_CATEGORY Categories[] = {};

			// Suppress messages based on their severity level
			D3D12_MESSAGE_SEVERITY Severities[] =
			{
				D3D12_MESSAGE_SEVERITY_INFO
			};

			// Suppress individual messages by their ID
			D3D12_MESSAGE_ID DenyIds[] = {
				D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   // I'm really not sure how to avoid this message.
				D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
				D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
			};

			D3D12_INFO_QUEUE_FILTER NewFilter = {};
			//NewFilter.DenyList.NumCategories = _countof(Categories);
			//NewFilter.DenyList.pCategoryList = Categories;
			NewFilter.DenyList.NumSeverities = _countof(Severities);
			NewFilter.DenyList.pSeverityList = Severities;
			NewFilter.DenyList.NumIDs = _countof(DenyIds);
			NewFilter.DenyList.pIDList = DenyIds;

			D3D_CHECK(infoQueue->PushStorageFilter(&NewFilter));
		}
#endif

		return d3d12Device2;
	}

	ComPtr<ID3D12CommandQueue> D3D12Module::CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type)
	{
		ComPtr<ID3D12CommandQueue> d3d12CommandQueue;

		D3D12_COMMAND_QUEUE_DESC desc =
		{
			type,
			D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
			D3D12_COMMAND_QUEUE_FLAG_NONE,
			0
		};

		D3D_CHECK(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&d3d12CommandQueue)));
		return d3d12CommandQueue;
	}
}

extern "C" MODULE_EXPORT SFM::IGraphicsAPI* __cdecl CreateModule()
{
	return new SFM::D3D12Module();
}