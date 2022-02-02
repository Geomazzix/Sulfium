cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/Gltf/GltfModule.h
	Include/Gltf/Gltf.h
)

set(SOURCE_FILES
	Src/GltfModule.cpp
	Src/Gltf.cpp
)

SULFIUM_ADD_INTERNAL_STATIC_LIB(
	Gltf
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(Gltf PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Gltf>
)

#Enables DLL symbol export.
target_compile_definitions(Gltf PRIVATE
	WIN_EXPORT
)

set_target_properties(Gltf PROPERTIES
	FOLDER 
		Modules
)

if(${SULFIUM_INSTALL})
SULFIUM_INSTALL_HEADERS(
	Gltf
	${CMAKE_CURRENT_SOURCE_DIR}/Include/
)
endif()