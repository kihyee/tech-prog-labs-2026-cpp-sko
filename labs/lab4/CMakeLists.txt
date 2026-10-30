file(GLOB_RECURSE LAB4_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM LAB4_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp"
)

# игра
add_executable(lab4 main.cpp ${LAB4_SOURCES})
target_include_directories(lab4 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# демонстрация - отдельная программа со своей функцией main, собирается, если есть demo.cpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp")
    add_executable(lab4_demo demo.cpp ${LAB4_SOURCES})
    target_include_directories(lab4_demo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
