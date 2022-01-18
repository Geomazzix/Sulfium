cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/VulkanModule.h
	Include/VulkanRenderer.h
)

set(SOURCE_FILES
	Src/VulkanModule.cpp
	Src/VulkanRenderer.cpp
)

add_library(
	VulkanRenderer
	SHARED
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(VulkanRenderer PUBLIC
	Include
	${SULFIUM_DIRECTORY}/Include
	${SULFIUM_RENDERCORE_DIRECTORY}/Include
	${CMAKE_CURRENT_BINARY_DIR}
)

#Enables DLL symbol export.
target_compile_definitions(VulkanRenderer PUBLIC
	WIN_EXPORT
)