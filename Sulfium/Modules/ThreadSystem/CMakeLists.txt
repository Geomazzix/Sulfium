cmake_minimum_required(VERSION 3.16)

set(HEADER_FILES
	Include/ThreadSystem/ThreadSystem.h
)

set(SOURCE_FILES
	Src/ThreadSystem.cpp
)

SULFIUM_ADD_INTERNAL_STATIC_LIB(
	ThreadSystem
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(ThreadSystem PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ThreadSystem>
)

set_target_properties(ThreadSystem PROPERTIES
	FOLDER 
		Modules
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	ThreadSystem
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)
endif()