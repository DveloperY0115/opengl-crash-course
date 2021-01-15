# CMakeList.txt : CMake project for opengl-crash-course, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (opengl-crash-course "opengl-crash-course.cpp" "opengl-crash-course.h")
add_executable (julia "julia_set.cpp")

# TODO: Add tests and install targets if needed.
