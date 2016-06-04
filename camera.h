
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
        Camera()
        {
            eyePos = Vec3(0.0f, 0.0f, 3.0f);
            centerPos = Vec3(0.0f, 0.0f, -5.0f);
            upVector = Vec3(0.0f, 1.0f, 0.0f);
        }

        /* Update the camera to look at the correct position with correct orientation */
        void updateCamera()
        {
            this->calculateUp();
            gluLookAt(
                eyePos.x, eyePos.y, eyePos.z,
                centerPos.x, centerPos.y, centerPos.z,
                upVector.x, upVector.y, upVector.z
            );
        }

        /* Compute the current up vector */
        void calculateUp()
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
};

class Light
{
    public:
        /* Light constructor */
        Light()
        {
            /* Initialize basic light */
            const GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
            const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
            const GLfloat light_position[] = { 1.0, -5.0, 1.0, 0.0 };
            glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        }
};
