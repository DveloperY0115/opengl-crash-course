// opengl-crash-course.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <GL/freeglut.h>

void CheckError(char* s) {
	GLenum error = glGetError();
	if (error) {
		printf("%s in %s\n", gluErrorString(error), s);
	}
}

// TODO: Reference additional headers your program requires here.
