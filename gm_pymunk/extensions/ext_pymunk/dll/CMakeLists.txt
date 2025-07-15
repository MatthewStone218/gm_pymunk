cmake_minimum_required(VERSION 3.14)
project(gmPymunk)

# pybind11 추가
add_subdirectory(extern/pybind11)

# 소스 파일
set(SOURCE_FILES
    src/dllmain.cpp
    src/pch.cpp
)

# Python 경로 설정
set(PYTHON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/python/include")
set(PYTHON_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/extern/python/python311.lib")

# DLL 생성
add_library(gmPymunk SHARED ${SOURCE_FILES})

# 인클루드 디렉토리
target_include_directories(gmPymunk PRIVATE
    ${PYTHON_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/pybind11/include
)

# 링커 설정
target_link_libraries(gmPymunk PRIVATE
    ${PYTHON_LIBRARY}
    pybind11::embed
)

# 전처리 헤더 (선택)
target_precompile_headers(gmPymunk PRIVATE src/pch.h)
