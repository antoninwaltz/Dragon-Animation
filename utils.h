#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


const aiNodeAnim *findNodeAnim(const aiAnimation *anim, aiString name);

aiVector3D operator*( float num, aiVector3D v );
aiQuaternion operator*( float num, aiQuaternion v );
aiVector3D getPosition( aiMatrix4x4 mat );
aiVector3D getScale( aiMatrix4x4 mat );
aiMatrix4x4 operator*( float num, aiMatrix4x4 m );
aiMatrix4x4 operator+( aiMatrix4x4 m1, aiMatrix4x4 m2 );
std::ostream& operator<<(std::ostream& os, const aiMatrix4x4& m);

#endif


