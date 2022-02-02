cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/VulkanRenderer/VulkanModule.h
	Include/VulkanRenderer/VulkanRenderer.h
)

set(SOURCE_FILES
	Src/VulkanModule.cpp
	Src/VulkanRenderer.cpp
)

SULFIUM_ADD_INTERNAL_SHARED_LIB(
	VulkanRenderer
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(VulkanRenderer PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<BUILD_INTERFACE:${SULFIUM_RENDERCORE_DIRECTORY}/Include/>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VulkanRenderer>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/RenderCore>
)

#Enables DLL symbol export.
target_compile_definitions(VulkanRenderer PRIVATE
	WIN_EXPORT
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