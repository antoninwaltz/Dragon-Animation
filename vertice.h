#ifndef __VERTICE_H__
#define __VERTICE_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>

#define MAX_BONES 4

class Vertice {
    private:
        int ID;
        aiVector3D position;
        aiString bonesName[MAX_BONES];
        int numBone;
        float bonesWeight[MAX_BONES];

    public:
        /* Constructor */
        Vertice(int id,aiVector3D pos)
        {
            int i;
            ID=id;
            position=pos;
            for(i = 0; i < MAX_BONES; i++){
                bonesName[i] = aiString();
                bonesWeight[i] = 0.0f;
            }
            numBone = 0;
        };

        void setBones(aiString boneID, float weight){
            if(numBone < MAX_BONES){
                bonesName[numBone]=boneID;
                bonesWeight[numBone++]=weight;
            }
        };

        /*seter */
        void setPosition(aiVector3D pos){position=pos;};

        /*getter*/
        int getID(){return ID;};

        aiVector3D &getPosition(){return position;};

        aiString* getBonesID() { return bonesName; };

        int getBoneNumber() { return numBone; };

        float* getBonesWeight(){return bonesWeight;};



};

#endif
