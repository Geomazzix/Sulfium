cmake_minimum_required(VERSION 3.10)

#Helpers for the installation of the project.
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(${CMAKE_SOURCE_DIR}/Cmake/SulfiumModuleUtility.cmake)

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

#Add all the 3rd party dependencies, project modules. They are called module, though this should not be confused with the CMake terminology for a "Module Library", more on this
#is explained in the cmake list file in the Modules folder.
#add_subdirectory(Externals)
add_subdirectory(Modules)
add_subdirectory(Sulfium)

#Generate the config file for the entire project, used to import all the targets required by find_package().
configure_package_config_file(
	${PROJECT_SOURCE_DIR}/CMake/${PROJECT_NAME}Config.cmake.in
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
INSTALL_DESTINATION
	${CMAKE_INSTALL_LIBDIR}/cmake/Sulfium
)

#Write the version file, which takes care of the package version control.
write_basic_package_version_file(
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

#Install both files in the cmake install directory located in lib/cmake/${PROJECT_NAME}
install(FILES
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
DESTINATION
	${CMAKE_INSTALL_LIBDIR}/CMake/Sulfium
)
