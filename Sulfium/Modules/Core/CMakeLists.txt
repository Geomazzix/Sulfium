cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/Core/Engine.h
	Include/Core/Printer/Printer.h

	Include/Core/Events/Delegate.h
	Include/Core/Events/EventArgs.h
	Include/Core/Events/EventSystem.h
)

set(SOURCE_FILES
	Src/Engine.cpp
	Src/Printer.cpp
	Src/EventSystem.cpp
)

SULFIUM_ADD_INTERNAL_STATIC_LIB(
	Core
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(Core PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Core>
)

if(WIN32 OR APPLE OR UNIX)
target_link_libraries(Core PUBLIC
	Spdlog
	Signals
)
endif()

set_target_properties(Core PROPERTIES
	FOLDER 
		Modules
)

target_precompile_headers(Core PUBLIC
	Include/Core/Pch.h
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	Printer
	${CMAKE_CURRENT_SOURCE_DIR}/Include/
)
endif()