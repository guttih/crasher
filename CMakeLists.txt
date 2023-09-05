cmake_minimum_required(VERSION 3.10)

project(crasher)

include(CTest)
enable_testing()

# Add the executable that uses your class
add_executable(crasher 
    src/base.cpp
    src/main.cpp 
    src/Version.cpp 
    src/Output.cpp
    src/Stopwatch.cpp
    src/Options.cpp
    )

# Set include directories
target_include_directories(crasher PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Optionally, set C++ standard version