cmake_minimum_required(VERSION 3.16)

set(MODULES_DIRECTORY ${CMAKE_SOURCE_DIRECTORY}/Modules)

add_subdirectory(ThreadSystem)
add_subdirectory(ApplicationCore)
add_subdirectory(RenderCore)
add_subdirectory(Core)

if(BUILD_VULKAN_BACKEND)
add_subdirectory(VulkanRenderer)
endif()

if(BUILD_D3D12_BACKEND)
add_subdirectory(D3D12Renderer)
endif()

if(USE_SULFIUM_GLTF)
add_subdirectory(Gltf)
endif()