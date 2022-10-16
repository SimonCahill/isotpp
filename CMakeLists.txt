cmake_minimum_required(VERSION 3.10)

project(isotpp LANGUAGES CXX VERSION 1.0 DESCRIPTION "A C++ implementation of the ISOTP CAN transmission protocol")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FILE(GLOB_RECURSE FILES ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

include_directories(
    include/
)

if (isotpp_DEBUG)
    add_definitions(
        -DDEBUG
        -D_DEBUG
        -Disotpp_DEBUG
    )


    add_compile_options(
        -ggdb
        -O0
    )
elseif(isotpp_SUPER_OPTIMISED)
    message(WARN "This could potentially result in an unstable build! Use with caution!")
    add_compile_options(
        -O3
    )
else()
    add_compile_options(
        -O2
    )
endif()

if (isotpp_BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC ${FILES})
else()
    add_library(${PROJECT_NAME} SHARED ${FILES})
endif()

if (isotpp_BUILD_TEST)
    # TODO
endif()

target_link_libraries(
    ${PROJECT_NAME}

    -lm
    -lpthread
)