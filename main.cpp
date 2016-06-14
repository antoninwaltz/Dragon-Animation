/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>
#include <fstream>
#include <string>
#include <list>


#include <scene.h>
#include <camera.h>
#include <utils.h>

SceneHandler *scene;

Camera c;

std::list<GLuint> shaderList;
GLuint shaderProg;


float d_angle_x =0.0f;
float d_angle_y =0.0f;

int xorigin = 0;
int yorigin = 0;

bool is_l_clicked = false;
bool is_r_clicked = false;

bool AddShader(GLenum ShaderType, const char* pFilename)
{
    std::string s;
    std::ifstream f(pFilename);

    if (f.is_open()) {
        std::string line;
        while (getline(f, line)) {
            s.append(line);
            s.append("\n");
        }
        f.close();
    } else {
        std::cerr << "Error reading file " << pFilename << "\n";
        return false;
    }

    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        std::cerr << "Error creating shader type " << ShaderType << "\n";
        return false;
    }

    // Save the shader object - will be deleted in the destructor
    shaderList.push_back(ShaderObj);

    const GLchar* p[1];
    p[0] = s.c_str();
    GLint Lengths[1] = { (GLint)s.size() };

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        std::cerr << "Error compiling '" << pFilename << "': '" << InfoLog << "'\n";
        return false;
    }
    glAttachShader(shaderProg, ShaderObj);

    return true;
}


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

    scene->render();

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

/* Manage ASCII key input */
void keyInput(unsigned char key, int x, int y){
    switch(key){
        case'1': scene->setNumAnimation(1);
                 scene->activateAnimation(true);
                 scene->resetNumFrame();
                 break;
        case'2': scene->setNumAnimation(2);
                 scene->activateAnimation(true);
                 scene->resetNumFrame();
                 break;
        case'3': scene->setNumAnimation(3);
                 scene->activateAnimation(true);
                 scene->resetNumFrame();
                 break;
        default : break;
    }
}

/* Manage non-ASCII key input */
void specialInput(int key, int x, int y){
    Vec3 newPos;
    switch(key){
        case GLUT_KEY_UP :
            newPos = c.getPos();
            newPos.y+=0.1;
            c.setPos(newPos);break;
        case GLUT_KEY_DOWN :
            newPos = c.getPos();
            newPos.y-=0.1;
            c.setPos(newPos);break;
        case GLUT_KEY_RIGHT :
            newPos = c.getPos();
            newPos.x+=0.1;
            c.setPos(newPos);break;
        case GLUT_KEY_LEFT :
            newPos = c.getPos();
            newPos.x-=0.1;
            c.setPos(newPos);break;
        default : break;
    }
}

/* Manage mouse input */
void mouseInput(int button, int state, int x, int y){
    Vec3 newPos;
    switch(button){
        case GLUT_LEFT_BUTTON :
            if(state==GLUT_UP){
                is_l_clicked=false;
            }else if(state == GLUT_DOWN){
                is_l_clicked=true;
                xorigin=x;
            }
            break;
        case GLUT_RIGHT_BUTTON :
            if(state==GLUT_UP){
                is_r_clicked=false;
            }else if(state == GLUT_DOWN){
                is_r_clicked=true;
                yorigin=y;
            }
            break;
        case 3 :
            newPos = c.getPos();
            newPos.z-=0.1;
            c.setPos(newPos);break;
        case 4 :
            newPos = c.getPos();
            newPos.z+=0.1;
            c.setPos(newPos);break;
        default : break;
    }
}

/* Manage mouse move */
void mouseMoveInput(int x, int y){
    Vec3 newOri;
    if(is_l_clicked){
        //d_angle_y=(y-yorigin)*0.001f;
        d_angle_x=(x-xorigin)*0.001f;

        newOri=c.getOrient();
        newOri.x+=d_angle_x;
        //newOri.y+=d_angle_y;
        c.setOrient(newOri);
    }

    if(is_r_clicked){
        d_angle_y=(y-yorigin)*0.001f;
        //d_angle_x=(x-xorigin)*0.001f;

        newOri=c.getOrient();
        //newOri.x+=d_angle_x;
        newOri.y+=d_angle_y;
        c.setOrient(newOri);
    }
}



int main(int argc, char** argv)
{
    c = Camera();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("IN55 - Animation rendering");
    glewInit();
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialInput);
    glutMouseFunc(mouseInput);
    glutMotionFunc(mouseMoveInput);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    shaderProg = glCreateProgram();
    if (shaderProg == 0) {
        std::cerr <<  "Error creating shader program\n";
        return 1;
    }
    if (!AddShader(GL_VERTEX_SHADER, "shader.vs")) {
        AddShader(GL_VERTEX_SHADER, "shader_legacy.vs");
    }
    glLinkProgram(shaderProg);
    std::cout << "GUY\n\n\n";
    glUseProgram(shaderProg);

    scene = new SceneHandler(argv[1], shaderProg);

    glutMainLoop();

    delete scene;
    return 0;
}


