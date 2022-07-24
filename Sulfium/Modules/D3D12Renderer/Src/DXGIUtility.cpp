#include "D3D12Renderer/Utility/DXGIUtility.h"

namespace SFM
{
	bool DXGIUtilty::CheckTearingSupport()
	{
		BOOL allowTearing = FALSE;
		ComPtr<IDXGIFactory5> factory5;
		if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory5))))
		{
			if (FAILED(factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing))))
			{
				allowTearing = FALSE;
			}
		}

		return allowTearing == TRUE;
	}
}