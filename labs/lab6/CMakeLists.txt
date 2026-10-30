file(GLOB_RECURSE LAB6_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM LAB6_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp"
)

# игра
add_executable(lab6 main.cpp ${LAB6_SOURCES})
target_include_directories(lab6 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# демонстрация - отдельная программа со своей функцией main, собирается, если есть demo.cpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp")
    add_executable(lab6_demo demo.cpp ${LAB6_SOURCES})
    target_include_directories(lab6_demo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
