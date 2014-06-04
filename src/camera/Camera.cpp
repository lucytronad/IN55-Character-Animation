
#include "Camera.h"
#include "math.h"

Camera::Camera(){

}

void
Camera::translate(float x, float y, float z) {
    Quaternion translationResult(0,-x,-y,-z);
    translationResult = this->m_Orientation * translationResult * this->m_Orientation.conjugate();

    m_Position+=translationResult.toVec();
}

void
Camera::translateX(float shift) {
    Quaternion translationResult(0,-1,0,0);
    translationResult = this->m_Orientation * translationResult * this->m_Orientation.conjugate();
    translationResult.normalize();
    translationResult = translationResult * shift;

    m_Position+=translationResult.toVec();

}
void
Camera::translateY(float shift) {
    Quaternion translationResult(0,0,-1,0);
    translationResult = this->m_Orientation * translationResult * this->m_Orientation.conjugate();
    translationResult.normalize();
    translationResult = translationResult * shift;

    m_Position+=translationResult.toVec();
}

void
Camera::translateZ(float shift) {
    Quaternion translationResult(0,0,0,-1);
    translationResult = this->m_Orientation * translationResult * this->m_Orientation.conjugate();
    translationResult = translationResult * shift;

    m_Position+=translationResult.toVec();
}

void
Camera::rotate(float angle, float ax, float ay, float az) {
    Quaternion rotation,rotationX,rotationY,rotationZ;
    rotationX.setFromAxis(cos(degToRad(-angle)/2),sin(degToRad(-angle)/2)*ax,0,0);
    rotationY.setFromAxis(cos(degToRad(-angle)/2),0,sin(degToRad(-angle)/2)*ay,0);
    rotationZ.setFromAxis(cos(degToRad(-angle)/2),0,0,sin(degToRad(-angle)/2)*az);
    rotation = rotationX*rotationY*rotationZ;
    this->m_Orientation = this->m_Orientation * rotation;
    this->m_Orientation.normalize();
}

void
Camera::rotateX(float angle) {
    Quaternion tmpQ;
    tmpQ.setFromAxis(cos(degToRad(-angle)/2),sin(degToRad(-angle)/2),0,0);
    tmpQ.normalize();
    this->m_Orientation = this->m_Orientation * tmpQ;
    this->m_Orientation.normalize();
}

void
Camera::rotateY(float angle) {
    Quaternion tmpQ;
    tmpQ.setFromAxis(cos(degToRad(-angle)/2),0,sin(degToRad(-angle)/2),0);
    tmpQ.normalize();
    this->m_Orientation = this->m_Orientation * tmpQ;
    this->m_Orientation.normalize();
}

void
Camera::rotateZ(float angle) {
    Quaternion tmpQ;
    tmpQ.setFromAxis(cos(degToRad(-angle)/2),0,0,sin(degToRad(-angle)/2));
    tmpQ.normalize();
    this->m_Orientation = this->m_Orientation * tmpQ;
    this->m_Orientation.normalize();
}

const GLMatrix&
Camera::getViewMatrix() {
     return this->m_ViewMatrix;
}

void
Camera::setAspectRatio(float ar) {
    this->ratio=ar;
}

void
Camera::setPlanes(float np, float fp) {
    this->zNear=np;
    this->zFar=fp;
}

void
Camera::setFOV(float angle) {
 this->fovY=angle;
}

const GLMatrix&
Camera::getProjectionMatrix() {
    return this->m_ProjectionMatrix;
}

void
Camera::setPosition(float x,float y,float z) {
    this->m_Position.x=x;
    this->m_Position.y=y;
    this->m_Position.z=z;
}

void
Camera::setOrientation(float angle, float x, float y, float z) {
    this->m_Orientation.setFromAxis(angle,x,y,z);
}

float
Camera::degToRad(int degrees) {
    return degrees * 2 * M_PI / 360.0;
}

void
Camera::buildViewMatrix() {
    this->m_ViewMatrix.data[0]=1;   this->m_ViewMatrix.data[1]=0;   this->m_ViewMatrix.data[2]=0;   this->m_ViewMatrix.data[3]=-m_Position.x;
    this->m_ViewMatrix.data[4]=0;   this->m_ViewMatrix.data[5]=1;   this->m_ViewMatrix.data[6]=0;   this->m_ViewMatrix.data[7]=-m_Position.y;
    this->m_ViewMatrix.data[8]=0;   this->m_ViewMatrix.data[9]=0;   this->m_ViewMatrix.data[10]=1;  this->m_ViewMatrix.data[11]=-m_Position.z;
    this->m_ViewMatrix.data[12]=0;  this->m_ViewMatrix.data[13]=0;  this->m_ViewMatrix.data[14]=0;  this->m_ViewMatrix.data[15]=1;

    this->m_ViewMatrix=(m_Orientation.conjugate()).setRotationMatrix()*this->m_ViewMatrix;
}

void
Camera::buildProjectionMatrix() {

    GLfloat thetaY = 0.5f * (M_PI * this->fovY / 180.0f);
    GLfloat tanThetaY = tan(thetaY);
    GLfloat tanThetaX = tanThetaY * this->ratio;
    GLfloat halfW   =  tanThetaX * this->zNear;
    GLfloat halfH   =  tanThetaY * this->zNear;
    GLfloat left    = -halfW;
    GLfloat right   =  halfW;
    GLfloat bottom  = -halfH;
    GLfloat top     =  halfH;
    GLfloat iWidth  = 1.0f / (right - left);
    GLfloat iHeight = 1.0f / (top - bottom);
    GLfloat iDepth  = 1.0f / (this->zFar - this->zNear);

    this->m_ProjectionMatrix.m[0][0] = 2.0f * this->zNear * iWidth;
    this->m_ProjectionMatrix.m[0][1] = 0.0f;
    this->m_ProjectionMatrix.m[0][2] =  (right + left) * iWidth;
    this->m_ProjectionMatrix.m[0][3] =  0.0f;

    this->m_ProjectionMatrix.m[1][0] = 0.0f;
    this->m_ProjectionMatrix.m[1][1] = 2.0f * this->zNear * iHeight;
    this->m_ProjectionMatrix.m[1][2] =  (top + bottom) * iHeight;
    this->m_ProjectionMatrix.m[1][3] =  0.0f;

    this->m_ProjectionMatrix.m[2][0] = 0.0f;
    this->m_ProjectionMatrix.m[2][1] = 0.0f;
    this->m_ProjectionMatrix.m[2][2] = -(this->zFar + this->zNear) * iDepth;
    this->m_ProjectionMatrix.m[2][3] = -2.0f * (this->zFar * this->zNear) * iDepth;

    this->m_ProjectionMatrix.m[3][0] = 0.0f;
    this->m_ProjectionMatrix.m[3][1] = 0.0f;
    this->m_ProjectionMatrix.m[3][2] = -1.0f;
    this->m_ProjectionMatrix.m[3][3] =  0.0f;
}
