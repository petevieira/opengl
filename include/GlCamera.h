
#ifndef GLCAMERA_H
#define GLCAMERA_H

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

};

#endif // GLCAMERA_H
