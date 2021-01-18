cmake_minimum_required (VERSION 3.8)

add_executable(julia_set_PA1 "julia_set_PA1.cpp")
add_executable(julia_set_ref "julia_set_ref.cpp")

if (APPLE)
    target_link_libraries(julia_set_ref "-framework OpenGL")
    target_link_libraries(julia_set_ref "-framework GLUT")

    target_link_libraries(julia_set_PA1 "-framework OpenGL")
    target_link_libraries(julia_set_PA1 "-framework GLUT")
endif()