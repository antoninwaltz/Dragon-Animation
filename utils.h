#ifndef __UTILS_H__
#define __UTILS_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

const aiNodeAnim *findNodeAnim(const aiAnimation *anim, aiString name);

aiVector3D operator*( float num, aiVector3D v );
aiQuaternion operator*( float num, aiQuaternion v );
aiVector3D getPosition( aiMatrix4x4 mat );
aiVector3D getScale( aiMatrix4x4 mat );

#endif


