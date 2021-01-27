if (APPLE)
    add_executable(PA2 "SimpleScene.cpp" "wavefront_obj.cpp")

    target_link_libraries(PA2 "-framework OpenGL")
    target_link_libraries(PA2 "-framework GLUT")
endif()

if (MSVC)
    add_executable(PA2 WIN32 "SimpleScene.cpp" "wavefront_obj.cpp")

    target_link_libraries(PA2 ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES})
endif()
