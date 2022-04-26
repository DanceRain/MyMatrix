cmake_minimum_required(VERSION 3.2)
PROJECT(MyMatrix_Server)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "g++")
set(BOOST_ROOT "/usr/local/include/boost/")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED COMPONENTS json)
find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRCLIST)
add_library(lib SHARED ${SRCLIST})
add_executable(CallNumber main.cpp)

include_directories(${Boost_INCLUDE_DIRS})
set(DEP_LIBS
        OpenSSL::Crypto OpenSSL::SSL  # modern
        #${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY}  # old style
        )
target_link_libraries(CallNumber  ${Boost_LIBRARIES} lib mysqlcppconn OpenSSL::SSL ${DEP_LIBS})





















#include_directories("./src")
#FIND_PACKAGE(Threads REQUIRED)
#SET(Boost_USE_MULTITHREADED ON)

#aux_source_directory(./ main_src)
#add_subdirectory(src)
#add_executable(CallNumber ${main_src})
#target_link_libraries(CallNumber src)
#target_link_libraries(CallNumber mysqlcppconn boost_thread boost_json boost_system ${CMAKE_THREAD_LIBS_INIT})


#target_link_libraries(CallNumber /usr/local/lib/libodb-mysql.so)
#target_link_libraries(CallNumber dl)

