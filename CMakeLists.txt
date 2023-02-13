cmake_minimum_required(VERSION 3.9)
project(libmdk VERSION 0.0.1 DESCRIPTION "C89 library providing helper structures and functions.")

set (CMAKE_C_STANDARD 90)
set (CMAKE_C_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Release)
endif()

if (MSVC)
    add_compile_options(/W4)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    string(REGEX REPLACE "/W3" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}") # CMake always add /W3 to MSVC
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories("include")

file(
        GLOB_RECURSE
        source_files
        src/*.c
        include/*
)

file(
		GLOB_RECURSE
        tests_files
        tests/tests.c
		include/*
)

# Define sources and executable
set(LIBRARY_NAME "mdk")
set(TESTS_NAME "tests")
add_definitions(-DLIBMDK_EXPORT)
add_library(${LIBRARY_NAME} SHARED ${source_files})
add_executable(${TESTS_NAME} ${tests_files})
target_link_libraries(${TESTS_NAME} ${LIBRARY_NAME})
set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS ${LIBRARY_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(TARGETS ${TESTS_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
