cmake_minimum_required(VERSION 3.15)

#! CHANGE YOUR PROJECT NAME
set(PROJECT_NAME test_vector_array)
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 20)

##########################################################
# User configurable options of the template
##########################################################
set(WARNINGS_AS_ERRORS OFF)
set(ENABLE_PVS_STUDIO OFF)

set(ENABLE_UBSan OFF)
set(ENABLE_ASAN OFF)
set(ENABLE_TSan OFF)
set(ENABLE_MSAN OFF)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

include(cmake/CompilerWarnings.cmake)

##########################################################
# Header-only libraries
##########################################################
add_library(my_vector INTERFACE)
target_include_directories(my_vector INTERFACE my_vector)

add_library(my_array INTERFACE)
target_include_directories(my_array INTERFACE my_array)

##########################################################
# Main executable
##########################################################
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} my_vector my_array)

##########################################################
# Tests
##########################################################
add_executable(my_vector_tests
		my_vector_tests/test_vector.cpp
		my_vector_tests/test_vector.h
)
target_link_libraries(my_vector_tests my_vector)

add_executable(my_array_tests
		my_array_tests/my_array_tests.cpp
		my_array_tests/my_array_tests.h
)
target_link_libraries(my_array_tests my_array)

##########################################################
# Install
##########################################################
INSTALL(PROGRAMS
		$<TARGET_FILE:${PROJECT_NAME}>
		DESTINATION bin
)

set(ALL_TARGETS ${PROJECT_NAME} my_vector_tests my_array_tests)

include(cmake/main-config.cmake)
