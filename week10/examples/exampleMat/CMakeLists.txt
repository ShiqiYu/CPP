cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)

project(matexample)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories( ${OpenCV_INCLUDE_DIRS} )

# Declare the executable target built from your sources
add_executable(matexample matexample.cpp)

# Link your application with OpenCV libraries
target_link_libraries(matexample PRIVATE ${OpenCV_LIBS})
