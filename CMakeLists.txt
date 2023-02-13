cmake_minimum_required(VERSION 3.9)
project(libmdk VERSION 0.0.1 DESCRIPTION "C89 library providing helper structures and functions.")

set (CMAKE_C_STANDARD 90)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Release)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

if (MSVC)
    add_compile_options(/W4)
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
        test_files
        tests/tests.c
		include/*
)

# Define sources and executable
set(LIBRARY_NAME "mdk")
set(TEST_NAME "test")
add_definitions(-DLIBMDK_EXPORT)
add_library(${LIBRARY_NAME} SHARED ${source_files})
add_executable(${TEST_NAME} ${test_files})
target_link_libraries(${TEST_NAME} ${LIBRARY_NAME})
set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS ${LIBRARY_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(TARGETS ${EXAMPLE_DEMO_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)