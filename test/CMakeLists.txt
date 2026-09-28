cmake_minimum_required(VERSION 3.20)

project(Proyecto0Tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ticket_tests
    test_tickets.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        target_compile_options(ticket_tests PRIVATE
            /clang:-fprofile-instr-generate
            /clang:-fcoverage-mapping
        )

        target_link_options(ticket_tests PRIVATE
            /clang:-fprofile-instr-generate
        )
    else()
        target_compile_options(ticket_tests PRIVATE
            -fprofile-instr-generate
            -fcoverage-mapping
        )

        target_link_options(ticket_tests PRIVATE
            -fprofile-instr-generate
        )
    endif()
endif()

target_include_directories(ticket_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../Proyecto0 v,fail"
)

target_link_libraries(ticket_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(ticket_tests)