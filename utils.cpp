/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */

#include <utils.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

const aiNodeAnim *findNodeAnim(const aiAnimation *anim, aiString name) {
    for (unsigned int i = 0; i < anim->mNumChannels; i++) {
        if (anim->mChannels[i]->mNodeName == name) {
            return anim->mChannels[i];
        }
    }
    return NULL;
}

aiVector3D operator*( float num, aiVector3D v ) {
    return aiVector3D(v.x * num, v.y * num, v.z * num);
}
aiQuaternion operator*( float num, aiQuaternion v ) {
    return aiQuaternion(v.w * num, v.x * num, v.y * num, v.z * num);
}

aiVector3D getPosition( aiMatrix4x4 mat ) {
    return aiVector3D(mat.a4, mat.b4, mat.c4);
}
aiVector3D getScale( aiMatrix4x4 mat ) {
    return aiVector3D(mat.a1, mat.b2, mat.c3);
}

