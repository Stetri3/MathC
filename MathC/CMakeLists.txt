cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${APP_NAME} "testing.cpp"
"linalg/vectors.hpp" "linalg/vector_lists.h"
"linalg/vec_utils.h" "calculus/duals.hpp"
"linalg/vector_cond.hpp" "func/func.hpp"
"func/funcs.hpp" "func/funcs_decl.h"
"utils/main_utils.hpp" "utils/type_utils.hpp"
"func/op_def.h" "func/runtime/f.hpp"
"func/op.hpp" "calculus/field_funcs.hpp")

target_precompile_headers(${APP_NAME} PRIVATE "utils/main_utils.hpp")