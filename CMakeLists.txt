cmake_minimum_required(VERSION 3.20)

project(mcproto
    VERSION 1.0
    LANGUAGES CXX)

option(MCPROTO_STANDALONE "Option to build libmcproto standalone.")
option(MCPROTO_ENABLE_TESTS "Option to build tests")

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(MCPROTO_STANDALONE ON)
endif()

set(MCPROTO_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mcproto/common/utils.cpp")

set(MCPROTO_MAIN_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

set(MCPROTO_TESTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/types.cpp"
)

add_library(${PROJECT_NAME} ${MCPROTO_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ./include)

if (MCPROTO_STANDALONE)
    add_executable(mcproto_main ${MCPROTO_MAIN_SOURCE})
    target_link_libraries(mcproto_main PRIVATE mcproto)
endif()

if (MCPROTO_ENABLE_TESTS)
    include(FetchContent)

    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2)
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)

    FetchContent_MakeAvailable(googletest)

    add_executable(mcproto_tests ${MCPROTO_TESTS_SOURCES})
    target_link_libraries(mcproto_tests PRIVATE mcproto gtest)

    enable_testing()
endif()
