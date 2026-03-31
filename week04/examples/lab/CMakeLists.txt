cmake_minimum_required(VERSION 3.10)

project(main)

aux_source_directory(./src DIR_SRCS)

include_directories(include)

add_executable(main ${DIR_SRCS})
