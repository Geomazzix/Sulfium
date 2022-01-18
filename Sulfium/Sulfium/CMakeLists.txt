cmake_minimum_required(VERSION 3.16)

#Create a configuration file, that leaks the version number of the application into the code base as a define.
set(Sulfium_MODULE_DIRECTORY ../Modules/)
configure_file(Config/SulfiumConfig.h.in SulfiumConfig.h)

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
add_executable(
	Sulfium
	${HEADER_FILES}
	${SOURCE_FILES}
)

#Add all the include directories of the projects.
target_include_directories(Sulfium PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
	Include
	${MODULES_DIRECTORY}ThreadSystem/Include
	${MODULES_DIRECTORY}ApplicationCore/Include
	${MODULES_DIRECTORY}RenderCore/Include
)

#All depencies connected to Sulfium according to https://lucid.app/lucidchart/0b97d091-8d77-4b75-a080-4d96d210966b/edit?invitationId=inv_cf056a50-91a2-4e0f-be82-1df210fe7c47
target_link_libraries(Sulfium PUBLIC
	ThreadSystem
	ApplicationCore
	RenderCore
)

#Creating the PCH
target_precompile_headers(
	Sulfium PUBLIC Include/Pch.h
)