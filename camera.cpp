
#include <iostream>

#include <GL/glut.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <camera.h>

Camera::Camera()
{
    eyePos = Vec3(0.0f, 0.0f, 3.0f);
    centerPos = Vec3(0.0f, 0.0f, -5.0f);
    upVector = Vec3(0.0f, 1.0f, 0.0f);
}

void Camera::updateCamera()
{
    this->calculateUp();
    gluLookAt(
        eyePos.x, eyePos.y, eyePos.z,
        centerPos.x, centerPos.y, centerPos.z,
        upVector.x, upVector.y, upVector.z
    );
}

void Camera::calculateUp()
{
    float l = eyePos.length();
    Vec3 v = Vec3(eyePos.x/l, eyePos.y/l, eyePos.z/l);
    Vec3 up = Vec3(0.0f, 1.0f, 0.0f);

    Vec3 s = Vec3(
        v.y * up.z - v.z * up.y,
        v.z * up.x - v.x * up.z,
        v.x * up.y - v.y * up.x
    );

    upVector.x = s.y * v.z - s.z * v.y;
    upVector.y = s.z * v.x - s.x * v.z;
    upVector.z = s.x * v.y - s.y * v.x;
}

void Camera::setPos(Vec3 newPos)
{
    eyePos=newPos;
}

void Camera::setOrient(Vec3 newOri)
{
    centerPos=newOri;
}

Vec3 Camera::getPos()
{
    return eyePos;
}

Vec3 Camera::getOrient()
{
    return centerPos;
}