#include "RenderCore/GraphicsAPILoader.h"
#include "Core/Printer/Printer.h"

namespace SFM
{
	GraphicsAPIModule& GraphicsAPILoader::LoadGraphicsAPI(const std::string& relativeModulePath)
	{
		std::size_t index = relativeModulePath.find_last_of('/');
		std::string moduleName = relativeModulePath.substr(index + 1, relativeModulePath.size() - index);

		auto& it = m_modules.find(moduleName);
		if (it != m_modules.end())
		{
			SFM_LOGCRITICAL("WARNING: Trying to load module that is already loaded in memory and will therefore be skipped: %s.", moduleName.c_str());
			return m_modules[moduleName];
		}

		GraphicsAPIModule graphicsAPIModule;
		LoadSharedLibrary(relativeModulePath, graphicsAPIModule.Process);

		createModuleFunction = (CreateModule)GetSymbol(graphicsAPIModule.Process, "CreateModule");
		if (createModuleFunction == nullptr)
		{
			SFM_LOGCRITICAL("Failed to retrieve the mandatory 'CreateModule' method in the library: %s.", moduleName.c_str());
		}
		else
		{
			graphicsAPIModule.Handle = createModuleFunction();
		}

		m_modules.insert(std::make_pair(moduleName, graphicsAPIModule));
		return m_modules[moduleName];
	}

	void GraphicsAPILoader::UnloadGraphicsAPI(const std::string& moduleName)
	{
		auto& it = m_modules.find(moduleName);
		if (it == m_modules.end())
		{
			SFM_LOGERROR("Failed: Failed to destroy module, presence of module '%s' not found.", moduleName.c_str());
			return;
		}

		m_modules[moduleName].Handle = nullptr;		//Doesn't have to be deleted, since the module gets wiped from memory anyways.
		FreeLibrary(m_modules[moduleName].Process);
		m_modules.erase(moduleName);
	}

	void GraphicsAPILoader::LoadSharedLibrary(const std::string& moduleName, SharedLib& process)
	{
#if defined(WIN32) || defined(WIN64)
		//Try the development folder structure first.
		std::string modulePath = GetModuleRootFolder();

		modulePath += moduleName;
		process = LoadLibraryA(modulePath.c_str());
		if (!process)
		{
			char errstr[1024] = "FormatMessage failed (unknown error code?)";
			if (GetLastErrorString(errstr, sizeof(errstr)))
			{
				SFM_LOGCRITICAL("Failed to load %s: %s\tTrying local DLL", modulePath.c_str(), errstr);
			}

			//See if the dll is perhaps in the current folder.
			process = LoadLibraryA(moduleName.c_str());
			if (!process)
			{
				GetLastErrorString(errstr, sizeof(errstr));
				SFM_LOGCRITICAL("Unable to open %s: %s", moduleName.c_str(), errstr);
			}
		}
#endif
	}

	char* GraphicsAPILoader::GetModuleRootFolder()
	{
#if defined(SULFIUM_DLL_DIRECTORY)
		return SULFIUM_DLL_DIRECTORY;
#else
		return "";
#endif
	}

#if defined(WIN32) || defined(WIN64)
	bool GetLastErrorString(char* buffer, DWORD length)
	{
		DWORD err = GetLastError();
		if (!err)
		{
			return false;
		}

		// Assuming buffer is large enough for any error message.
		// Otherwise, use FORMAT_MESSAGE_ALLOCATE_BUFFER and LocalFree!
		auto ret = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
			buffer,
			length,
			NULL
		);

		return ret > 0;
	}

	FARPROC GetSymbol(SharedLib module, const char* symbol)
	{
		return GetProcAddress(module, symbol);
	}
#endif
}