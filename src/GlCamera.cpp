#include "GlCamera.h"

GlCamera::GlCamera(){}

    /**
     * Rotate scene on hemisphere. Project x,y coordinates
     * onto hemisphere and then compute angle between the
     * vectors and axis to rotate about and convert to
     * quaternion.
     */
//    void camera_rotate(int x, int y)
//    {
//        Eigen::Quaternionf quat;
//        Eigen::Vector3f vec1, vec2, axis;
//        float angle;
//        vec1 = origin_x, origin_y, sqrt(r - (origin_x*origin_x) - (origin_y*origin_y));
//        vec2 = x, y, sqrt(r - (x*x) - (y*y));
//        axis = vec1.cross(vec2);

//        angle = axis.norm() / (vec1.norm() * vec2.norm());
//        quat.FromTwoVectors(vec1, vec2);


//    }

void GlCamera::pan(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(x, y, z);
    glutPostRedisplay();
}

void GlCamera::pan(const Eigen::Vector3f& p)
{

}
