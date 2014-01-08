#include "GlCamera.h"
#include <iostream>

GlCamera::GlCamera()
{
    setViewport(0, 0, 100, 100);
}

void GlCamera::rotate(int x, int y)
{
    Eigen::Vector3f cur, origin;

    cur = hemisphereCoords(x,y);
    origin = hemisphereCoords(mousePos.x(), mousePos.y());

    Eigen::Quaternionf quat;
    Eigen::Vector3f axis;
    float angle;
    axis = origin.cross(cur);

    angle = axis.norm() / (origin.norm() * cur.norm());
    quat.setFromTwoVectors(origin, cur);
    std::cerr << "angle-axis: " << angle << ", " << axis.transpose() << std::endl;
    std::cerr << "quat      : " << quat.vec().transpose() << std::endl;
    Eigen::Matrix3f mat = quat.matrix();
//    GLfloat m[16];
//    m[0] = mat(0,0); m[5] = mat(0,1); m[9] = mat(0,2); m[13] = d[0];
//    m[1] = mat(1,0); m[6] = mat(1,1); m[10]= mat(1,2); m[14] = d[1];
//    m[3] = mat(2,0); m[7] = mat(2,1); m[11]= mat(2,2); m[15] = d[2];
//    m[4] = 0; m[8] = 0; m[12]= 0; m[16] = 1;

    glMatrixMode(GL_MODELVIEW);
    glRotatef(angle, axis.x(), axis.y(), axis.z());
    glutPostRedisplay();
}

void GlCamera::rotate(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);

    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    glRotatef(z, 0, 0, 1);
    glutPostRedisplay();
}

void GlCamera::pan(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(x/100, -y/100, z);
    glutPostRedisplay();
}

void GlCamera::pan(const Eigen::Vector3f& p)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(p.x()/100, -p.y()/100, p.z());
    glutPostRedisplay();
}

void GlCamera::zoom(float factor)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0, 0, factor);
    glutPostRedisplay();
}

void GlCamera::setCameraType(CameraType cameraType)
{
    _cameraType = cameraType;
}

//--------------------------
// Private Member Functions
//--------------------------

void GlCamera::setViewport(int x, int y, int w, int h)
{
    _viewport.x = x;
    _viewport.y = y;
    _viewport.w = w;
    _viewport.h = h;
    _viewport.center.x() = (w - x)/2;
    _viewport.center.y() = (h - y)/2;
    _viewport.diagonal = sqrt((w-x)*(w-x) + (h-y)*(h-y));
}

Eigen::Vector3f GlCamera::hemisphereCoords(int x, int y) const
{
    Eigen::Vector3f ray; // Ray in hemisphere going from world origin

    // Compute ray components by first getting radius of hemishpere which
    // is half the diagonal of the viewport
    float r = _viewport.diagonal/2;
    ray.x() = x - _viewport.center.x();
    ray.y() = y - _viewport.center.y();
    ray.z() = sqrt(r*r - x*x - y*y);

    return ray;
}
