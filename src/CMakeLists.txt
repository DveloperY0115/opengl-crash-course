# CMakeList.txt : CMake project for opengl-crash-course, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (opengl-crash-course "opengl-crash-course.cpp")
add_executable (julia_set "julia_set.cpp")
add_executable(julia_set_ref "julia_set_ref.cpp")
if (APPLE)
    target_link_libraries(opengl-crash-course "-framework OpenGL")
    target_link_libraries(opengl-crash-course "${BREW_DIRS}/${GLFW_LIB_DIRS}")
    target_link_libraries(opengl-crash-course "${BREW_DIRS}/${GLEW_LIB_DIRS}")

    target_link_libraries(julia_set "-framework OpenGL")
    target_link_libraries(julia_set "${BREW_DIRS}/${GLFW_LIB_DIRS}")
    target_link_libraries(julia_set "${BREW_DIRS}/${GLEW_LIB_DIRS}")

    target_link_libraries(julia_set_ref "-framework OpenGL")
    target_link_libraries(julia_set_ref "-framework GLUT")
    # target_link_libraries(julia_set_ref "${BREW_DIRS}/${GLFW_LIB_DIRS}")
    # target_link_libraries(julia_set_ref "${BREW_DIRS}/${GLEW_LIB_DIRS}")
endif()

# TODO: Add tests and install targets if needed.
