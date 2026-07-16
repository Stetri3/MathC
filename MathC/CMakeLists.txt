

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Definizione della libreria principale
add_library(algebra_lib)

# Assegnazione dei sorgenti e dei moduli C++20
target_sources(algebra_lib
    PUBLIC
        FILE_SET CXX_MODULES FILES
            mathC.cppm
            calculus/calculus.cppm
            calculus/duals.cppm
            linalg/math_vec.cppm
    PRIVATE
        calculus/calculus.cpp
        calculus/duals.cpp
        linalg/math_vec.cpp
)

# Inclusione delle directory per gli header (es. debug_helper.h, linalg/vec_utils.h)
target_include_directories(algebra_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Configurazione dell'eseguibile di test
add_executable(mathc_tests testing.cpp)
target_link_libraries(mathc_tests PRIVATE algebra_lib)