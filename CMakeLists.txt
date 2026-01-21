cmake_minimum_required(VERSION 3.10)

project(mycli VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(mylib
        src/math.cpp
)
target_include_directories(mylib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(mycli
        src/main.cpp
)
target_link_libraries(mycli PRIVATE mylib)

add_executable(unit_tests
        tests/test_math.cpp
)
target_link_libraries(unit_tests PRIVATE mylib)

# Warnings: apply to both executables (and optionally the library too)
target_compile_options(mycli PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
target_compile_options(unit_tests PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
