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
#include <vectors.h>

const struct aiScene* scene;
aiVector3D scene_min, scene_max, scene_center;


Camera c;

float angle = 0;

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
    float scale;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glLoadIdentity();
    c.updateCamera();

    scale= scene_max.x-scene_min.x;
    scale= max(scene_max.y - scene_min.y,scale);
    scale= max(scene_max.z - scene_min.z,scale);
    scale= 2.f / scale;
    glScalef(scale, scale, scale);

    glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

    angle += 0.9;
    glRotatef(angle, 0, 1, 0);
    recursive_render(scene, scene->mRootNode);

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

    scene = aiImportFile(argv[1],aiProcessPreset_TargetRealtime_MaxQuality);

    if (!scene) {
        return 1;
    }
    get_bounding_box(scene, &scene_min,&scene_max);
    scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
    scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
    scene_center.z = (scene_min.z + scene_max.z) / 2.0f;

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
    aiReleaseImport(scene);
    return 0;
}


