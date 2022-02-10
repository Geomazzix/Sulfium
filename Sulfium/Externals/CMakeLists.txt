cmake_minimum_required(VERSION 3.16)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)

#Glm - header only.
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(Glm)

target_include_directories(glm_static PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Glm>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Glm>
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	Glm
	${CMAKE_CURRENT_SOURCE_DIR}/Glm/
)
endif()

#Spdlog
SULFIUM_ADD_INTERNAL_STATIC_LIB(
	Spdlog
	Spdlog/src/async.cpp
	Spdlog/src/cfg.cpp
	Spdlog/src/color_sinks.cpp
	Spdlog/src/file_sinks.cpp
	Spdlog/src/fmt.cpp
	Spdlog/src/spdlog.cpp
	Spdlog/src/stdout_sinks.cpp
)

target_include_directories(Spdlog PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Spdlog/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/spdlog>
)

target_compile_definitions(Spdlog PUBLIC
	SPDLOG_COMPILED_LIB
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	Spdlog
	${CMAKE_CURRENT_SOURCE_DIR}/Spdlog/include/
)
endif()

#TinyGltf.
set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF CACHE BOOL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE BOOL "" FORCE)
set(TINY_GLTF_HEADER_ONLY OFF CACHE BOOL "" FORCE)
add_subdirectory(Tinygltf)

if(SULFIUM_INSTALL)
#Don't use sulfium utility, since that copies a directory.
INSTALL ( 
	FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Tinygltf/json.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Tinygltf/stb_image.h
		${CMAKE_CURRENT_SOURCE_DIR}/Tinygltf/stb_image_write.h
		${CMAKE_CURRENT_SOURCE_DIR}/Tinygltf/tiny_gltf.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Tinygltf
)
endif()

#Signal library
add_library(Signals INTERFACE 
	${CMAKE_CURRENT_SOURCE_DIR}/Signals/optional.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Signals/signals.hpp
)

target_include_directories(Signals INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Signals>
)

if(SULFIUM_INSTALL)
#Don't use sulfium utility, since that copies a directory.
INSTALL ( 
	FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Signals/optional.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Signals/signals.hpp
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Signals
)
endif()

#Imgui-dependency & Imguizmo, due to object library siyrce files not being able to link themselves into another project.
#set(IMGUI_SOURCES
#    Imgui/imgui.cpp
#    Imgui/imgui_demo.cpp
#    Imgui/imgui_draw.cpp
#    Imgui/imgui_widgets.cpp
#)
#
#set(IMGUI_HEADERS
#    Imgui/imconfig.h
#    Imgui/imgui.h
#    Imgui/imgui_internal.h
#    Imgui/imstb_rectpack.h
#    Imgui/imstb_textedit.h
#    Imgui/imstb_truetype.h
#)
#
#set(IMGUIZMO_SOURCES
#   Imguizmo/GraphEditor.cpp
#   Imguizmo/ImCurveEdit.cpp
#   Imguizmo/ImGradient.cpp
#   Imguizmo/Imguizmo.cpp
#   Imguizmo/ImSequencer.cpp
#)
#
#set(IMGUIZMO_HEADERS
#   Imguizmo/GraphEditor.h
#   Imguizmo/ImCurveEdit.h
#   Imguizmo/ImGradient.h
#   Imguizmo/Imguizmo.h
#   Imguizmo/ImSequencer.h
#   Imguizmo/ImZoomSlider.h
#)
#
#SULFIUM_ADD_INTERNAL_STATIC_LIB(Imgui
#    ${IMGUI_SOURCES}
#    ${IMGUI_HEADERS}
#	${IMGUIZMO_SOURCES}
#	${IMGUIZMO_HEADERS}
#)
#
#target_include_directories(Imgui PUBLIC
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Imgui>
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo>
#	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIRS}/Imgui>
#	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIRS}>
#)
#
#if(SULFIUM_INSTALL)
##Don't use sulfium utility, since that copies a directory.
#INSTALL (
#	FILES
#		${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imconfig.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imgui.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imgui_internal.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imstb_rectpack.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imstb_textedit.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imstb_truetype.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo/GraphEditor.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo/ImCurveEdit.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo/ImGradient.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo/Imguizmo.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo/ImSequencer.h
#		${CMAKE_CURRENT_SOURCE_DIR}/Imguizmo/ImZoomSlider.h
#	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Imgui
#)
#endif()

#Adding the targets to a "Modules" filter in the cmake view and build structure.
set_target_properties(
	glm_static
	uninstall
	PROPERTIES
		FOLDER 
			Externals/glm
)

set_target_properties(
	Spdlog
	tinygltf
	#Imgui
	Signals
	PROPERTIES
		FOLDER 
			Externals
)