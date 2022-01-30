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
sulfium_add_internal_lib(
	Sulfium
	${HEADER_FILES}
	${SOURCE_FILES}
)

#Add all the include directories of the projects.
target_include_directories(Sulfium PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#All depencies connected to Sulfium according to https://lucid.app/lucidchart/0b97d091-8d77-4b75-a080-4d96d210966b/edit?invitationId=inv_cf056a50-91a2-4e0f-be82-1df210fe7c47
target_link_libraries(Sulfium PUBLIC
	ThreadSystem
#	ApplicationCore
#	RenderCore
)

#Creating the PCH
target_precompile_headers(
	Sulfium PUBLIC Include/Pch.h
)

set(SULFIUM_EXPORTED_TARGETS
	Sulfium
	ThreadSystem
)

sulfium_install_and_export_targets(
	${SULFIUM_EXPORTED_TARGETS}
)
sulfium_install_headers(
	Sulfium
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)