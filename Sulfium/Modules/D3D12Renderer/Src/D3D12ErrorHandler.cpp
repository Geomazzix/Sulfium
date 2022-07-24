#include "D3D12Renderer/Utility/D3D12ErrorHandler.h"

namespace SFM
{
	D3D12ErrorHandler::D3D12ErrorHandler()
	{
#if defined (_DEBUG)
		D3D_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&m_DebugInterface)));
		m_DebugInterface->EnableDebugLayer();

		//For "Device Removed Extended Data" - debug logging.
		D3D_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&m_DredSettings)));
		m_DredSettings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
		m_DredSettings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
#endif
	}

	void D3D12ErrorHandler::CheckAPIError(long hr, const char* method, const std::string& file, int lineNumber)
	{
		if (FAILED(hr))
		{
			SFM_LOGINFO(std::string(fmt::sprintf("D3D12 error in %s on line number %i in '%s'.", file.c_str(), lineNumber, method)));
		}
	}
}