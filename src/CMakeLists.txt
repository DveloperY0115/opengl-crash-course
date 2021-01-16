# CMakeList.txt : CMake project for opengl-crash-course, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (opengl-crash-course "opengl-crash-course.cpp")
if (APPLE)
    target_link_libraries(opengl-crash-course "-framework OpenGL")
    target_link_libraries(opengl-crash-course "${BREW_DIRS}/${GLFW_LIB_DIRS}")
    target_link_libraries(opengl-crash-course "${BREW_DIRS}/${GLEW_LIB_DIRS}")
endif()
    # add_executable (julia "julia_set.cpp")

# TODO: Add tests and install targets if needed.
