// opengl-crash-course.h : Include file for standard system include files,
// or project specific include files.

#include <iostream>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

void CheckError(char* s) {
	GLenum error = glGetError();
	if (error) {
		printf("%s in %s\n", gluErrorString(error), s);
	}
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// TODO: Reference additional headers your program requires here.
