cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/RenderCore.h
	Include/DLLDefines.h
	Include/IGraphicsAPI.h
	Include/GraphicsAPILoader.h
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
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
)

set_target_properties(RenderCore PROPERTIES
	FOLDER 
		Modules
)

target_precompile_headers(
	RenderCore PUBLIC Include/Pch.h
)

SULFIUM_INSTALL_AND_EXPORT_TARGETS(
	RenderCore 
	""
)

SULFIUM_INSTALL_HEADERS(
	RenderCore
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)