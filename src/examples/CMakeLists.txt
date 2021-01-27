cmake_minimum_required (VERSION 3.8)

if (APPLE)
    add_executable(spinning_rect "spinning_rect.cpp")

    target_link_libraries(spinning_rect "-framework OpenGL")
    target_link_libraries(spinning_rect "-framework GLUT")
endif(APPLE)

if (MSVC)
    add_executable(spinning_rect WIN32 "spinning_rect.cpp")

    target_link_libraries(spinning_rect ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} )
    target_link_libraries(spinning_rect ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} )
endif(MSVC)