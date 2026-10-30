cmake_minimum_required(VERSION 3.20)
project(lab3 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем исходные файлы игровой логики
file(GLOB_RECURSE LAB3_SOURCES "src/*.cpp")

# Исключаем файлы точек входа, чтобы они не конфликтовали при линковке
list(REMOVE_ITEM LAB3_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/demo.cpp"
)

# созд библиотеку
add_library(lab3_lib ${LAB3_SOURCES})
target_include_directories(lab3_lib PUBLIC include)

# игра
add_executable(lab3_game src/main.cpp)
target_link_libraries(lab3_game PRIVATE lab3_lib)

add_executable(lab3_demo src/demo.cpp)
target_link_libraries(lab3_demo PRIVATE lab3_lib)