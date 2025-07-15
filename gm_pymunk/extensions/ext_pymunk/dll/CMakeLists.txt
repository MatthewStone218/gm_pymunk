cmake_minimum_required(VERSION 3.14)
project(gmPymunk)

add_subdirectory(extern/pybind11)

set(SOURCE_FILES
    src/dllmain.cpp
)

add_library(gmPymunk SHARED ${SOURCE_FILES})
target_link_libraries(gmPymunk PRIVATE pybind11::embed)
