cmake_minimum_required (VERSION 3.8)

if (APPLE)
    add_executable(julia_set_PA1 "julia_set_PA1.cpp")
    add_executable(julia_set_ref "julia_set_ref.cpp")

    target_link_libraries(julia_set_ref "-framework OpenGL")
    target_link_libraries(julia_set_ref "-framework GLUT")

    target_link_libraries(julia_set_PA1 "-framework OpenGL")
    target_link_libraries(julia_set_PA1 "-framework GLUT")
endif(APPLE)

if (MSVC)
    add_executable(julia_set_PA1 WIN32 "julia_set_PA1.cpp")
    add_executable(julia_set_ref WIN32 "julia_set_ref.cpp")

    target_link_libraries(julia_set_ref ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} )
    target_link_libraries(julia_set_PA1 ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} )
endif(MSVC)