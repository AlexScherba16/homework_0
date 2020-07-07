# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()



# set required CMake version
cmake_minimum_required(VERSION 3.2)

# set project name / configuere CMake internals
project(homework_0 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# search GoogleTest libs
# find_package(GTest REQUIRED)

# create config file
configure_file(version.h.in version.h)

# create binary file from source
add_executable(homework_0 main.cpp)

# create library
add_library(homework_0_library lib.cpp)

# create test binary file
add_executable(test_version test_version.cpp)

# copy lib to binary file
target_include_directories(homework_0_library
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# set project properties
set_target_properties(homework_0 test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(homework_0 PRIVATE
    homework_0_library
)

target_link_libraries(test_version
    gtest_main
    homework_0_library
)

##########################################################################################
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
##########################################################################################

enable_testing()

add_test(test_version test_version)
