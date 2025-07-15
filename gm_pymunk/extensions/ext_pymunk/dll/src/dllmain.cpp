// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include <Windows.h>
#include <pybind11/embed.h>  // py::scoped_interpreter
#include <pybind11/pybind11.h>
#include <string>
#include <cstring> // for strdup'

namespace py = pybind11;

static bool py_ready = false;
static py::object py_module;

extern "C" __declspec(dllexport) double test() {
    return 15;
}

extern "C" __declspec(dllexport) double pymunk_init() {
    if (!py_ready) {
        py::initialize_interpreter();
        py_module = py::module_::import("physics_engine");  // py에서 사용할 모듈명
        py_ready = true;
        return 1;
    }
    return 0;
}

// 문자열을 파이썬으로 전달하는 함수
extern "C" __declspec(dllexport) const char* pymunk_set(const char* msg) {
    pymunk_init();
    try {
        py_module.attr("set_state")(std::string(msg));
    }
    catch (py::error_already_set& e) {
        std::string error_msg = "[ERROR]: ";
        error_msg += e.what();
        return _strdup(error_msg.c_str());
    }

    return _strdup("Setting Succeeded");
}

// 파이썬에서 문자열을 받아와 char*로 반환하는 함수
extern "C" __declspec(dllexport) const char* pymunk_get(const char* msg) {
    pymunk_init();
    try {
        std::string result = py_module.attr("get_state")(msg).cast<std::string>();
        return _strdup(result.c_str());  // 메모리는 호출자가 책임져야 함
    }
    catch (py::error_already_set& e) {
        std::string error_msg = "[ERROR]: ";
        error_msg += e.what();
        return _strdup(error_msg.c_str());
    }
}
