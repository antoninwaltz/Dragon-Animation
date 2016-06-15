#ifndef __MESH_H__
#define __MESH_H__

#include <iostream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>
#include <animation.h>
#include <utils.h>

class Face
{
    private:
        GLenum type;
        int indexNumber, maxIndexNumber;
        int *indices;

    public:
        Face(int nb) {
            indexNumber = 0;
            maxIndexNumber = nb;
            switch(nb) {
                case 1: type = GL_POINTS; break;
                case 2: type = GL_LINES; break;
                case 3: type = GL_TRIANGLES; break;
                default: type = GL_POLYGON; break;
            }
            indices = (int*) malloc(sizeof(int) * nb);
        };
        virtual ~Face() { free(indices); };

        int getIndexNumber() { return indexNumber; };
        GLenum getType() { return type; };
        int getIndex(int idx) { return (idx < indexNumber) ? indices[idx] : -1; };
        void addIndex(int idx) {
            if (indexNumber < maxIndexNumber) {
                indices[indexNumber++] = idx;
            }
        };
};


class Mesh
{
    private:
        Vertice **verticeList;
        aiVector3D **normalList;
        Face **faceList;
        Bone **boneList;
        aiMatrix4x4 *boneStateList;
        Animation **animList;
        int vertNb, boneNb, faceNb, animNb, maxFaceNb;
        int mesh_id;
        int currentAnimation;
        GLint shader_bones;
        GLint shader_Position;
        GLint shader_Normal;
        GLint shader_BoneTransform;
        GLint shader_Weights;
        GLuint shaderProg;

    public:
        Mesh(int id, int vertSize, int boneSize, int faceSize, GLuint prog){
            shaderProg = prog;
            vertNb = vertSize;
            boneNb = boneSize;
            faceNb = 0;
            animNb = 0;
            maxFaceNb = faceSize;
            mesh_id = id;
            verticeList = (Vertice**)malloc(vertNb * sizeof(Vertice*));
            normalList = (aiVector3D**)malloc(vertNb * sizeof(aiVector3D*));
            boneList = (Bone**)malloc(boneNb * sizeof(Bone*));
            boneStateList = (aiMatrix4x4*) malloc(boneNb * sizeof(aiMatrix4x4));
            faceList = (Face**)malloc(faceSize * sizeof(Face*));
            currentAnimation = 0;
            shader_bones = glGetUniformLocation(shaderProg, "gBones");
            shader_Position = glGetAttribLocation(shaderProg, "Position");
            shader_Normal = glGetAttribLocation(shaderProg, "Normal");
            shader_BoneTransform = glGetAttribLocation(shaderProg, "BoneTransform");
            shader_Weights = glGetAttribLocation(shaderProg, "Weights");
        };

        void setCurrentAnim(int n) {
            if (0 < n && n <= animNb) {
                currentAnimation = n-1;
            } else {
                currentAnimation = 0;
            }
        };

        void initAnimList(const aiScene *scene);

        bool updateBoneStateList(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform);

        void render(bool anim);

        void addVertice(Vertice *vert, aiVector3D *normal, int index) {
            if (index < vertNb) {
                verticeList[index] = vert;
                normalList[index] = normal;
            }
        };

        void setVertBone(int index, aiString boneID, float weight) {
            if(index < vertNb) {
                verticeList[index]->setBones(boneID, weight);
            }
        };

        void addBone(Bone *bone, int index) {
            if (index < boneNb) {
                boneList[index] = bone;
            }
        }

        void addFace(Face *f) {
            if (faceNb < maxFaceNb) {
                faceList[faceNb++] = f;
            }
        }

        int getNbVert(){return vertNb;};
        int getNbBone(){return boneNb;};
        int getFaceNumber() { return faceNb; };
        int getId() { return mesh_id; };

        Face *getFace(int i) { return (i < faceNb) ? faceList[i] : NULL; };
        Vertice *getVertex(int i) { return (i < vertNb) ? verticeList[i] : NULL; };
        aiVector3D *getNormal(int i) { return (i < vertNb) ? normalList[i] : NULL; };
        Bone *getBone(int i) { return (i < boneNb) ? boneList[i] : NULL; };
        int getBoneIndex(aiString name) {
            for (int i = 0; i < boneNb; ++i) {
                if (boneList[i]->getName() == name) {
                    return i;
                }
            }
            return -1;
        }
        Bone *getBone(aiString name) {
            int i = getBoneIndex(name);
            return (i != -1) ? boneList[i] : NULL;
        };
};

#endif
