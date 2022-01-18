cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/ApplicationCore.h
)

set(SOURCE_FILES
	Src/ApplicationCore.cpp
)

add_library(
	ApplicationCore
	STATIC
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(ApplicationCore PUBLIC
	Include
)