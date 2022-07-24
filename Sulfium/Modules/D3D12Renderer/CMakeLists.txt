cmake_minimum_required(VERSION 3.10)

if(NOT WIN32)
	message(FATAL_ERROR "WARNING: This backend is specifically used for Windows OS!")
endif()

set(HEADER_FILES
	Include/D3D12Renderer/D3D12Module.h
	Include/D3D12Renderer/Utility/d3dx12.h
	Include/D3D12Renderer/Utility/D3D12ErrorHandler.h
	Include/D3D12Renderer/Utility/DXGIUtility.h
	Include/D3D12Renderer/D3D12Swapchain.h
	Include/D3D12Renderer/D3D12Fence.h
)

set(SOURCE_FILES
	Src/D3D12Module.cpp
	Src/D3D12ErrorHandler.cpp
	Src/DXGIUtility.cpp
	Src/D3D12Swapchain.cpp
	Src/D3D12Fence.cpp
)

SULFIUM_ADD_INTERNAL_MODULE_LIB(
	D3D12Renderer
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(D3D12Renderer PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<BUILD_INTERFACE:${SULFIUM_RENDERCORE_DIRECTORY}/Include/>
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Modules/ApplicationCore/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/D3D12Renderer>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ApplicationCore/>
)

#Enables DLL symbol export.
target_compile_definitions(D3D12Renderer PRIVATE
	WIN_EXPORT
	cxx_std_17
)

target_link_libraries(D3D12Renderer PUBLIC
	Core
	"d3d12.lib"
	"dxgi.lib"
	"d3dcompiler.lib"
)
target_precompile_headers(D3D12Renderer PUBLIC
	Include/D3D12Renderer/Pch.h
)

set_target_properties(D3D12Renderer PROPERTIES
	FOLDER 
		Modules
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	D3D12Renderer
	${CMAKE_CURRENT_SOURCE_DIR}/Include/
)
endif()