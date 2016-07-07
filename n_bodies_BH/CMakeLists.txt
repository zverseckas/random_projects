cmake_minimum_required(VERSION 3.3)
project(n_bodies_BH)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp Quadrant.cpp Quadrant.h Body.cpp Body.h Simulator.cpp Simulator.h)
add_executable(n_bodies_BH ${SOURCE_FILES})

set(INCLUDE_DIRECTORIES "/usr/include/smfl")
set(EXECUTABLE_NAME "n_bodies_BH")

# Detect and add SFML
set(CMAKE_MODULE_PATH "/home/zilvinas/ClionProjects/n_bodies_BH/SFML-2.3.2/share/SFML/cmake/Modules")
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()