cmake_minimum_required(VERSION 3.13.0...3.26)
project(TND004-Lab-4 VERSION 1.0.0 DESCRIPTION "TND004 Lab 4" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Lab4a code4a/edge.h code4a/digraph.h code4a/digraph.cpp code4a/main.cpp 
                     code4a/digraph1.txt code4a/digraph1_test_run.txt code4a/digraph2.txt code4a/digraph2_test_run.txt)
add_executable(Lab4b code4b/edge.h code4b/dsets.h code4b/dsets.cpp 
                     code4b/graph.h code4b/graph.cpp code4b/main.cpp 
					 code4b/graph1.txt code4b/graph1_test_run.txt code4b/graph2.txt code4b/graph2_test_run.txt)

enable_warnings(Lab4a)
enable_warnings(Lab4b)