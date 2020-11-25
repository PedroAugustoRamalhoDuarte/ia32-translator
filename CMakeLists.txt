cmake_minimum_required(VERSION 3.15)
project(ia_32_translater)

set(CMAKE_CXX_STANDARD 14)

add_executable(ia_32_translater src/main.cpp src/arquivoHandler.cpp src/preProcessador.cpp src/utils.cpp src/main.cpp src/tradutor.cpp)
add_executable(test src/utils.cpp test/utilsTest.cpp src/arquivoHandler.cpp)