#include <GL/glew.h>
#include <GL/glut.h>

void display(void)
{
    glClearColor(1.f, 0.f, 0.f, 1.f); // Make background red
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity(); // Load identity matrix to reset our drawing locations
    glFlush(); // Flush the OpenGL buffers to the window
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE); // Set up basic display buffer
    glutInitWindowSize(500, 500); // Set the width and height of the window
    glutInitWindowPosition(100, 100); // Set the position of the window
    glutCreateWindow("My first OpenGL window"); // Set title of the window

    glutDisplayFunc(display);
    glutMainLoop();
}


