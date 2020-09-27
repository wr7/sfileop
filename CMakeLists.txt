cmake_minimum_required(VERSION "3.17.2")
project(sfileop VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(FILE_IO "STD" CACHE STRING "The file I/O used; valid options are STD and POSIX (1 and 2 can be used in the place of STD and POSIX)")

if(FILE_IO STREQUAL "POSIX")
	set(FILE_IO "2")
elseif(FILE_IO STREQUAL "STD")
	set(FILE_IO "1")
endif()

if(NOT ((FILE_IO STREQUAL "1") OR (FILE_IO STREQUAL "2")))
	message(FATAL_ERROR "Invalid FILE_IO provided")
endif()

include_directories(${CMAKE_BINARY_DIR})

configure_file(config.h.in config.h)

add_executable(sread sread.c)
add_executable(swrite swrite.c)
