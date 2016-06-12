#ifndef __ROTINTERPOLATION_H__
#define __ROTINTERPOLATION_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>

class RotInterpolation{
    private:
        aiQuatKey prevKeyframe;
        int indexPrevKeyframe;
        aiQuatKey nextKeyframe;
        int indexNextKeyframe;
        int dist;

    public:
        RotInterpolation(aiQuatKey prev, aiQuatKey next, int prevI, int nextI){
            prevKeyframe = prev;
            nextKeyframe = next;
            indexPrevKeyframe = prevI;
            indexNextKeyframe = nextI;
            dist = indexNextKeyframe - indexPrevKeyframe;
        };

        RotInterpolation(){

        };

        void Update(aiQuatKey newK, int index){
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

        aiQuaternion *InterpolateRot(int index){
            aiQuaternion *rot = new aiQuaternion();
            rot->Interpolate(*rot, prevKeyframe.mValue, nextKeyframe.mValue, getFactor(index) );
            return rot;
        }



};
#endif
