add_subdirectory(extern/pybind11)
target_link_libraries(MyDll PRIVATE pybind11::embed)