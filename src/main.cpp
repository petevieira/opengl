// OpenGL includes
#include <GL/glew.h>
#include <GL/glut.h>
// C includes
#include <iostream>


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

bool movingUp;
float yLocation = 0.0f;
float yRotAngle = 0.0f;

void _keyOperations(void)
{

}

void _mouse(int button, int state, int x, int y)
{

}

void _motion(int x, int y)
{

}

void _passiveMotion(int x, int y)
{
    std::cout << "(x,y) = " << x << ", " << y << std::endl;
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
    gluLookAt(2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glutSolidCube(2.0f);
    glutSwapBuffers(); // Swap OpenGL buffers and send to monitor
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set viewport to size of window
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix so we can manipulate scene
    glLoadIdentity(); // Reset projection matrix to identity to avoid artifacts
    // Set field of view, aspect ratio and min and max distances to draw objects
    gluPerspective(60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
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

    glutDisplayFunc(_display); // Tell GLUT to use the display() function to dislay stuff
    glutIdleFunc(_display); // Tell GLUT to use the displa() function for the idle operations
    glutReshapeFunc(reshape); // Tell GLUT to use the reshape function to reshape the window
    glutKeyboardFunc(_keyPressed); // Tell GLUT to use keyboard function for key presses
    glutKeyboardUpFunc(_keyReleased); // Tell GLUT to use keyUp function for key releases
    glutSpecialFunc(_keySpecialPressed); // Tell GLUT to use keySpecialPressed function for special key presses
    glutSpecialUpFunc(_keySpecialReleased); // Tell GLUT to use keySpecialReleased function for special key releases
    glutMouseFunc(_mouse); // Tell GLUT to use _mouse() function for mouse events
    glutMotionFunc(_motion); // Tell GLUT to use _motion() function for mouse motion events
    glutPassiveMotionFunc(_passiveMotion);


    glutMainLoop(); // Main loop
}


