cmake_minimum_required(VERSION 3.10)

#Sets helper directory.
set(EXTERNAL_DEPENDENCIES_DIRECTORY ${CMAKE_SOURCE_DIRECTORY}/Externals)


#Glm
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(Glm)

target_include_directories(
	glm_static
    PUBLIC
        Glm/glm
)

#Spdlog
add_library(
	Spdlog
	STATIC
	Spdlog/src/spdlog.cpp
)

target_include_directories(
	Spdlog
	PUBLIC
		Spdlog/include
)

target_compile_definitions(
	Spdlog
	PUBLIC
		SPDLOG_COMPILED_LIB
)

#TinyGltf.
set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF CACHE BOOL "" FORCE)
set(TINYGLTF_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(Tinygltf)

#Imgui-dependency.
set(IMGUI_SOURCES
    Imgui/imgui.cpp
    Imgui/imgui_demo.cpp
    Imgui/imgui_draw.cpp
    Imgui/imgui_widgets.cpp
)

set(IMGUI_HEADERS
    Imgui/imconfig.h
    Imgui/imgui.h
    Imgui/imgui_internal.h
    Imgui/imstb_rectpack.h
    Imgui/imstb_textedit.h
    Imgui/imstb_truetype.h
)

add_library(Imgui
    STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_HEADERS}
)

#Imguizmo
set(IMGUIZMO_SOURCES
   Imguizmo/GraphEditor.cpp
   Imguizmo/ImCurveEdit.cpp
   Imguizmo/ImGradient.cpp
   Imguizmo/Imguizmo.cpp
   Imguizmo/ImSequencer.cpp
)

set(IMGUIZMO_HEADERS
   Imguizmo/GraphEditor.h
   Imguizmo/ImCurveEdit.h
   Imguizmo/ImGradient.h
   Imguizmo/Imguizmo.h
   Imguizmo/ImSequencer.h
   Imguizmo/ImZoomSlider.h
)

add_library(Imguizmo
    STATIC
    ${IMGUIZMO_SOURCES}
    ${IMGUIZMO_HEADERS}
)

target_include_directories(Imguizmo PUBLIC
	${CMAKE_SOURCE_DIR}/Externals/Imgui
)

#Adding the targets to a "Modules" filter in the cmake view and build structure.
set_target_properties(
	glm_static
	Spdlog
	tinygltf
	Imgui
	Imguizmo
	uninstall
	PROPERTIES
		FOLDER 
			Externals
)