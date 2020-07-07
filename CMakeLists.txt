
# set required CMake version
cmake_minimum_required(VERSION 3.2)

# set project name / configuere CMake internals
project(homework_0 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})


# create config file
configure_file(version.h.in version.h)

# create binary file from source
add_executable(homework_0 main.cpp)

# create library
add_library(homework_0_library lib.cpp)

# copy lib to binary file
target_include_directories(homework_0_library
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# set project properties
set_target_properties(homework_0 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(homework_0 PRIVATE
    homework_0_library
)


##########################################################################################
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
