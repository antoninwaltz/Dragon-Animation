#ifndef __VECTINTERPOLATION_H__
#define __VECTINTERPOLATION_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>
#include <vectorKey.h>
#include <rotKey.h>

class VectInterpolation{
    private:
        VectorKey prevKeyframe;
        int indexPrevKeyframe;
        VectorKey nextKeyframe;
        int indexNextKeyframe;
        int dist;

    public:
        Interpolation(VectorKey prev, VectorKey next, int prevI, int nextI){
            prevKeyframe = prev;
            nextKeyframe = next;
            indexPrevKeyframe = prevI;
            indexNextKeyframe = nextI;
            dist = indexNextKeyframe - indexPrevKeyframe;
        };

        void Update(VectorKey newK, int index){
            prevKeyframe = nextKeyframe;
            indexPrevKeyframe = indexNextKeyframe;
            nextKeyframe = newK;
            indexNextKeyframe = index;
            dist = indexNextKeyframe - indexPrevKeyframe;
        };

        float getFactor(int currentIndex){
            float fact;
            fact = (float)((currentIndex-indexPrevKeyframe)/dist);
            return fact;
        };

        aiVector3D InterpolateVect(int index){
            aiVector3D pos;
            float t = getFactor(index);
            pos= (1-t)*prevKeyframe.getKey().mValue + t*nextKeyframe.getKey().mValue;
            return pos;
        }



};
#endif