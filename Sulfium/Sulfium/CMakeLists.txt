cmake_minimum_required(VERSION 3.16)

#List all the header files.
set(HEADER_FILES
	Include/Sulfium.h
)

#List all the source files.
set(SOURCE_FILES
	Src/Main.cpp
	Src/Sulfium.cpp
)

#Add the main library of the project.
add_library(
	Sulfium
	STATIC
	${HEADER_FILES}
	${SOURCE_FILES}
)

#Add all the include directories of the projects.
target_include_directories(Sulfium PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	#${MODULES_DIRECTORY}ThreadSystem/Include
	#${MODULES_DIRECTORY}ApplicationCore/Include
	#${MODULES_DIRECTORY}RenderCore/Include
)

#All depencies connected to Sulfium according to https://lucid.app/lucidchart/0b97d091-8d77-4b75-a080-4d96d210966b/edit?invitationId=inv_cf056a50-91a2-4e0f-be82-1df210fe7c47
#target_link_libraries(Sulfium PUBLIC
#	ThreadSystem
#	ApplicationCore
#	RenderCore
#)

#Creating the PCH
target_precompile_headers(
	Sulfium PUBLIC Include/Pch.h
)


#INSTALLING
#----------------------------------------------------------------------------------------------------

#Step 1, Installing - specify files to package.
install(
	TARGETS Sulfium
	EXPORT SulfiumExports
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		NAMELINK_SKIP #Skip on first try in order to export the library as Sulfium-major.minor.patch.lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#Step 2, the export meta data.
install(
	EXPORT SulfiumExports
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Sulfium-${PROJECT_VERSION}
	NAMESPACE Sulfium::
)

#Step 3, 2nd install added for name linking so unix systems support -L Sulfium, without the major.minor.patch
install(
	TARGETS Sulfium
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		NAMELINK_ONLY
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#Step 4, installing the headers.
install(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING
	PATTERN *.h
	PATTERN *.hpp
	PATTERN *.inl
	PATTERN *.ih
)

#Generate the config file, used to import all the targets required by FindModule.
configure_package_config_file(
	${PROJECT_SOURCE_DIR}/CMake/${PROJECT_NAME}Config.cmake.in
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
INSTALL_DESTINATION
	${CMAKE_INSTALL_LIBDIR}/cmake/Sulfium-${PROJECT_VERSION}
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
	${CMAKE_INSTALL_LIBDIR}/CMake/Sulfium-${PROJECT_VERSION}
)