cmake_minimum_required(VERSION 3.5.1)

#project name
project(marketdecision)

#creates the variable EXEC and sets it to main
set(EXEC main)

#set the C++14 standard
set(CMAKE_CXX_STANDARD 14)

#set Build Type
set(CMAKE_BUILD_TYPE Debug)

#set Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#set includes
include_directories("includes/")

#configure source files
file(GLOB SOURCES "src/*.cpp" "src/*.c")

#set flags -Wall -lpthread etc
add_definitions("-Wall")

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})
