cmake_minimum_required(VERSION 3.16)

set(APP_CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include/ApplicationCore)

set(HEADER_FILES
	${APP_CORE_INCLUDE_DIR}/ApplicationCore.h
	
	${APP_CORE_INCLUDE_DIR}/Window/WindowEventArgs.h
	${APP_CORE_INCLUDE_DIR}/Window/Win32Window.h
	${APP_CORE_INCLUDE_DIR}/Window/Window.h
	
	${APP_CORE_INCLUDE_DIR}/Input/Input.h
	${APP_CORE_INCLUDE_DIR}/Input/InputEventArgs.h
	${APP_CORE_INCLUDE_DIR}/Input/KeyCodes.h
)

set(SOURCE_FILES
	Src/ApplicationCore.cpp
	Src/Window/Win32Window.cpp
	Src/Input/Input.cpp
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

target_link_libraries(ApplicationCore PUBLIC
	Core
)

target_precompile_headers(ApplicationCore PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Include/ApplicationCore/Pch.h
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	ApplicationCore
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)
endif()