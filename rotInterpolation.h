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
#include <vectorKey.h>
#include <rotKey.h>

class RotInterpolation{
    private:
        RotKey prevKeyframe;
        int indexPrevKeyframe;
        RotKey nextKeyframe;
        int indexNextKeyframe;
        int dist;

    public:
        RotInterpolation(RotKey prev, RotKey next, int prevI, int nextI){
            prevKeyframe = prev;
            nextKeyframe = next;
            indexPrevKeyframe = prevI;
            indexNextKeyframe = nextI;
            dist = indexNextKeyframe - indexPrevKeyframe;
        };

        RotInterpolation(){

        };

        void Update(RotKey newK, int index){
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

        aiQuaternion interpolateRot(int index){
            aiQuaternion rot;
            rot.Interpolate(rot,prevKeyframe.getKey().mValue,nextKeyframe.getKey().mValue, getFactor(index) );
            return rot;
        }



};
#endif