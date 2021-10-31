cmake_minimum_required(VERSION 3.12)

add_definitions(-DWITH_NEON)
#add_definitions(-DWITH_AVX2)

project(dotp)

ADD_EXECUTABLE(dotp main.cpp matoperation.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message("OpenMP found.")
    target_link_libraries(dotp PUBLIC OpenMP::OpenMP_CXX)
endif()

