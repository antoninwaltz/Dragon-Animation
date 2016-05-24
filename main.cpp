/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

#include <model.h>
#include <camera.h>
#include <vectors.h>


Model m;
Camera c;

float angle = 0;

/* Initialize OpenGL */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);               // Set background color to black and opaque
   glClearDepth(1.0f);                                 // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);                            // Enable depth testing
   glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
   glShadeModel(GL_SMOOTH);                            // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glLoadIdentity();
    c.updateCamera();
    glTranslatef(0, -0.2, 1);
    // glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glScalef(0.001, 0.001, 0.001);

    glBegin(GL_TRIANGLES); // TODO maybe move that to some glDrawArray for optimization?
        unsigned int size = m.getFaceList().size();
        for (unsigned int i = 0; i < size; i++)
        {
            Face f = m.getFace(i);
            Vec3 v = m.getVertex(f.getV1()-1);
            glColor3f((i%3)==0, (i%3)==1, (i%3)==2);
            glVertex3f(v.x, v.y, v.z);
            v = m.getVertex(f.getV2()-1);
            glVertex3f(v.x, v.y, v.z);
            v = m.getVertex(f.getV3()-1);
            glVertex3f(v.x, v.y, v.z);
        }
    glEnd();
    glutSwapBuffers();
    angle += 0.9;
}


/* Timer to refresh every 15ms */
void timer(int value) {
   glutPostRedisplay();
   glutTimerFunc(50, timer, 0);
}

/* Resize the window */
void reshape(GLsizei width, GLsizei height) {
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv)
{
    m = Model();
    c = Camera();

    m.loadFile(argv[1]);
    // m.printVertex();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("IN55 - Animation rendering");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}


