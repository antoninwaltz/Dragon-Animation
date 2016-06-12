#ifndef __ROTKEY_H__
#define __ROTKEY_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>

class RotKey{
    private:
        int index;
        aiQuatKey key;

    public:
        RotKey(int i,aiQuatKey k){
            index=i;
            key=k;
        };

        RotKey(){
        };

        aiQuatKey getKey(){
            return key;
        };

        int getIndex(){
            return index;
        }

};
#endif