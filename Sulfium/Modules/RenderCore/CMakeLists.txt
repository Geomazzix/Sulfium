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

add_library(
	RenderCore
	STATIC
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(RenderCore PUBLIC
	Include
)

#Creating the PCH
target_precompile_headers(
	RenderCore PUBLIC Include/Pch.h
)