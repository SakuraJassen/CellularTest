cmake_minimum_required(VERSION 3.8.2)
project(CellSim)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED graphics window system)

file(GLOB_RECURSE SOURCE ./*.cpp)

add_executable(cellsim ${SOURCE})

set_property(TARGET cellsim PROPERTY CXX_STANDARD 17)

target_link_libraries(cellsim ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
