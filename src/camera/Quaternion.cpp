#include "Quaternion.h"

Quaternion::Quaternion() {}

Quaternion::Quaternion(float w, float x, float y, float z) {
    this->w=w;
    this->x=x;
    this->y=y;
    this->z=z;
}

void Quaternion::setQuaternion(float w, float x, float y, float z) {
    this->w=w;
    this->x=x;
    this->y=y;
    this->z=z;
}

Quaternion Quaternion::operator*(const Quaternion &q) {

    float tmpW= this->w*q.w - this->x*q.x - this->y*q.y - this->z*q.z;
    float tmpX= this->w*q.x + this->x*q.w + this->y*q.z - this->z*q.y;
    float tmpY= this->w*q.y + this->y*q.w - this->x*q.z + this->z*q.x;
    float tmpZ= this->z*q.w + this->w*q.z + this->x*q.y - this->y*q.x;

    Quaternion tmpQ;
    tmpQ.setQuaternion(tmpW,tmpX,tmpY,tmpZ);
    tmpQ.normalize();
    return tmpQ;
}

Vec3 Quaternion::operator*(const Vec3 &v) {
    Quaternion tmpQuaternion;
    tmpQuaternion.setQuaternion(0,v.x,v.y,v.z);
    tmpQuaternion = this->operator*(tmpQuaternion.operator*(this->conjugate()));
    tmpQuaternion.normalize();
    Vec3 returnVec;
    returnVec.x=tmpQuaternion.x;
    returnVec.y=tmpQuaternion.y;
    returnVec.z=tmpQuaternion.z;
    return returnVec;
}

Quaternion Quaternion::operator*(float f) {
    Quaternion tmpQ;
    tmpQ.setQuaternion(this->w*f,this->x*f,this->y*f,this->z*f);
    tmpQ.normalize();
    return tmpQ;
}

Quaternion Quaternion::operator+(const Quaternion &q) {
    Quaternion tmpQ;
    tmpQ.setQuaternion(this->w+q.w,this->x+q.x,this->y+q.y,this->z+q.z);
    return tmpQ;
}

Quaternion& Quaternion::operator*=(const Quaternion &q) {
    float tmpW= this->w*q.w - this->x*q.x - this->y*q.y - this->z*q.z;
    float tmpX= this->w*q.x + this->x*q.w + this->y*q.z - this->z*q.y;
    float tmpY= this->w*q.y + this->y*q.w - this->x*q.z + this->z*q.x;
    float tmpZ= this->z*q.w + this->w*q.z + this->x*q.y - this->y*q.x;

    this->w=tmpW;
    this->x=tmpX;
    this->y=tmpY;
    this->z=tmpZ;

    return *this;
}

float Quaternion::dot(const Quaternion &q) {
    return this->w*q.w+this->x*q.x+this->y*q.y+this->z*q.z;
}

void Quaternion::setFromAxis(float angle, float ax, float ay, float az) {

    this->w=cos(angle);
    this->x=sin(angle)*ax;
    this->y=sin(angle)*ay;
    this->z=sin(angle)*az;

}

Quaternion Quaternion::conjugate() {
    Quaternion tmpQ;
    tmpQ.setQuaternion(this->w,-this->x,-this->y,-this->z);
    return tmpQ;
}

Quaternion Quaternion::slerp(const Quaternion &q1, const Quaternion &q2, float t) {

    Quaternion tmpQ1 = q1;
    Quaternion tmpQ2 = q2;
    Quaternion tmpQ;
    Quaternion tmp = tmpQ1.operator *(tmpQ2.conjugate());
    float teta = acos(tmp.w);

    tmpQ=(tmpQ1.operator*((sin(teta)*(1-t))/sin(teta))).operator+(tmpQ2.operator*((sin(teta)*t)/sin(teta)));

    return tmpQ;

}

void Quaternion::normalize() {
    float norm=sqrt(pow(this->w,2)+pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
    this->x/=norm;
    this->y/=norm;
    this->z/=norm;
    this->w/=norm;
}

GLMatrix
Quaternion::setRotationMatrix() {
    GLMatrix rotation;
    rotation.data[0]=1-2*this->y*this->y-2*this->z*this->z;
    rotation.data[1]=2*this->x*this->y-2*this->w*this->z;
    rotation.data[2]=2*this->x*this->z+2*this->w*this->y;
    rotation.data[3]=0;

    rotation.data[4]=2*this->x*this->y+2*this->w*this->z;
    rotation.data[5]=1-2*this->x*this->x-2*this->z*this->z;
    rotation.data[6]=2*this->y*this->z-2*this->w*this->x;
    rotation.data[7]=0;

    rotation.data[8]=2*this->x*this->z-2*this->w*this->y;
    rotation.data[9]=2*this->y*this->z+2*this->w*this->x;
    rotation.data[10]=1-2*this->x*this->x-2*this->y*this->y;
    rotation.data[11]=0;

    rotation.data[12]=0;
    rotation.data[13]=0;
    rotation.data[14]=0;
    rotation.data[15]=1;


    return rotation;
}

Vec3
Quaternion::toVec() {
    Vec3 returnVec;
    returnVec.x=this->x;
    returnVec.y=this->y;
    returnVec.z=this->z;
    return returnVec;
}
