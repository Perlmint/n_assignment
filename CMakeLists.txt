project(assignments)

add_executable(assignment1 assignment1/main.cpp)
add_executable(assignment2 assignment2/main.cpp)

add_library(shapelib
  assignment3/shplib/dbfopen.c
  assignment3/shplib/safileio.c
  assignment3/shplib/shpopen.c
  assignment3/shplib/shptree.c)
add_executable(assignment3
  assignment3/main.cpp
  assignment3/World.cpp
  assignment3/World.hpp
  assignment3/Path.cpp
  assignment3/Path.hpp
  assignment3/Node.hpp)
target_link_libraries(assignment3 shapelib)
target_compile_features(assignment3 PRIVATE cxx_range_for)
