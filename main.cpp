/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>


#include <scene.h>
#include <camera.h>

SceneHandler scene;

Camera c;

/* Initialize OpenGL */
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);               // Set background color to black and opaque
    glClearDepth(1.0f);                                 // Set background depth to farthest
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);                                // Uses default lighting parameters
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);                            // Enable depth testing
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_NORMALIZE);
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

    scene.render();

    glutSwapBuffers();
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
    c = Camera();
    scene = SceneHandler();

    if (scene.load_file(argv[1])) {
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
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


