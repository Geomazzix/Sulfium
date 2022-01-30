cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/ThreadSystem.h
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
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Modules/ThreadSystem>
)

set_target_properties(ThreadSystem PROPERTIES
	FOLDER 
		Modules
)

SULFIUM_INSTALL_AND_EXPORT_TARGETS(
	ThreadSystem 
	""
)
SULFIUM_INSTALL_HEADERS(
	ThreadSystem
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)