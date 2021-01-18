# CMakeList.txt : CMake project for opengl-crash-course, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add subdirectory
add_subdirectory(PA1)

# Build opengl-crash-course.cpp
add_executable(opengl-crash-course "opengl-crash-course.cpp")
target_link_libraries(opengl-crash-course "-framework OpenGL")
target_link_libraries(opengl-crash-course "-framework GLUT")

# TODO: Add tests and install targets if needed.
