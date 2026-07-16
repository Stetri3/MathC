cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${APP_NAME} "testing.cpp"
"linalg/vectors.hpp" "linalg/vector_lists.h"
"linalg/vec_utils.h")