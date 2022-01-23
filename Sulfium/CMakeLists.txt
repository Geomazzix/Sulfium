cmake_minimum_required(VERSION 3.10)

#Project setup.
project(
	Sulfium
	VERSION 0.1
	DESCRIPTION "Sulfium represent the full project, including optional modules and 3rd party dependencies."
	HOMEPAGE_URL https://github.com/Geomazzix/Sulfium
	LANGUAGES CXX
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

#Add all the 3rd party dependencies, project modules. They are called module, though this should not be confused with the CMake terminology for a "Module Library", more on this
#is explained in the cmake list file in the Modules folder.
add_subdirectory(Externals)
add_subdirectory(Modules)
add_subdirectory(Sulfium)