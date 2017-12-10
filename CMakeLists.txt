cmake_minimum_required(VERSION 3.8)
project(Project_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp scanner.cpp scanner.h token.h token.cpp FileInputFunction.cpp FileInputFunction.h filterFunction.cpp filterFunction.h parser.cpp parser.h node.cpp node.h targetLanguage.cpp targetLanguage.h)
add_executable(Project_2 ${SOURCE_FILES})