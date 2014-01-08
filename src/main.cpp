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

double d[9] = {2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};

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

int origin_x = 0;
int origin_y = 0;
motion_type_t motion_type = MOTION_NULL;

bool movingUp;
float yLocation = 0.0f;
float yRotAngle = 0.0f;

void _keyOperations(void)
{

}

void _mouse(int button, int state, int x, int y)
{
	// If button pressed, get x,y and toggle motion type
	if(GLUT_DOWN == state) {
        origin_x = x;
        origin_y = y;

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
		}
    }
	else {
        std::cerr << "not in a mouse mode\n";
		motion_type = MOTION_NULL;
	}

}

/**
 * Rotate scene on hemisphere. Project x,y coordinates
 * onto hemisphere and then compute angle between the
 * vectors and axis to rotate about and convert to
 * quaternion. 
 */
void camera_rotate(int x, int y)
{
    GLfloat winSize[4];
    glGetFloatv(GL_VIEWPORT, winSize);
    printf("win size: %f, %f, %f, %f\n", winSize[0], winSize[1], winSize[2], winSize[3]);
    printf("origin: %d, %d\n", origin_x, origin_y);
    printf("curren: %d, %d\n", x, y);

    float r = sqrt(winSize[2]*winSize[2] + winSize[3]*winSize[3]);
    Eigen::Vector3f cur, origin;
    cur.x() = x - winSize[2]/2;
    cur.y() = y - winSize[3]/2;
    cur.z() = sqrt(r*r - cur.x()*cur.x() - cur.y()*cur.y());

    origin.x() = origin_x - winSize[2]/2;
    origin.y() = origin_y - winSize[3]/2;
    origin.z() = sqrt(r*r - origin.x()*origin.x() - origin.y()*origin.y());

    std::cerr << "   r: " << r
              << "\norig: " << origin.transpose()
              << " \ncur: " << cur.transpose() << std::endl;

    Eigen::Quaternionf quat;
    Eigen::Vector3f axis;
	float angle;
    axis = origin.cross(cur);

    angle = axis.norm() / (origin.norm() * cur.norm());
    quat.setFromTwoVectors(origin, cur);
    std::cerr << "angle-axis: " << angle << ", " << axis.transpose() << std::endl;
    std::cerr << "quat      : " << quat.vec().transpose() << std::endl;
    Eigen::Matrix3f mat = quat.matrix();
    GLfloat m[16];
    m[0] = mat(0,0); m[5] = mat(0,1); m[9] = mat(0,2); m[13] = d[0];
    m[1] = mat(1,0); m[6] = mat(1,1); m[10]= mat(1,2); m[14] = d[1];
    m[3] = mat(2,0); m[7] = mat(2,1); m[11]= mat(2,2); m[15] = d[2];
    m[4] = 0; m[8] = 0; m[12]= 0; m[16] = 1;

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(m);
    glutPostRedisplay();

}

void _motion(int x, int y)
{
	switch(motion_type) {
	case MOTION_ROTATE:
        std::cerr << "Rotating view\n";
	    camera_rotate(x, y);
		break;
	case MOTION_PAN:
        if()
        camera.pan(.01,0,0);
		break;
	case MOTION_ZOOM:
//		camera_zoom();
        break;
	}
}

void _passiveMotion(int x, int y)
{

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
//    gluLookAt(2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8]);
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
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix so we can manipulate scene
    glLoadIdentity(); // Reset projection matrix to identity to avoid artifacts
    // Set field of view, aspect ratio and min and max distances to draw objects
    gluPerspective(60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
    glTranslatef(.1,.1,.1);
    glMatrixMode(GL_MODELVIEW); // Switch back to model view matrix to draw shapes correctly
}

void _keyPressed(unsigned char key, int x, int y)
{
    if(27 == key) { // escape key
        glutDestroyWindow(glutGetWindow());
        exit(0);
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


