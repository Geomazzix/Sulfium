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

#Entt
add_library(Entt INTERFACE)

message(${CMAKE_CURRENT_SOURCE_DIR}/entt/src)

target_include_directories(Entt INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/entt/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/entt>
)

target_compile_features(Entt INTERFACE 
	cxx_std_17
)

target_compile_definitions(Entt INTERFACE
	ENTT_USE_ATOMIC			#https://github.com/skypjack/entt/wiki/Crash-Course:-configuration#entt_use_atomic
	NOMINMAX				#https://github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-C4003-the-min-the-max-and-the-macro
)

if(SULFIUM_INSTALL)
SULFIUM_INSTALL_HEADERS(
	Entt
	${CMAKE_CURRENT_SOURCE_DIR}/entt/src/
)
endif()

#Spdlog
#file(GLOB_RECURSE SPDLOG_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Spdlog/include/spdlog/*.h)
#file(GLOB_RECURSE SPDLOG_INLINE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Spdlog/include/spdlog/*.inl)
#
#SULFIUM_ADD_INTERNAL_STATIC_LIB(
#	Spdlog
#	${SPDLOG_HEADERS}
#	${SPDLOG_INLI1NE_HEADERS}
#	Spdlog/src/async.cpp
#	Spdlog/src/cfg.cpp
#	Spdlog/src/color_sinks.cpp
#	Spdlog/src/file_sinks.cpp
#	Spdlog/src/fmt.cpp
#	Spdlog/src/spdlog.cpp
#	Spdlog/src/stdout_sinks.cpp
#)

add_library(Spdlog INTERFACE)

target_include_directories(Spdlog INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Spdlog/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/spdlog>
)

#target_compile_definitions(Spdlog PUBLIC
#	SPDLOG_COMPILED_LIB
#)

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
	PROPERTIES
		FOLDER 
			Externals
)