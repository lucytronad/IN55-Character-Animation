#ifndef QUATERNION_H
#define QUATERNION_H

#include "../common/Vectors.h"
#include "../common/GlFramework.h"

class Quaternion {

private:
    float w,x,y,z;
public :
    Quaternion();
    Quaternion(float w,float x,float y, float z);
    Quaternion operator*(const Quaternion &q);
    Vec3 operator*(const Vec3 &v);
    Quaternion operator*(float f);
    Quaternion operator+(const Quaternion &q);
    Quaternion& operator*=(const Quaternion &q);
    float dot(const Quaternion &q);
    void setFromAxis(float angle, float ax, float ay, float az);
    Quaternion conjugate();
    Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t);
    void normalize();
    GLMatrix setRotationMatrix();
    void setQuaternion(float w, float x, float y, float z);
    Vec3 toVec();
};

#endif // QUATERNION_H
