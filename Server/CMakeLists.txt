cmake_minimum_required(VERSION 3.2)
PROJECT(MyMatrix_Server)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "g++")
include_directories(~/usr/local/lib/)

add_executable(CallNumber main.cpp)
target_link_libraries(CallNumber mysqlcppconn)

#target_link_libraries(CallNumber /usr/local/lib/libodb-mysql.so)
#target_link_libraries(CallNumber dl)

