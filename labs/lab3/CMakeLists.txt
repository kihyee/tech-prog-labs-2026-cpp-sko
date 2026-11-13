cmake_minimum_required(VERSION 3.20)
project(lab3 CXX)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
        URL_HASH SHA256=d6c65aca6b1ed68e7a182f4757257b107ae403032760ed6ef121c9d55e81757d
)
FetchContent_MakeAvailable(nlohmann_json)

file(GLOB_RECURSE LAB3_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM LAB3_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/demo.cpp"
)

# игра
add_executable(lab3 src/main.cpp ${LAB3_SOURCES})
target_include_directories(lab3 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(lab3 PRIVATE nlohmann_json::nlohmann_json)

# демонстрация паттернов
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/demo.cpp")
    add_executable(lab3_demo src/demo.cpp ${LAB3_SOURCES})
    target_include_directories(lab3_demo PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    target_link_libraries(lab3_demo PRIVATE nlohmann_json::nlohmann_json)
endif()