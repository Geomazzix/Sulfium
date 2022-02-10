##############################################################################################################
#Sulfium module utility file, contains:
# - sulfium_add_third_party_lib
# - sulfium_add_internal_lib
# - sulfium_add_internal_static_lib
# - sulfium_install_targets
# - sulfium_install_headers
# - sulfium_add_internal_shared_lib
# - sulfium_add_internal_object_lib
# - sulfium_add_internal_module_lib

#MODULE/LIBRARY UTILITY.
##############################################################################################################

cmake_minimum_required(VERSION 3.16)

#Adding a third party library to the build and install tree.
function(sulfium_add_third_party_lib NAME)
    if (SULFIUM_SHARED)
        #Create the shared library
        add_library(
            ${NAME} 
            SHARED 
            ${ARGN}
        )

        if (MSVC)
            set_target_properties(${NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
        endif()
    else() #Else make it a static library
        add_library(
            ${NAME} 
            STATIC 
            ${ARGN}
        )

        if (MSVC)
            set_target_properties(${NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS OFF)
        endif()
    endif()

    #Create an alias library for the component.
    if(NOT ${NAME} STREQUAL "Sulfium")
        add_library(Sulfium::${NAME} :: ALIAS ${NAME})
    endif()
endfunction()

#Adding an internal library to the project.
function(sulfium_add_internal_lib NAME)
    SULFIUM_ADD_THIRD_PARTY_LIB(${NAME} ${ARGN})

    if (SULFIUM_SHARED AND MSVC)
        set_target_properties(${NAME} PROPERTIES 
            WINDOWS_EXPORT_ALL_SYMBOLS ON
        )
    endif()
endfunction()

#Adding a static library to the project.
function(sulfium_add_internal_static_lib NAME)
    add_library(
        ${NAME} 
        STATIC 
        ${ARGN}
    )

endfunction()

#Adding a module library to the project.
function(sulfium_add_internal_module_lib NAME)
    add_library(
        ${NAME} 
        MODULE
        ${ARGN}
    )

    if (MSVC)
        set_target_properties(${NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    endif()
endfunction()

#Adding a shared library to the project.
function(sulfium_add_internal_shared_lib NAME)
    add_library(
        ${NAME} 
        SHARED 
        ${ARGN}
    )

    if (MSVC)
        set_target_properties(${NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    endif()
endfunction()

#Adding a shared library to the project.
function(sulfium_add_internal_object_lib NAME)
    add_library(
        ${NAME} 
        OBJECT
        ${ARGN}
    )

    if (MSVC)
        set_target_properties(${NAME} PROPERTIES
            LINK_FLAGS "/WHOLEARCHIVE"
	        POSITION_INDEPENDENT_CODE ON
            WINDOWS_EXPORT_ALL_SYMBOLS ON
        )
    endif()
endfunction()

##############################################################################################################


#INSTALL UTILITY
##############################################################################################################

#Installing libraries - always expects name of library as first target.
function(sulfium_install_and_export_targets TARGET_NAME)
    if(SULFIUM_INSTALL)
        #Installing - specify files to package.
        install(
	        TARGETS
		        ${ARGV}
	        EXPORT ${TARGET_NAME}Exports
	        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		        NAMELINK_SKIP #Skip on first try in order to export the library as Sulfium-major.minor.patch.lib
	        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

        #The export meta data - in this case a file that concerns itself to the targets mentioned above.
        install(
	        EXPORT ${TARGET_NAME}Exports
	        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}
	        NAMESPACE Sulfium::
        )

        #2nd install added for name linking so unix systems support -L Sulfium, without the major.minor.patch
        install(
	        TARGETS 
		        ${ARGV}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		        NAMELINK_ONLY
	        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
	        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

        #Generate the config file for the entire project, used to import all the targets required by find_package().
        configure_package_config_file(
	        ${PROJECT_SOURCE_DIR}/CMake/${TARGET_NAME}Config.cmake.in
	        ${PROJECT_BINARY_DIR}/${TARGET_NAME}Config.cmake
        INSTALL_DESTINATION
	        ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}
        )

        #Write the version file, which takes care of the package version control.
        write_basic_package_version_file(
	        ${PROJECT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake
	        VERSION ${PROJECT_VERSION}
	        COMPATIBILITY SameMajorVersion
        )

        #Install both files in the cmake install directory located in lib/cmake/${PROJECT_NAME}
        install(FILES
	        ${PROJECT_BINARY_DIR}/${TARGET_NAME}Config.cmake
	        ${PROJECT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake
        DESTINATION
	        ${CMAKE_INSTALL_LIBDIR}/CMake/${TARGET_NAME}
        )

    endif(SULFIUM_INSTALL)
endfunction()

#Installing headers.
function(sulfium_install_headers NAME HEADER_DIR)
    if(SULFIUM_INSTALL)
        if(${NAME} STREQUAL "Sulfium")
            set(HEADER_DESTINATION_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/Core)
        else()
            set(HEADER_DESTINATION_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/)
        endif()

        #Installing the current target's headers.
        install(
	        DIRECTORY ${HEADER_DIR}/
	        DESTINATION ${HEADER_DESTINATION_DIRECTORY}
            FILES_MATCHING
                PATTERN *.h
                PATTERN *.inl
                PATTERN *.hpp
                PATTERN *.ih

                #GLM
                PATTERN "cmake" EXCLUDE
                PATTERN "doc" EXCLUDE
                PATTERN "test" EXCLUDE
                PATTERN "util" EXCLUDE

                #Pch shouldn't be copied over!
                PATTERN "Pch.h" EXCLUDE
        )
    endif(SULFIUM_INSTALL)
endfunction()
##############################################################################################################
