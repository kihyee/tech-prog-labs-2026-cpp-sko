file(GLOB_RECURSE LAB7_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM LAB7_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp"
)

# игра
add_executable(lab7 main.cpp ${LAB7_SOURCES})
target_include_directories(lab7 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# демонстрация - отдельная программа со своей функцией main, собирается, если есть demo.cpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp")
    add_executable(lab7_demo demo.cpp ${LAB7_SOURCES})
    target_include_directories(lab7_demo PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
