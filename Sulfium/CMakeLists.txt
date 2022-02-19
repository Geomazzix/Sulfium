cmake_minimum_required(VERSION 3.16)

#Making sure all cmake files can be found.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

#Helpers for the installation of the project.
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(SulfiumModuleUtility)

set(PROJECT_NAME Sulfium)

#Setting up the version.
set(SULFIUM_VERSION_MAJOR 0)
set(SULFIUM_VERSION_MINOR 1)
set(SULFIUM_VERSION_PATCH 0)
set(SULFIUM_VERSION ${SULFIUM_VERSION_MAJOR}.${SULFIUM_VERSION_MINOR}.${SULFIUM_VERSION_PATCH})

#Project setup.
project(
	${PROJECT_NAME}
	VERSION ${SULFIUM_VERSION}
	DESCRIPTION "Sulfium represent the full project, including optional modules and 3rd party dependencies."
	HOMEPAGE_URL https://github.com/Geomazzix/Sulfium
	LANGUAGES CXX C
)

#General project settings.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Set general directories for references sake.
set(SULFIUM_DIRECTORY ${CMAKE_SOURCE_DIR}/Sulfium)
set(SULFIUM_RENDERCORE_DIRECTORY ${CMAKE_SOURCE_DIR}/Modules/RenderCore)

#Sets the output directories all in one place.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Bin/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Bin/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Bin)

#The options provided by Sulfium for the user to configure.
option(SULFIUM_SHARED "Builds Sulfium as a shared library" OFF)
option(SULFIUM_INSTALL "Installs the full build into an provided install directory" ON)
option(BUILD_VULKAN_BACKEND "Specify whether you want the Vulkan backend to be build" ON)
option(USE_SULFIUM_GLTF "Specify whether the user wants to use the Sulfium GLTF module, which currently is a wrapper for TinyGltf" ON)

#Add all the 3rd party dependencies, project modules. They are called module, though this should not be confused with the CMake terminology for a "Module Library", more on this
#is explained in the cmake list file in the Modules folder.
add_subdirectory(Externals)
add_subdirectory(Modules)
add_subdirectory(Sulfium)

if(SULFIUM_INSTALL)

#Install the cmake utility files in the cmake install directory located in lib/cmake/${PROJECT_NAME}
install(FILES
	${PROJECT_SOURCE_DIR}/CMake/${PROJECT_NAME}ModuleUtility.cmake
DESTINATION
	${CMAKE_INSTALL_LIBDIR}/CMake/Sulfium
)

#Package the whole project into a single export config.
set(SULFIUM_EXPORT_TARGETS
	Sulfium
	Entt
	Core
	glm
	tinygltf
	ThreadSystem
	ApplicationCore
	RenderCore
)

if(BUILD_VULKAN_BACKEND)
list(APPEND SULFIUM_EXPORT_TARGETS VulkanRenderer) #Component loaded in on runtime as shared library
endif()

if(USE_SULFIUM_GLTF)
list(APPEND SULFIUM_EXPORT_TARGETS Gltf)
endif()

if(WIN32 OR APPLE OR UNIX)
list(APPEND SULFIUM_EXPORT_TARGETS Spdlog)
endif()

sulfium_install_and_export_targets(
	${SULFIUM_EXPORT_TARGETS}	
)
endif()