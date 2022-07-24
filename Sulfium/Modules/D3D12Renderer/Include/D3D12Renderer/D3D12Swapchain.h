#include <RenderCore/IGraphicsAPI.h>

namespace SFM
{
	/// <summary>
	/// Manages the swap chain backend used for rendering to the screen.
	/// </summary>
	class D3D12Swapchain
	{
	public:
		D3D12Swapchain();
		~D3D12Swapchain() = default;

		void Initialize(WindowHandle& windowx, ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandQueue> cmdQueue, uint32_t width, uint32_t height, uint32_t bufferCount);
		void Terminate();

		void OnClientResize(uint32_t width, uint32_t height);
		void ClearBackBuffer();
		void Present(ComPtr<ID3D12CommandQueue> cmdQueue);

	private:
		uint64_t Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue);
		void WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent);
		void Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent);

		ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
		ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
		ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> cmdAllocator, D3D12_COMMAND_LIST_TYPE type);

		const uint8_t m_numFrames = 3;
		uint32_t clientWidth;
		uint32_t clientHeight;

		ComPtr<IDXGISwapChain4> m_swapchain;
		ComPtr<ID3D12Resource> m_backBuffers[3];
		ComPtr<ID3D12DescriptorHeap> m_RTVDescriptorHeap;
		uint32_t m_RTVDescriptorSize;
		uint32_t m_currentBackBufferIndex;

		ComPtr<ID3D12Fence> m_fence;
		uint64_t m_fenceValue;
		uint64_t m_frameFenceValues[3];
		HANDLE m_fenceEvent;

		ComPtr<ID3D12GraphicsCommandList> m_commandList;
		ComPtr<ID3D12CommandAllocator> m_commandAllocators[3];

		bool m_vsync = true;
		bool m_tearingSupported = false;
	};
}