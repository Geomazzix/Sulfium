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
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
)

set_target_properties(RenderCore PROPERTIES
	FOLDER 
		Modules
)

target_precompile_headers(
	RenderCore PUBLIC Include/RenderCore/Pch.h
)

SULFIUM_INSTALL_HEADERS(
	RenderCore
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)