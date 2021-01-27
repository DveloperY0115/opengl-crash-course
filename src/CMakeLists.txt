# CMakeList.txt : CMake project for opengl-crash-course, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add subdirectory
add_subdirectory(examples)
add_subdirectory(PA1)
add_subdirectory(PA2_Apple)

# Build opengl-crash-course.cpp
if (APPLE)
    add_executable(opengl-crash-course "opengl-crash-course.cpp")
    target_link_libraries(opengl-crash-course "-framework OpenGL")
    target_link_libraries(opengl-crash-course "-framework GLUT")
endif(APPLE)

if (MSVC)
    add_executable(opengl-crash-course WIN32 "opengl-crash-course.cpp")
    target_link_libraries(opengl-crash-course ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} )
    target_link_libraries(opengl-crash-course ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} )
endif(MSVC)

# TODO: Add tests and install targets if needed.
