import ctypes

global test_val
test_val = 5

def set_state(str):
    global test_val
    test_val += 1
    return "{test_val}".encode()

def get_state(str):
    global test_val
    test_val += 2
    return "{test_val}".encode()
