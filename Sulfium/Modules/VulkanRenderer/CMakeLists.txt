cmake_minimum_required(VERSION 3.10)

#Find vulkan before doing anything else, if it can't be found don't bother continueing with this part of the build.
find_package(Vulkan)
if(NOT Vulkan_FOUND)
	message(FATAL_ERROR "ERROR: Make sure to have the Vulkan SDK installed!")
endif()

set(HEADER_FILES
	Include/VulkanRenderer/VulkanModule.h
	Include/VulkanRenderer/VulkanRenderer.h

	Include/VulkanRenderer/Core/VulkanInstance.h
	Include/VulkanRenderer/Core/VulkanPhysicalDevice.h
	Include/VulkanRenderer/Core/VulkanDevice.h
	Include/VulkanRenderer/Core/VulkanQueueFamilyIndices.h
	Include/VulkanRenderer/Core/VulkanSwapChainRenderTargetInfo.h
	
	Include/VulkanRenderer/Utility/VulkanDebugMessenger.h
)

set(SOURCE_FILES
	Src/VulkanModule.cpp
	Src/VulkanRenderer.cpp
	Src/VulkanInstance.cpp
	Src/VulkanPhysicalDevice.cpp
	Src/VulkanDevice.cpp
	Src/VulkanDebugMessenger.cpp
)

SULFIUM_ADD_INTERNAL_MODULE_LIB(
	VulkanRenderer
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(VulkanRenderer PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<BUILD_INTERFACE:${SULFIUM_RENDERCORE_DIRECTORY}/Include/>
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Modules/ApplicationCore/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VulkanRenderer>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ApplicationCore/>
	${Vulkan_INCLUDE_DIRS}
)

message(	${Vulkan_INCLUDE_DIRS})

#Enables DLL symbol export.
target_compile_definitions(VulkanRenderer PRIVATE
	WIN_EXPORT
	cxx_std_17
)

if(WIN32)
target_compile_definitions(VulkanRenderer PRIVATE
	VK_USE_PLATFORM_WIN32_KHR
)
endif()

target_link_libraries(VulkanRenderer PUBLIC
	Core
	${Vulkan_LIBRARIES}
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