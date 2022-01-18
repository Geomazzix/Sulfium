#pragma once
#include "IGraphicsAPI.h"

namespace SFM
{
#if defined(WIN32) || defined(WIN64)
	typedef HMODULE SharedLib;

	/// <summary>
	/// Retrieves the last error caught by the windows OS and stores this in the provided buffer.
	/// </summary>
	/// <param name="buffer">A pointer to the buffer of the error message.</param>
	/// <param name="length">An expected buffer length for the message.</param>
	/// <returns>Returns true or false depending on if an error occured, false meaning everything is fine.</returns>
	bool GetLastErrorString(char* buffer, DWORD length);

	/// <summary>
	/// Wrapper function for GetProccAddress();
	/// </summary>
	/// <param name="module">The module of the engine.</param>
	/// <param name="symbol">The symbol that should be retrieved from the shared library.</param>
	/// <returns>Returns a function pointer that can/should be casted to the function of the request.</returns>
	FARPROC GetSymbol(SharedLib module, const char* symbol);
#endif

	/// <summary>
	/// Holds the information on a sulfium module.
	/// </summary>
	struct GraphicsAPIModule
	{
		IGraphicsAPI* Handle;
		SharedLib Process;
	};

	/// <summary>
	/// This class is responsible for loading DLL modules into memory and granting access to the initialize and terminate methods of the modules.
	/// Currently the class only loads windows modules.
	/// </summary>
	class GraphicsAPILoader final
	{
	public:
		GraphicsAPILoader() = default;
		~GraphicsAPILoader() = default;

		/// <summary>
		/// Loads a shared library into memory and returns the *uninitialized* result.
		/// </summary>
		GraphicsAPIModule& LoadGraphicsAPI(const std::string& moduleName);

		/// <summary>
		/// Deletes the handle to the shared library and frees the shared library from memory.
		/// *Note: Make sure that the module should be done processing whatever it's been doing, 
		/// since this function will delete the handle to it and immediately free the occupied memory.
		/// </summary>
		void UnloadGraphicsAPI(const std::string& moduleName);

	private:
		/// <summary>
		/// Loads a shared library into memory and stores it in the handle that is passed by reference.
		/// </summary>
		/// <param name="moduleName">The name of the library.</param>
		/// <param name="sharedLib">The shared library reference, containing the result of the function.</param>
		void LoadSharedLibrary(const std::string& moduleName, SharedLib& sharedLib);

		/// <summary>
		/// Returns the hard coded root folder where the build DLLs should live.
		/// </summary>
		/// <returns></returns>
		char* GetModuleRootFolder();

		//Function point for module creation, deletion happens immediately when requested.
		typedef IGraphicsAPI* (_cdecl* CreateModule)();
		CreateModule createModuleFunction;

		/// <summary>
		/// Keeps track of the currently loaded graphics APIs. This is required for hotloading them.
		/// </summary>
		std::unordered_map<std::string, GraphicsAPIModule> m_modules;
	};
}