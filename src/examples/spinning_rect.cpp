//
// Created by 유승우 on 2021/01/27.
//

#include <opengl-crash-course.hpp>

/**
 * declare global variables used in this example
 */
 static int width = 400;
 static int height = 400;
 static float spin = 30.0;

/**
 * forward declaration of functions
 */
void display();
void spinDisplay();
void mouse( int button, int state, int x, int y );
void keyboard(unsigned char k, int x, int y);
void reshape( int w, int h );

#ifdef __APPLE__
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Spinning Rect");
    glutDisplayFunc(display);
    glutIdleFunc(spinDisplay);

    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
}
#endif

#ifdef _MSC_VER
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Spinning Rect");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
#endif
void display(void) {
#ifdef __APPLE__
    glViewport(0, 0, 2 * width, 2 * height);
#endif
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glRotatef(spin, 0.0, 0.0, 1.0);
        glColor3f(1.0, 1.0, 1.0);
        glRectf(-0.5, -0.5, 0.5, 0.5);
        glPopMatrix();

        glutSwapBuffers();
}

void spinDisplay() {
    spin += 2.0f;
    if (spin > 360.0f)
        spin -= 360.0f;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay);
            break;  // watch out fall-through
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
    }
}

void keyboard(unsigned char k, int x, int ) {
    if ((k == 'q') || (k == 'Q')) {
        exit(EXIT_SUCCESS);
    }
}

void reshape(int w, int h) {
    return;
}