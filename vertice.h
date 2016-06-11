#ifndef __VERTICE_H__
#define __VERTICE_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>

class Vertice {
    private:
        int ID;
        aiVector3D position;
        aiString bonesName[4];
        float bonesWeight[4];

    public:
        /* Constructor */
        Vertice(int id,aiVector3D pos)
        {
            int i;
            ID=id;
            position=pos;
            for(i=0;i<4;i++){
                bonesName[i]=aiString();
                bonesWeight[i]=0.0f;
            }
        };

        void setBones(aiString boneID, float weight){
            int i=0;
            while (bonesName[i].length!=0 && i<4){
                i++;
            }
            if(i<4){
                bonesName[i]=boneID;
                bonesWeight[i]=weight;
            }
        };

        /*seter */
        void setPosition(aiVector3D pos){position=pos;};

        /*getter*/
        int getID(){return ID;};

        aiVector3D &getPosition(){return position;};

        aiString* getBonesID(){return bonesName;};

        float* getBonesWeight(){return bonesWeight;};



};

#endif
