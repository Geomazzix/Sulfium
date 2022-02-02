cmake_minimum_required(VERSION 3.16)

set(HEADER_FILES
	Include/ApplicationCore/ApplicationCore.h
)

set(SOURCE_FILES
	Src/ApplicationCore.cpp
)

SULFIUM_ADD_INTERNAL_STATIC_LIB(
	ApplicationCore
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(ApplicationCore PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ApplicationCore>
)

set_target_properties(ApplicationCore PROPERTIES
	FOLDER 
		Modules
)

if(${SULFIUM_INSTALL})
SULFIUM_INSTALL_HEADERS(
	ApplicationCore
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)
endif()