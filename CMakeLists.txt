
# set required CMake version
cmake_minimum_required(VERSION 3.2)

# set project name / configuere CMake internals
project(homework_0 VERSION 1.2.3)

# create binary file from source
add_executable(homework_0 main.cpp)

# set project properties
set_target_properties(homework_0 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

