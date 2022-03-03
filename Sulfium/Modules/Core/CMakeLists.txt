cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/Core/Engine.h
	Include/Core/Printer/Printer.h

	Include/Core/Events/EventSystem.h
	Include/Core/Events/EventArgs.h
	Include/Core/Timer/Stopwatch.h
)

set(SOURCE_FILES
	Src/Engine.cpp
	Src/Printer.cpp
	Src/EventSystem.cpp
	Src/Stopwatch.cpp
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

target_link_libraries(Core PUBLIC
	Spdlog
	Entt
)

set_target_properties(Core PROPERTIES
	FOLDER 
		Modules
)

target_compile_definitions(Core PUBLIC
	cxx_std_17 #enforce cxx17 on any target that wants to use the library, since signals requires this.
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