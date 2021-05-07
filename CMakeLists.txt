cmake_minimum_required(VERSION 3.10)

project(structure)

# Standard set to 17 to have mandatory RVO
set(CMAKE_CXX_STANDARD 17)


# EXECUTABLE SECTION
add_executable(mainEntry main.cpp)
target_include_directories(mainEntry PRIVATE include)
# Class A is not a library: its source file needs to be included in the target sources
target_sources(mainEntry PRIVATE src/fc_scara.cpp
                                 src/fc_svg.cpp
                                 src/pistone.cpp
                                 src/svg.cpp
                                 src/fc_machine.cpp
                                 )
target_link_libraries(mainEntry)

# TESTS SECTION
# Basically makes CMake read the CMakeLists.txt file contained in tests
add_subdirectory(tests)



