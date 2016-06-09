#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>

/* Camera class */
class Camera
{
    private:
        Vec3 eyePos;
        Vec3 centerPos;
        Vec3 upVector;

    public:
        /* Camera constructor */
        Camera();

        /* Update the camera to look at the correct position with correct orientation */
        void updateCamera();


        /* Compute the current up vector */
        void calculateUp();

        void setPos(Vec3 newPos);

        void setOrient(Vec3 newOrient);

        Vec3 getPos();

        Vec3 getOrient();
};

