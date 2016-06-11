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

class Face {
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

class Mesh{
    private:
        Vertice **verticeList;
        aiVector3D **normalList;
        Bone **boneList;
        Face **faceList;
        int vertNb, boneNb, faceNb, maxFaceNb;
        int mesh_id;

    public:
        Mesh(int mesh_id, int vertSize, int boneSize, int faceSize){
            vertNb = vertSize;
            boneNb = boneSize;
            faceNb = 0;
            maxFaceNb = faceSize;
            mesh_id = mesh_id;
            verticeList = (Vertice**)malloc(vertNb * sizeof(Vertice*));
            normalList = (aiVector3D**)malloc(vertNb * sizeof(aiVector3D*));
            boneList = (Bone**)malloc(boneNb * sizeof(Bone*));
            faceList = (Face**)malloc(faceSize * sizeof(Face*));
        };

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
};

#endif
