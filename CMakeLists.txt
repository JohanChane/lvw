cmake_minimum_required(VERSION 3.12)
project(lvw VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option configuration
option(LVW_BUILD_EXAMPLES "Build example programs" OFF)

# Set library type (header-only library)
set(LVW_LIBRARY_TYPE INTERFACE)

# Create main library target
add_library(lvw ${LVW_LIBRARY_TYPE})

# Set library's include directories
target_include_directories(lvw ${LVW_LIBRARY_TYPE}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(fmt REQUIRED)

# Declare lvw depends on lvgl
target_link_libraries(lvw ${LVW_LIBRARY_TYPE}
    lvgl
    fmt::fmt
)

# Add header files
target_sources(lvw ${LVW_LIBRARY_TYPE}
    FILE_SET HEADERS
    BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/lvw/event_handler.hpp
        include/lvw/setter.hpp
        include/lvw/timer.hpp
        include/lvw/event_handler/event_handler.hpp
        include/lvw/setter/btn.hpp
        include/lvw/setter/checkbox.hpp
        include/lvw/setter/img.hpp
        include/lvw/setter/label.hpp
        include/lvw/setter/obj.hpp
        include/lvw/timer/timer.hpp
)

# Add example subdirectory
if(LVW_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
