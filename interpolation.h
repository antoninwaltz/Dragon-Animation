#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>
#include <keyframe.h>

class Interpolation{
    private:
        Keyframe prevKeyframe;
        int indexPrevKeyframe;
        Keyframe nextKeyframe;
        int indexNextKeyframe;
        int dist;

    public:
        Interpolation(Keyframe prev, Keyframe next, int prevI, int nextI){
            prevKeyframe = prev;
            nextKeyframe = next;
            indexPrevKeyframe = prevI;
            indexNextKeyframe = nextI;
            dist = indexNextKeyframe - indexPrevKeyframe;
        };

        void Update(Keyframe newK, int index){
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
            rot.Interpolate(rot,prevKeyframe.getRotation().mValue,nextKeyframe.getRotation().mValue, getFactor(index) );
            return rot;
        }

        aiVector3D InterpolatePos(int index){
            aiVector3D pos;
            float t = getFactor(index);
            pos= (1-t)*prevKeyframe.getPosition().mValue + t*nextKeyframe.getPosition().mValue;
            return pos;
        }

        aiVector3D InterpolateScal(int index){
            aiVector3D scal;
            float t = getFactor(index);
            scal = (1-t)*prevKeyframe.getScaling().mValue + t*nextKeyframe.getScaling().mValue;
            return scal;
        }


};
#endif
