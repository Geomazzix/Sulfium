cmake_minimum_required(VERSION 3.16)

set(HEADER_FILES
	Include/RenderCore/RenderCore.h
	Include/RenderCore/DLLDefines.h
	Include/RenderCore/IGraphicsAPI.h
	Include/RenderCore/GraphicsAPILoader.h
)

set(SOURCE_FILES
	Src/GraphicsAPILoader.cpp
	Src/RenderCore.cpp
)

SULFIUM_ADD_INTERNAL_STATIC_LIB(
	RenderCore
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(RenderCore PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Modules/ApplicationCore/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ApplicationCore/>
)
target_compile_definitions(RenderCore PRIVATE
	SULFIUM_DLL_DIRECTORY="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/"
)

target_link_libraries(RenderCore PUBLIC
	Core
)

if(BUILD_VULKAN_BACKEND)
target_compile_definitions(RenderCore PRIVATE
	VULKAN_BACKEND
)
endif()

if(BUILD_D3D12_BACKEND)
target_compile_definitions(RenderCore PRIVATE
	D3D12_BACKEND
)
endif()

set_target_properties(RenderCore PROPERTIES
	FOLDER 
		Modules
)

target_precompile_headers(
	RenderCore PUBLIC Include/RenderCore/Pch.h
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	RenderCore
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)
endif()