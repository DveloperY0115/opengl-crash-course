//
// Created by 유승우 on 2021/01/16.
//

#ifndef OPENGL_CRASH_COURSE_OPENGL_HPP
#define OPENGL_CRASH_COURSE_OPENGL_HPP

#include <iostream>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

/* utility functions */
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

#endif //OPENGL_CRASH_COURSE_OPENGL_HPP
