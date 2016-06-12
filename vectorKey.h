#ifndef __VECTORKEY_H__
#define __VECTORKEY_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>

class VectorKey{
    private:
        int index;
        aiVectorKey key;

    public:
        VectorKey(int i,aiVectorKey k){
            index=i;
            key=k;
        };

        VectorKey(){
        };

        aiVectorKey getKey(){
            return key;
        };

        int getIndex(){
            return index;
        }

};
#endif