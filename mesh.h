#ifndef __MESH_H__
#define __MESH_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>
#include <animation.h>
#include <scene.h>

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

const aiNodeAnim *findNodeAnim(const aiAnimation *anim, aiString name);

class Mesh
{
    private:
        Vertice **verticeList;
        aiVector3D **normalList;
        Face **faceList;
        Bone **boneList;
        Animation **animList;
        int vertNb, boneNb, faceNb, animNb, maxFaceNb;
        int mesh_id;

    public:
        Mesh(int id, int vertSize, int boneSize, int faceSize){
            vertNb = vertSize;
            boneNb = boneSize;
            faceNb = 0;
            animNb = 0;
            maxFaceNb = faceSize;
            mesh_id = id;
            verticeList = (Vertice**)malloc(vertNb * sizeof(Vertice*));
            normalList = (aiVector3D**)malloc(vertNb * sizeof(aiVector3D*));
            boneList = (Bone**)malloc(boneNb * sizeof(Bone*));
            faceList = (Face**)malloc(faceSize * sizeof(Face*));
        };

        void initAnimList(const aiScene *scene) {
            animList = (Animation**) malloc(scene->mNumAnimations * sizeof(Animation*));
            for (int i = 0; i < scene->mNumAnimations; i++) {
                const aiAnimation *anim = scene->mAnimations[i];
                Animation *my_anim = new Animation(boneNb, scene->mAnimations[i]->mDuration, scene->mAnimations[i]->mTicksPerSecond);
                for (int j = 0; j < boneNb; j++) {
                     const aiNodeAnim *nodeAnim = findNodeAnim(anim, getBone(j)->getName());
                     BoneAnim *boneAnim = new BoneAnim(
                                 nodeAnim->mNumPositionKeys,
                                 nodeAnim->mNumRotationKeys,
                                 nodeAnim->mNumScalingKeys);
                     for (int k = 0; k < nodeAnim->mNumPositionKeys; k++)
                        boneAnim->addTrans(nodeAnim->mPositionKeys[k]);
                     for (int k = 0; k < nodeAnim->mNumRotationKeys; k++)
                        boneAnim->addRot(nodeAnim->mRotationKeys[k]);
                     for (int k = 0; k < nodeAnim->mNumScalingKeys; k++)
                        boneAnim->addScal(nodeAnim->mScalingKeys[k]);
                     my_anim->addBoneAnim(boneAnim);
                }
                animList[animNb++] = my_anim;
            }
         };

        void render() {
            int i, j;
            bool use_normal = false;
            if (this->getNormal(0) != NULL) {
                use_normal = true;
            }

            if(use_normal) {
                glEnable(GL_LIGHTING);
            } else {
                glDisable(GL_LIGHTING);
            }

            for (i = 0; i < this->getFaceNumber(); i++) {
                Face *f = this->getFace(i);
                glBegin(f->getType());
                for (j = 0; j < f->getIndexNumber(); j++) {
                    //pushMatrix
                    int index = f->getIndex(j);
                    if (this->getNormal(index) != NULL) {
                        glNormal3fv(&this->getNormal(index)->x);
                    }
                    glVertex3fv(&(this->getVertex(index)->getPosition()).x);
                    //popMatrix
                }
                glEnd();
            }

        }
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
};

#endif
