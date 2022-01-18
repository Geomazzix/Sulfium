cmake_minimum_required(VERSION 3.10)

set(HEADER_FILES
	Include/ThreadSystem.h
)

set(SOURCE_FILES
	Src/ThreadSystem.cpp
)

add_library(
	ThreadSystem
	STATIC
	${HEADER_FILES}
	${SOURCE_FILES}
)

target_include_directories(ThreadSystem PUBLIC
	Include
)