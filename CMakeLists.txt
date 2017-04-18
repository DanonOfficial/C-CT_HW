cmake_minimum_required(VERSION 3.6)
project(HW_4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Calculator.h CalculatorRealisation.cpp Printer.cpp Printer.h Expression.h Parser.cpp Parser.h)
add_executable(HW_4 ${SOURCE_FILES})