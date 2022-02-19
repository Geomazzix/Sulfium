cmake_minimum_required(VERSION 3.10)

#Find vulkan before doing anything else, if it can't be found don't bother continueing with this part of the build.
find_package(Vulkan)
if(NOT Vulkan_FOUND)
	message(FATAL_ERROR "ERROR: Make sure to have the Vulkan SDK installed!")
endif()

set(HEADER_FILES
	Include/VulkanRenderer/VulkanModule.h
	Include/VulkanRenderer/VulkanRenderer.h
)

set(SOURCE_FILES
	Src/VulkanModule.cpp
	Src/VulkanRenderer.cpp
)

SULFIUM_ADD_INTERNAL_MODULE_LIB(
	VulkanRenderer
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(VulkanRenderer PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<BUILD_INTERFACE:${SULFIUM_RENDERCORE_DIRECTORY}/Include/>
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Modules/ApplicationCore/Include/ApplicationCore/Window/>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VulkanRenderer>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ApplicationCore/Window/>
)

#Enables DLL symbol export.
target_compile_definitions(VulkanRenderer PRIVATE
	WIN_EXPORT
	cxx_std_17
)

target_link_libraries(VulkanRenderer PUBLIC
	Core
)
target_precompile_headers(VulkanRenderer PUBLIC
	Include/VulkanRenderer/Pch.h
)

set_target_properties(VulkanRenderer PROPERTIES
	FOLDER 
		Modules
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	VulkanRenderer
	${CMAKE_CURRENT_SOURCE_DIR}/Include/
)
endif()