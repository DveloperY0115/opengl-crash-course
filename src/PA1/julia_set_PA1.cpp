//
// Created by 유승우 on 2021/01/16.
//

#include "opengl-crash-course.hpp"

#include <cmath>
#include <complex>

struct Extent {
    float l, r, b, t;
};

// glut callbacks
void display();
void keyboard( unsigned char k, int x, int y );
void mouse( int button, int state, int x, int y );
void reshape( int w, int h );

Extent world{ -1, 1, -1, 1 };
std::complex<float> c( 0.109f, 0.603f );
int width = 512, height = 512;
bool doJuliaSet = true;
constexpr int maxIterations = 256;


//------------------------------------------------------------------------------
#ifdef __APPLE__
int main( int argc, char *argv[] ) {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( width, height );
    glutCreateWindow( "Fractal Land" );
    glutDisplayFunc( display );
    glutMouseFunc( mouse );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    glutMainLoop();
}
#endif

#ifdef _MSC_VER
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {
    glutInit( &__argc, __argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( width, height );
    glutCreateWindow( "Fractal Land" );
    glutDisplayFunc( display );
    glutMouseFunc( mouse );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    glutMainLoop();
}
#endif

//------------------------------------------------------------------------------
void julia( std::complex<float> p, std::complex<float> c, int &i, float &r ) {
    float rSqr;
    for( i = 0; i < maxIterations; i++ ) {
        p = p * p + c;
        rSqr = std::norm( p );
        if( rSqr > 4 )
            break;
    }
    r = sqrt( rSqr );
}

//------------------------------------------------------------------------------
void mandelbrot( std::complex<float> c, int &i, float &r ) {
    float rSqr;
    std::complex<float> p( 0.f, 0.f );
    for( i = 0; i < maxIterations; i++ ) {
        p = p * p + c;
        rSqr = std::norm( p );
        if( rSqr > 4 )
            break;
    }
    r = sqrt( rSqr );
}

void display() {
    // Clear the screen
    glClearColor( 0, 0, 1, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

#ifdef __APPLE__
    /*
     * Resolution of Retina Display = 4 * regular display
     * Double the width and height of the viewport on macOS
     */
    glViewport(0, 0, 2 * width, 2 * height);
#endif

    // Setup the viewing matrices
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( world.l, world.r, world.b, world.t );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // loop over the pixels on the screen
    // NOTE: In this case, we need two delta for scaling the window and viewport
    float delta_x = ( world.r - world.l ) / float( width );
    float delta_y = ( world.t - world.b ) / float( height );
    for( int j = 0; j < height; j++ ) {
        for( int i = 0; i < width; i++ ) {
            // convert pixel location to world coordinates
            float x = world.l + i * delta_x;
            float y = world.b + j * delta_y;

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
            glVertex2d( x, y + delta_y );
            glVertex2d( x + delta_x, y + delta_y );
            glVertex2d( x + delta_x, y );
            glEnd();
        }
        glFlush();
    }
}

//-----------------------------------------------------------------------------
void keyboard( unsigned char key, int x, int y ) {
    if ( ( key == 'r' ) || ( key == 'R' ) ) {
        if( doJuliaSet ) {
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
    } else if( ( key == 'c' ) || ( key == 'C' ) ) {
        // set c = (0,0)
        c = std::complex<float>( 0.f, 0.f );
        world.l = -1;
        world.r = 1;
        world.b = -1;
        world.t = 1;
        display();
    } else if( key == ' ' ) {
        doJuliaSet = !doJuliaSet;
        display();
    } else if ( ( key == 'q' ) || ( key == 'Q' ) ) {
        exit(EXIT_SUCCESS);
    }
}

//------------------------------------------------------------------------------
float xScreenToWorld( float scrX ) {
    return ( ( world.r - world.l ) * scrX / float( width ) ) + world.l;
}

//------------------------------------------------------------------------------
float yScreenToWorld( float scrY ) {
    return ( ( world.t - world.b ) * ( 1 - scrY / float( height ) ) ) + world.b;
}


//-----------------------------------------------------------------------------
void mouse( int button, int state, int mx, int my ) {
    float x = xScreenToWorld( mx );
    float y = yScreenToWorld( my );
    float dx = ( world.r - world.l );
    float dy = ( world.t - world.b );
    if( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) ) {
        world.l = x - dx / 4;
        world.r = x + dx / 4;
        world.b = y - dy / 4;
        world.t = y + dy / 4;
        display();
    } else if( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_DOWN ) ) {
        world.l = x - dx;
        world.r = x + dx;
        world.b = y - dy;
        world.t = y + dy;
        display();
    }
}

//------------------------------------------------------------------------------

void reshape( int w, int h ) {

    width = w;
    height = h;
    glViewport( 0, 0, w, h );

    // comment out the following fragment when doing PA1
    /*
    float cx = 0.5 * ( world.r + world.l );
    float dy = world.t - world.b;;
    world.l = cx - 0.5 * dy * w / h;
    world.r = cx + 0.5 * dy * w / h;
     */
}
