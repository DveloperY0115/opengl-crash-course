#include "opengl-crash-course.hpp"
#include <cmath>
#include <complex>

struct Extent {
    float l, r, b, t;
};

// forward declaration of callbacks
static void display();
static void keyboard_button_Callback( GLFWwindow* window, int key, int scancode, int action, int mods );
static void mouse_cursor_pos_Callback( GLFWwindow* window, double xpos, double ypos );
static void mouse_button_Callback( GLFWwindow* window, int button, int action, int mods );

std::complex<float> c( 0.109f, 0.603f );
Extent world{  -1, 1, -1, 1  };
int width = 512;
int height = 512;
bool doJuliaSet = true;
constexpr int maxIterations = 256;

int main( int argc, char** argv ) {

    // set GLFW error callback function
    glfwSetErrorCallback( error_callback );

    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwWindowHint( GLFW_SAMPLES, 4 );

    int major, minor, rev;
    glfwGetVersion( &major, &minor, &rev );
    fprintf( stderr, "OpenGL version detected: %d.%d.%d\n", major, minor, rev );

    GLFWwindow* window = glfwCreateWindow( width, height, "GLFW Main", NULL, NULL );
    if ( !window ) {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);

    // set window to current context
    glfwMakeContextCurrent( window );

    // set GLFW user input callbacks
    glfwSetKeyCallback( window, keyboard_button_Callback );
    glfwSetCursorPosCallback( window, mouse_cursor_pos_Callback );
    glfwSetMouseButtonCallback( window, mouse_button_Callback );

    glewExperimental = GL_TRUE;

    // set swap interval to 1
    glfwSwapInterval( 1 );

    // main loop
    while( !glfwWindowShouldClose( window ) ) {

        display();
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // control reaches here only if when user presses exit button
    glfwTerminate();
    exit( EXIT_SUCCESS );
}

void julia( std::complex<float> p, std::complex<float> c, int& i, float& r ) {
	float rSqr;
	for ( i = 0; i < maxIterations; i++ ) {
        p = p * p + c;
        rSqr = std::norm( p );
        if ( rSqr > 4 )
            break;
    }
	r = sqrt( rSqr );
}

void mandelbrot( std::complex<float> c, int& i, float& r ) {
    float rSqr;
    std::complex<float> p( 0.f, 0.f );
    for( i = 0; i < maxIterations; i++ ) {
        p = p * p + c;
        rSqr = std::norm( p );
        if ( rSqr > 4 )
            break;
    }
    r = sqrt( rSqr );
}

void initialize_screen() {
    // clear screen
    glClearColor(0, 0, 1, 0);
    glClear( GL_COLOR_BUFFER_BIT );

    // set up the viewing matrices
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( world.l, world.r, world.b, world.t ); // what's world? -> setting up camera
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void display() {
    initialize_screen();

    // loop over the pixels on the screen
    float delta = ( world.r - world.l ) / float( width );
    for( int j = 0; j < height; j++ ) {
        for( int i = 0; i < width; i++ ) {
            // convert pixel location to world coordinates
            float x = world.l + i * delta;
            float y = world.b + j * delta;

            // test for convergence
            int its;
            float R;
            std::complex<float> p( x, y );
            if( doJuliaSet )
                julia( p, c, its, R );
            else
                mandelbrot( p, its, R );

            // turn iterations and radius to color
            if( its == 256 )
                glColor3d( 0, 0, 0 );
            else {
                float r = R / 3.f;
                float g = its / 128.f;
                float b = R / float( its + 1 );
                glColor3d( r, g, b );
            }

            // draw polygon
            glBegin( GL_POLYGON );
            glVertex2d( x, y );
            glVertex2d( x, y + delta );
            glVertex2d( x + delta, y + delta );
            glVertex2d( x + delta, y );
            glEnd();
        }
        glFlush();
    }
}

float xScreenToWorld( float scrX ) {
    return ( ( world.r - world.l ) * scrX / float( width ) ) + world.l;
}

float yScreenToWorld( float scrY ) {
    return ( ( world.t - world.b ) * ( 1 - scrY / float( height ) ) ) + world.b;
}


void keyboard_button_Callback( GLFWwindow* window, int key, int scancode, int action, int mods ) {

    // Press EXIT
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose( window, GL_TRUE );

    // Press R
    if ( key == GLFW_KEY_R && action == GLFW_PRESS ) {
        if ( doJuliaSet ) {
            // return to initial position
            c = std::complex<float>( 0.109f, 0.603f );
            world.l = -1;
            world.r = 1;
            world.b = -1;
            world.t = 1;
        } else {
            world.l = -2;
            world.r = 2;
            world.b = -2;
            world.t = 2;
        }
        display();
    }

    // Press C
    if ( key == GLFW_KEY_C && action == GLFW_PRESS ) {
        // set c = (0,0)
        c = std::complex<float>( 0.f, 0.f );
        world.l = -1;
        world.r = 1;
        world.b = -1;
        world.t = 1;
        display();
    }

    // Press Space
    if ( key == GLFW_KEY_SPACE && action == GLFW_PRESS ) {
        doJuliaSet = !doJuliaSet;
        display();
    }
}

static void mouse_cursor_pos_Callback( GLFWwindow* window, double xpos, double ypos ) {
    // do nothing
}

static void mouse_button_Callback( GLFWwindow* window, int button, int action, int mods ) {

    double mx, my;
    glfwGetCursorPos(window, &mx, &my);

    float x = xScreenToWorld( mx );
    float y = yScreenToWorld( my );

    float dx = ( world.r - world.l );
    float dy = ( world.t - world.b );

    if ( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ) {
        world.l = x - dx / 4;
        world.r = x + dx / 4;
        world.b = y - dy / 4;
        world.t = y + dy / 4;
        display();
    } else if ( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS ) {
        world.l = x - dx;
        world.r = x + dx;
        world.b = y - dy;
        world.t = y + dy;
        display();
    }
}
