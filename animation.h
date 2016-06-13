#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//#include <vertice.h>
//#include <bone.h>
//#include <interpolation.h>
//#include <keyframe.h>
#include <boneAnim.h>

class Animation
{
    private:
        BoneAnim **listBoneAnim;
        int nbBoneAnim;
        int currentindex;
        float animationTime;
        float ticksPerSecond;

    public:
        Animation(int nbBone, float t, float tps){
            nbBoneAnim = nbBone;
            animationTime = t;
            ticksPerSecond = tps;
            listBoneAnim = (BoneAnim**) malloc(nbBone*sizeof(BoneAnim*));
            currentindex=0;
        };

        void addBoneAnim(BoneAnim *bone){
            if(currentindex < nbBoneAnim){
                listBoneAnim[currentindex] = bone;
                currentindex++;
            }
        }

        BoneAnim* getBoneAnim(const aiString &boneName){
            int i=0;
            while ( i < nbBoneAnim && listBoneAnim[i]->getName() != boneName) {
                i++;
            }

            if (i < nbBoneAnim) {
                return listBoneAnim[i];
            } else {
                return NULL;
            }
        }

        float getDuration() { return animationTime; };
        float getTicksPerSecond() { return ticksPerSecond; };

        BoneAnim** getBonesAnims(){
            return listBoneAnim;
        }

        int getNbBonesAnim(){
            return nbBoneAnim;
        }

};

#endif
