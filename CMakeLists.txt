cmake_minimum_required( VERSION 3.5 FATAL_ERROR )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3" )

message( "Compiler: ${CMAKE_CXX_COMPILER}" )
message( "Option: ${CMAKE_CXX_FLAGS}" )

include_directories( "." )

# Put phat directory here
include_directories( "../phat-master/include/" )

# Boost
find_package( Boost 1.5 )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable( fzz
    fzz_main.cpp
    fzz.cpp
    ) 
