// opengl-crash-course.cpp : Defines the entry point for the application.
//
#include "opengl-crash-course.hpp"
#define PI 3.141592

using namespace std;

int width = 800;
int height = 800;

void DrawCircle()
{
	glClear( GL_COLOR_BUFFER_BIT );

#ifdef __APPLE__
	glViewport( 0, 0, 2 * width, 2 * height );
#endif

	glColor3d( 1.0, 0.0, 0.0 );

	glBegin( GL_LINE_LOOP );

	for ( int i = 0; i < 360; i = i + 2 ) {
			float x = cos( i * ( PI ) / 180 );
			float y = sin( i * ( PI ) / 180 );
			glVertex2d( x, y );
		}

	glEnd();

	glFlush();
}

#ifdef __APPLE__
int main( int argc, char** argv ) {

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( width, height );
    glutCreateWindow( "Hello OpenGL!" );

    glutDisplayFunc( DrawCircle );

    glutMainLoop();
}
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {
    glutInit( &__argc, __argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( width, height );
    glutCreateWindow( "Hello OpenGL!" );

    glutDisplayFunc( DrawCircle );

    glutMainLoop();
}
