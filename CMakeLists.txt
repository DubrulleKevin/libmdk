cmake_minimum_required(VERSION 3.1)
project(libmdk)

set (CMAKE_C_STANDARD 90)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Release)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

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
set(LIBRARY_NAME "libmdk")
set(TEST_NAME "test")
add_definitions(-DLIBMDK_EXPORT)
add_library(${LIBRARY_NAME} SHARED ${source_files})
add_executable(${TEST_NAME} ${test_files})
target_link_libraries(${TEST_NAME} ${LIBRARY_NAME})

install(TARGETS ${LIBRARY_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(TARGETS ${EXAMPLE_DEMO_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)