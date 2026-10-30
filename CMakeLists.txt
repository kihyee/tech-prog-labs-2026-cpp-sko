cmake_minimum_required(VERSION 3.20)

project(tech_prog_labs_2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    # исходники в UTF-8, иначе русские строки сломаются при компиляции
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(labs/lab2)
add_subdirectory(labs/lab3)
add_subdirectory(labs/lab4)
add_subdirectory(labs/lab5)
add_subdirectory(labs/lab6)
add_subdirectory(labs/lab7)
