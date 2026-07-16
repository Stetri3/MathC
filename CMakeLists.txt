# CMakeList.txt: file di progetto CMake di primo livello. Eseguire la configurazione globale
# e includere qui i sottoprogetti.
#
cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(PNAME "MathC")

set(APP_NAME ${PNAME})
project (${APP_NAME})
# Includere i sottoprogetti.
add_subdirectory ("MathC")
