cmake_minimum_required(VERSION 3.14)
project(gmPymunk)

# pybind11 추가 (서브모듈 또는 수동 포함 경로)
add_subdirectory(extern/pybind11)

# 소스 파일 명시
set(SOURCE_FILES
    src/dllmain.cpp
    src/pch.cpp  # pch를 쓰고 있다면 포함
)

# DLL 생성
add_library(gmPymunk SHARED ${SOURCE_FILES})

# pybind11 임베딩 링크
target_link_libraries(gmPymunk PRIVATE pybind11::embed)

# 전처리 헤더 설정 (dllmain.cpp에서 pch.h를 include 한다면)
target_precompile_headers(gmPymunk PRIVATE src/pch.h)
