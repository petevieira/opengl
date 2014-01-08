
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

    enum CameraType {
        CAMERA_ORTHONORMAL,
        CAMERA_PERSPECTIVE
    };

    enum MatrixType {
        MATRIX_PROJECTION,
        MATRIX_MODELVIEW
    };

    enum MouseMode {
        MOUSE_NONE=0,
        MOUSE_PAN,
        MOUSE_ZOOM,
        MOUSE_ROTATE
    };

    Eigen::Vector3f mousePos;

    /**
     * \brief Constructor for camera class
     */
    GlCamera();

    /**
     * Rotate scene on hemisphere. Project x,y coordinates
     * onto hemisphere and then compute angle between the
     * vectors and axis to rotate about and convert to
     * quaternion.
     */
    void rotate(int x, int y);
    void rotate(float x, float y, float z);
    void pan(float x, float y, float z);
    void pan(const Eigen::Vector3f& p);
    void zoom(float factor);
    void setCameraType(CameraType cameraType);
    void setViewport(int x, int y, int w, int h);


private:

    class Viewport
    {
    public:
        int x;
        int y;
        int w;
        int h;
        float diagonal;
        Eigen::Vector2f center;
    };

    Viewport _viewport;
    CameraType _cameraType;
    Eigen::Vector2f _mouseXY;
    Eigen::Vector3f _eye, _center, _up;

    float _minSize, _maxSize;
    float _minXRot, _maxXRot;
    float _minYRot, _maxYRot;

    Eigen::Vector3f hemisphereCoords(int x, int y) const;
};

#endif // GLCAMERA_H
