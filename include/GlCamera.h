
#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

class GlCamera
{
public:

    /**
     * Rotate scene on hemisphere. Project x,y coordinates
     * onto hemisphere and then compute angle between the
     * vectors and axis to rotate about and convert to
     * quaternion.
     */
    void camera_rotate(int x, int y);


    Eigen::Vector3f mouse_origin;
};

#endif // GLCAMERA_H
