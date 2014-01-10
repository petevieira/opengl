// C includes
#include <iostream>
#include <stdio.h>
// Eigen includes
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
// OpenGL includes
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GlCamera.h"
#include "glutils.h"

double d[9] = {1, 2, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};

bool* keyStates = new bool[256]; // Create array of bools for key states (true=up/false=down)
bool* keySpecialStates = new bool[256]; // Create array of bools for special key states (true=up/false=down)

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0};
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0};
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
GLfloat blankMaterial[] = {0.0, 0.0, 0.0};
GLfloat mShininess[] = {128};
bool diffuse = false;
bool emissive = false;
bool specular = false;

GLuint texture;
GlCamera camera;

typedef enum {
	MOTION_NULL=0,
	MOTION_ROTATE,
	MOTION_PAN,
	MOTION_ZOOM
} motion_type_t;

Eigen::Vector2f mousePos(0,0);

motion_type_t motion_type = MOTION_NULL;

bool movingUp;
float yLocation = 0.0f;
float yRotAngle = 0.0f;

void _keyOperations(void)
{

}

void _mouse(int button, int state, int x, int y)
{
    std::cerr << "button: " << button << std::endl;
	// If button pressed, get x,y and toggle motion type
	if(GLUT_DOWN == state) {
       // origin_x = x;
       // origin_y = y;

		switch(button) {
		case GLUT_LEFT_BUTTON:
            std::cerr << "now in rotate mode\n";
			motion_type = MOTION_ROTATE;
			break;
            std::cerr << "now in zoom mode\n";
		case GLUT_MIDDLE_BUTTON:
			motion_type = MOTION_ZOOM;
			break;
        case GLUT_RIGHT_BUTTON:
            std::cerr << "now in pan mode\n";
			motion_type = MOTION_PAN;
			break;
        case 3:
            motion_type = MOTION_ZOOM;
            break;
        case 4:
            motion_type = MOTION_ZOOM;
            break;
		}
    }
	else {
        std::cerr << "not in a mouse mode\n";
		motion_type = MOTION_NULL;
	}

}

void _motion(int x, int y)
{
    float dx=x-mousePos.x();
    float dy=y-mousePos.y();
	switch(motion_type) {
	case MOTION_ROTATE:
        std::cerr << "Rotating view\n";
        camera.rotate(x, y);
		break;
    case MOTION_PAN:
        std::cerr << "mousePos: " << mousePos.x() << ", " << mousePos.y() << "\n"
                  << "dx, dy: " << dx << ", " << dy << std::endl;
        camera.pan(dx,dy,0);
		break;
	case MOTION_ZOOM:
        camera.zoom(dy);
        break;
	}
    mousePos << x, y;
    camera.setMousePosition(mousePos);

}

void _passiveMotion(int x, int y)
{
    mousePos.x() = x;
    mousePos.y() = y;
   // std::cerr << "x,y: " << x << ", " << y << std::endl;
}

void renderPrimitive(void)
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

void _init()
{
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity(); // Load identity matrix to reset our drawing locations
    // Camera center, aim at, up vector
    gluLookAt(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8]);
    Eigen::Vector3f p, t, u;
    p << d[0], d[1], d[2];
    t << d[3], d[4], d[5];
    u << d[6], d[7], d[8];
    std::cerr << "Setting camera init pose\n";
    //camera.setPose(p, t, u);
    camera.setPose();
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    std::cerr << "main_modelview:\n" << glutils::glToMat4(m) << "\n";
}

void _lighting()
{
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

void _display(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _keyOperations();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Make background red
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

    glScalef(1.0, 1.0, 1.0);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glutSolidCube(2.0f);
    glutSwapBuffers(); // Swap OpenGL buffers and send to monitor
}

void _reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set viewport to size of window
    camera.setViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix so we can manipulate scene
    glLoadIdentity(); // Reset projection matrix to identity to avoid artifacts
    // Set field of view, aspect ratio and min and max distances to draw objects
    gluPerspective(60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
    glTranslatef(.1,.1,.1);
    glMatrixMode(GL_MODELVIEW); // Switch back to model view matrix to draw shapes correctly
}

void _keyPressed(unsigned char key, int x, int y)
{
    switch(key) {
    case 27: // escape key
        glutDestroyWindow(glutGetWindow());
        exit(0);
        break;
    case 'w':
        std::cerr << "Move up\n";
        camera.pan(0, 1, 0);
        break;
    case 's':
        std::cerr << "Move down\n";
        camera.pan(0, -1, 0);
        break;
    case 'a':
        std::cerr << "Move left\n";
        camera.pan(-1, 0, 0);
        break;
    case 'd':
        std::cerr << "Move right\n";
        camera.pan(1, 0, 0);
        break;
    case '=':
        std::cerr << "Zoom out\n";
        camera.zoom(.1);
        break;
    case '-':
        std::cerr << "Zoom in\n";
        camera.zoom(-.1);
        break;
    case 'i':
    {
        Eigen::AngleAxisf a(5*M_PI/180, Eigen::Vector3f::UnitY());
        Eigen::Quaternionf q(a);
        camera.rotate(q);
        break;
    }
    case 'k':
        camera.rotate(1, 0, 0);
        break;
    case 'j':
        camera.rotate(0, -1, 0);
        break;
    case 'l':
        camera.rotate(0, 1, 0);
        break;
    case 'u':
        camera.rotate(0, 0, 1);
        break;
    case 'o':
        camera.rotate(0, 0, -1);
        break;
    case 'n':
    {
        GLfloat m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        std::cerr << "pre modelview:\n" << glutils::glToMat4(m) << "\n";
        camera.pan(1, 0, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        std::cerr << "post modelview:\n" << glutils::glToMat4(m) << "\n";
        break;
    }
    case 'm': {
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(0, 0, -.1);
        glutPostRedisplay();
        GLfloat m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        std::cerr << "\nmodelview:\n" << glutils::glToMat4(m);
        break;
    }
    case ',': {
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(0, 0, .1);
        glutPostRedisplay();
        GLfloat m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        std::cerr << "modelview:\n" << glutils::glToMat4(m) << "\n";
        std::cerr << "raw modelview\n"
                  << m[0] << m[4] << m[8] << m[12] << "\n"
                  << m[1] << m[5] << m[9] << m[13] << "\n"
                  << m[2] << m[6] << m[10] << m[14] << "\n"
                  << m[3] << m[7] << m[11] << m[15] << "\n";
        break;
    }
    }


}

void _keyReleased(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}

void _keySpecialPressed(int key, int x, int y)
{
    keySpecialStates[key] = true;
}

void _keySpecialReleased(int key, int x, int y)
{
    keySpecialStates[key] = false;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Set up basic display buffer (double buffered)
    glutInitWindowSize(500, 500); // Set the width and height of the window
    glutInitWindowPosition(100, 100); // Set the position of the window
    glutCreateWindow("My first OpenGL window"); // Set title of the window

    _init();

	// Tell GLUT which member functions to use for each action
    glutDisplayFunc(_display); // dislay stuff
    glutIdleFunc(_display); // idle operations
    glutReshapeFunc(_reshape); // reshape the window
    glutKeyboardFunc(_keyPressed); // key presses
    glutKeyboardUpFunc(_keyReleased); // key releases
    glutSpecialFunc(_keySpecialPressed); // special key presses
    glutSpecialUpFunc(_keySpecialReleased); // special key releases
    glutMouseFunc(_mouse); // mouse events
    glutMotionFunc(_motion); // mouse motion events
    glutPassiveMotionFunc(_passiveMotion); // passive mouse motion events

    glutMainLoop(); // Main loop
}


