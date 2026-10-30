file(GLOB_RECURSE LAB2_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM LAB2_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp"
)

# игра
add_executable(lab2 main.cpp ${LAB2_SOURCES})
target_include_directories(lab2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# демонстрация - отдельная программа со своей функцией main, собирается, если есть demo.cpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp")
    add_executable(lab2_demo demo.cpp ${LAB2_SOURCES})
    target_include_directories(lab2_demo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
