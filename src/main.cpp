// OpenGL includes
#include <GL/glew.h>
#include <GL/glut.h>
// C includes
#include <iostream>


bool* keyStates = new bool[256]; // Create array of bools for key states (true=up/false=down)
bool* keySpecialStates = new bool[256]; // Create array of bools for special key states (true=up/false=down)

bool movingUp;
float yLocation = 0.0f;
float yRotAngle = 0.0f;

void keyOperations(void)
{
    if(keyStates['a'])
        std::cout << "Help" << std::endl;
    if(keyStates['e'])
        std::cout << "e" << std::endl;
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

void display(void)
{
    keyOperations();
    glClearColor(1.f, 0.f, 0.f, 1.f); // Make background red
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity(); // Load identity matrix to reset our drawing locations
    glTranslatef(0.0f, 0.0f, -5.0f); // Move back 5 units
    glTranslatef(0.0f, yLocation, 0.0f);
    glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
    glutWireCube(2.0f);
    glFlush(); // Flush the OpenGL buffers to the window

    if(movingUp)
        yLocation -= 0.005f;
    else
        yLocation += 0.005f;

    if(yLocation < -3.0f)
        movingUp = false;
    else if(yLocation > 3.0f)
        movingUp = true;

    yRotAngle += 0.005f;
    if(yRotAngle > 360.0f)
        yRotAngle -= 0.005f;
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

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true;
}

void keyReleased(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}

void keySpecialPressed(int key, int x, int y)
{
    keySpecialStates[key] = true;
}

void keySpecialReleased(int key, int x, int y)
{
    keySpecialStates[key] = false;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE); // Set up basic display buffer
    glutInitWindowSize(500, 500); // Set the width and height of the window
    glutInitWindowPosition(100, 100); // Set the position of the window
    glutCreateWindow("My first OpenGL window"); // Set title of the window

    glutDisplayFunc(display); // Tell GLUT to use the display() function to dislay stuff
    glutIdleFunc(display); // Tell GLUT to use the displa() function for the idle operations
    glutReshapeFunc(reshape); // Tell GLUT to use the reshape function to reshape the window
    glutKeyboardFunc(keyPressed); // Tell GLUT to use keyboard function for key presses
    glutKeyboardUpFunc(keyReleased); // Tell GLUT to use keyUp function for key releases
    glutSpecialFunc(keySpecialPressed); // Tell GLUT to use keySpecialPressed function for special key presses
    glutSpecialUpFunc(keySpecialReleased); // Tell GLUT to use keySpecialReleased function for special key releases


    glutMainLoop(); // Main loop
}


