
#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <GL/glew.h>

#include <GL/glu.h>
#include <GL/glut.h>


class GlCamera
{
public:

    GlCamera();

    /**
     * Rotate scene on hemisphere. Project x,y coordinates
     * onto hemisphere and then compute angle between the
     * vectors and axis to rotate about and convert to
     * quaternion.
     */
    void rotate(int x, int y);
    void pan(float x, float y, float z);
    void pan(const Eigen::Vector3f& p);
    void zoom();

    Eigen::Vector3f mouse_origin;
};

#endif // GLCAMERA_H
