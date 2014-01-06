// C includes
#include <iostream
// Eigen includes
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
// OpenGL includes
#include <GL/glew.h>
#include <GL/glut.h>

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
			motion_type = MOTION_ROTATE;
			break;
		case GLUT_MIDDLE_BUTTON:
			motion_type = MOTION_ZOOM;
			break;
		case GLUT_RIGHT_BUTTON:
			motion_type = MOTION_PAN;
			break;
		}
    }
	else {
		motion_type = MOTION_NULL;
	}

}

/**
 * Rotate scene on hemisphere. Project x,y coordinates
 * onto hemisphere and then compute angle between the
 * vectors and axis to rotate about and convert to
 * quaternion. 
 */
void camera_rotate()
{
	Eigen


}

void _motion(int x, int y)
{
	switch(motion_type) {
	case MOTION_ROTATE:
	    camera_rotate();
		break;
	case MOTION_PAN:
		camera_pan();
		break;
	case MOTION_ZOOM:
		camera_zoom();
		break;
	}
}

void _passiveMotion(int x, int y)
{
    d[2] += .01;
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
    glLoadIdentity(); // Load identity matrix to reset our drawing locations
    // Camera center, aim at, up vector
//    gluLookAt(2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8]);
    glScalef(1.0, 1.0, 1.0);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
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
    // Toggle specularity
    if(key == 's')
    {
        if(!specular)
        {
            specular = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        }
        else if(specular)
        {
            specular = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, blankMaterial);
        }
    }
    if(key == 'd')
    {
        if(!diffuse)
        {
            diffuse = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
        }
        else if(diffuse)
        {
            diffuse = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
        }
    }
    if(key == 'e')
    {
        if(!emissive)
        {
            emissive = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
        }
        else if(emissive)
        {
            emissive = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
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


