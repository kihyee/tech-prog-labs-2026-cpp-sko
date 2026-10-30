file(GLOB_RECURSE LAB5_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM LAB5_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp"
)

# игра
add_executable(lab5 main.cpp ${LAB5_SOURCES})
target_include_directories(lab5 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# демонстрация - отдельная программа со своей функцией main, собирается, если есть demo.cpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp")
    add_executable(lab5_demo demo.cpp ${LAB5_SOURCES})
    target_include_directories(lab5_demo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
