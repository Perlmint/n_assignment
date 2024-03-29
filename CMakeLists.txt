cmake_minimum_required(VERSION 3.2)
project(assignments)

add_executable(assignment1 assignment1/main.cpp)
target_compile_features(assignment1 PRIVATE
  cxx_generalized_initializers
  cxx_range_for)

add_executable(assignment2
  assignment2/main.cpp
  assignment2/utils.hpp
  assignment2/stack.hpp
  assignment2/heap.hpp
  assignment2/vector.hpp)
target_compile_features(assignment2 PRIVATE
  cxx_noexcept
  cxx_range_for
  cxx_return_type_deduction)

add_library(shapelib
  shplib/dbfopen.c
  shplib/safileio.c
  shplib/shpopen.c
  shplib/shptree.c)
if(WIN32)
  target_compile_definitions(shapelib PRIVATE _CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_executable(assignment3 WIN32
  assignment3/main.cpp
  assignment3/app.hpp
  assignment3/app.cpp
  assignment3/World.cpp
  assignment3/World.hpp
  assignment3/Path.cpp
  assignment3/Path.hpp
  assignment3/point.hpp
  assignment3/Node.hpp)
target_link_libraries(assignment3 shapelib D2d1 Dwrite)
target_compile_features(assignment3 PRIVATE
  cxx_nullptr
  cxx_uniform_initialization
  cxx_range_for)
target_include_directories(assignment3
  PRIVATE shplib)
