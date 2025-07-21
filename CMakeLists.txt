cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ExamSchedulingSystem)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target and include all source files
add_executable(main
    main.cpp
    scheduler.cpp
    seating.cpp
    utils.cpp
) 