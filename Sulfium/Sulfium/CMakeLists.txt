cmake_minimum_required(VERSION 3.16)

#List all the header files.
set(HEADER_FILES
	Include/Sulfium.h

	Include/World/World.h
	
	Include/Ecs/Entity.h
	Include/Ecs/EcsUtility.h
	Include/Ecs/SystemDirector.h

	Include/Ecs/Components/NameComponent.h
	Include/Ecs/Components/RelationComponent.h
	Include/Ecs/Components/SceneComponent.h
	Include/Ecs/Components/SceneEntityTypeComponent.h
	Include/Ecs/Components/TransformComponent.h
	
	Include/Ecs/Systems/TransformSystem.h
	Include/Ecs/Systems/ISystem.h
)

#List all the source files.
set(SOURCE_FILES
	Src/Sulfium.cpp
	Src/World.cpp
	Src/Entity.cpp
	Src/TransformSystem.cpp
	Src/ISystem.cpp
	Src/SystemDirector.cpp
)

#Add the main library of the project.
SULFIUM_ADD_INTERNAL_LIB(
	Sulfium
	${HEADER_FILES}
	${SOURCE_FILES}
)

#Add all the include directories of the projects.
target_include_directories(Sulfium PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#All depencies connected to Sulfium according to https://lucid.app/lucidchart/0b97d091-8d77-4b75-a080-4d96d210966b/edit?invitationId=inv_cf056a50-91a2-4e0f-be82-1df210fe7c47
target_link_libraries(Sulfium PUBLIC
	Core
	ThreadSystem
	ApplicationCore
	RenderCore
	glm
)

target_compile_definitions(Sulfium INTERFACE
	cxx_std_17 #enforce cxx17 on any target that wants to use the library, since signals requires this.
)

#Creating the PCH
target_precompile_headers(
	Sulfium PUBLIC Include/Pch.h
)

sulfium_install_headers(
	Sulfium
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)

set_target_properties(Sulfium PROPERTIES
	SOVERSION ${SULFIUM_VERSION_MAJOR}
	VERSION ${SULFIUM_VERSION}
)