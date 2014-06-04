#ifndef CAMERA_H
#define CAMERA_H

#include "../common/Vectors.h"
#include "../common/GlFramework.h"
#include "Quaternion.h"

class Camera {

private:
    Vec3 m_Position;
    Quaternion m_Orientation;
    GLMatrix m_ViewMatrix;
    GLMatrix m_ProjectionMatrix;
    float fovY,zNear,zFar,ratio;

public:
    Camera();
    void translate(float x, float y, float z);
    void translateX(float shift);
    void translateY(float shift);
    void translateZ(float shift);
    void rotate(float angle, float ax, float ay, float az);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    const GLMatrix& getViewMatrix();
    void setAspectRatio(float ar);
    void setPlanes(float np, float fp);
    void setFOV(float angle);
    const GLMatrix& getProjectionMatrix();
    void setPosition(float x,float y, float z);
    void setOrientation(float angle, float x, float y, float z);
    float degToRad(int degrees);
    void buildViewMatrix();
    void buildProjectionMatrix();

};

#endif // CAMERA_H
