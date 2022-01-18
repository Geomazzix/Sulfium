cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/GltfModule.h
	Include/Gltf.h
)

set(SOURCE_FILES
	Src/GltfModule.cpp
	Src/Gltf.cpp
)

add_library(
	Gltf
	SHARED
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(Gltf PUBLIC
	Include
	${SULFIUM_INCLUDE_DIRECTORY}
)

#Enables DLL symbol export.
target_compile_definitions(Gltf PUBLIC
	WIN_EXPORT
)