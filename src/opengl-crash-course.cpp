// opengl-crash-course.cpp : Defines the entry point for the application.
//

#include "opengl-crash-course.h"
#define PI 3.141592

using namespace std;

void DrawCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	CheckError("Buffer Clear");

	glColor3d(1.0, 0.0, 0.0);
	CheckError("Set color");

	glBegin(GL_LINE_LOOP);
	CheckError("Loop Initialization failed");

	for (int i = 0; i < 360; i = i + 2) {
			float x = cos(i * (PI) / 180);
			float y = sin(i * (PI) / 180);
			glVertex2d(x, y);
		}

	glEnd();

	glFlush();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	CheckError("Failed to initialize GLUT");

	glutCreateWindow("First Screen");
	CheckError("Failed to create window");
	glutDisplayFunc(DrawCircle);
	glutMainLoop();
}
