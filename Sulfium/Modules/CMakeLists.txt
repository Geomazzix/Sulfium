cmake_minimum_required(VERSION 3.16)

set(MODULES_DIRECTORY ${CMAKE_SOURCE_DIRECTORY}/Modules)

#The required static libraries of the engine.
add_subdirectory(ThreadSystem)
add_subdirectory(ApplicationCore)
add_subdirectory(RenderCore)

#Though these are optional they still have to be linked, since run-time DLL support will not be maintained due to the lack of interestand resources that can be
#spend on the project, therefore static libs containing the function symbols still need to be linked against and resolved by the linker.

if(${BUILD_VULKAN_BACKEND})
add_subdirectory(VulkanRenderer)
endif()

if(${USE_SULFIUM_GLTF})
add_subdirectory(Gltf)
endif()