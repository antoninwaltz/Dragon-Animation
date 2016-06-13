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

aiMatrix4x4 operator*( float n, aiMatrix4x4 m ) {
    return aiMatrix4x4(
            n*m.a1, n*m.a2, n*m.a3, n*m.a4,
            n*m.b1, n*m.b2, n*m.b3, n*m.b4,
            n*m.c1, n*m.c2, n*m.c3, n*m.c4,
            n*m.d1, n*m.d2, n*m.d3, n*m.d4
            );
}

aiMatrix4x4 operator+( aiMatrix4x4 m1, aiMatrix4x4 m2 ) {
    return aiMatrix4x4(
            m1.a1+m2.a1, m1.a2+m2.a2, m1.a3+m2.a3, m1.a4+m2.a4,
            m1.b1+m2.b1, m1.b2+m2.b2, m1.b3+m2.b3, m1.b4+m2.b4,
            m1.c1+m2.c1, m1.c2+m2.c2, m1.c3+m2.c3, m1.c4+m2.c4,
            m1.d1+m2.d1, m1.d2+m2.d2, m1.d3+m2.d3, m1.d4+m2.d4
            );
}

aiVector3D getPosition( aiMatrix4x4 mat ) {
    return aiVector3D(mat.a4, mat.b4, mat.c4);
}
aiVector3D getScale( aiMatrix4x4 mat ) {
    return aiVector3D(mat.a1, mat.b2, mat.c3);
}
std::ostream& operator<<(std::ostream& os, const aiMatrix4x4& m) {
    return os <<
        "Mat: " << m.a1 << " " << m.a2 << " " << m.a3 << " " << m.a4 << "\n" <<
        "     " << m.b1 << " " << m.b2 << " " << m.b3 << " " << m.b4 << "\n" <<
        "     " << m.c1 << " " << m.c2 << " " << m.c3 << " " << m.c4 << "\n" <<
        "     " << m.d1 << " " << m.d2 << " " << m.d3 << " " << m.d4 << "\n";
}
