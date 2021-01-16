// opengl-crash-course.cpp : Defines the entry point for the application.
//

#include "opengl-crash-course.h"
#define PI 3.141592

using namespace std;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void DrawCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// heckError("Buffer Clear");

	glColor3d(1.0, 0.0, 0.0);
	// CheckError("Set color");

	glBegin(GL_LINE_LOOP);
	// CheckError("Loop Initialization failed");

	for (int i = 0; i < 360; i = i + 2) {
			float x = cos(i * (PI) / 180);
			float y = sin(i * (PI) / 180);
			glVertex2d(x, y);
		}

	glEnd();

	glFlush();
}

int main(int argc, char** argv) {

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    /* at least OpenGL 3.3 or higher is  required */
    /*
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    */
    glfwWindowHint(GLFW_SAMPLES, 4);

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    fprintf(stderr, "OpenGL version detected: %d.%d.%d\n", major, minor, rev);

    GLFWwindow* window = glfwCreateWindow(800, 800, "GLFW Main", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set window to current context
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = GL_TRUE;

    GLenum errorCode = glewInit();
    if (GLEW_OK != errorCode) {
        std::cerr << "Error: Failed to initialize GLEW - " << glewGetErrorString(errorCode) << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    int count = 0;

    double lastTime = glfwGetTime();
    int num_frames = 0;
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        num_frames++;

        if (currentTime - lastTime >= 1.0) {
            printf("%f ms/frame %d fps \n", 1000.0 / double(num_frames), num_frames);
            num_frames = 0;
            lastTime = currentTime;
        }

        DrawCircle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // control reaches here only if user press a button to finish
    glfwTerminate();
}
