##############################################################################################################
#Sulfium module utility file, contains:
# - sulfium_add_third_party_lib
# - sulfium_add_internal_lib
# - sulfium_install_targets
# - sulfium_install_headers


#MODULE/LIBRARY UTILITY.
##############################################################################################################

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

##############################################################################################################


#INSTALL UTILITY
##############################################################################################################

#Installing libraries - always expects name of library as first target.
function(sulfium_install_and_export_targets TARGETS)
    if(SULFIUM_INSTALL)
        
        separate_arguments(EXPORT_TARGETS UNIX_COMMAND ${TARGETS})
        list(GET EXPORT_TARGETS 0 TARGET_NAME)

        #Installing - specify files to package.
        install(
	        TARGETS
		        ${EXPORT_TARGETS}
	        EXPORT ${TARGET_NAME}Exports
	        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		        NAMELINK_SKIP #Skip on first try in order to export the library as Sulfium-major.minor.patch.lib
	        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

        #The export meta data.
        install(
	        EXPORT ${TARGET_NAME}Exports
	        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}
	        NAMESPACE Sulfium::
        )

        #2nd install added for name linking so unix systems support -L Sulfium, without the major.minor.patch
        install(
	        TARGETS 
		        ${EXPORT_TARGETS}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		        NAMELINK_ONLY
	        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
    endif(SULFIUM_INSTALL)
endfunction()

#Installing headers.
function(sulfium_install_headers NAME HEADER_DIR)
    if(SULFIUM_INSTALL)
        if(${NAME} STREQUAL "Sulfium")
            set(HEADER_DESTINATION_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/Core)
        else()
            set(HEADER_DESTINATION_DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/${NAME})
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
        )
    endif(SULFIUM_INSTALL)
endfunction()
##############################################################################################################
