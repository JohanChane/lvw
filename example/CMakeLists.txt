cmake_minimum_required(VERSION 3.12)
project(lvw_example)

add_library(lvw_example
    src/event_handler_usage.cpp
    src/example.cpp
    src/my_ui_creator.cpp
    src/setter_usage.cpp
    src/timer_usage.cpp
)

target_include_directories(lvw_example PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(lvw_example
    lvw
    lvgl
)
