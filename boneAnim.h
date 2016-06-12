#ifndef __BONEANIM_H__
#define __BONEANIM_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vertice.h>
#include <bone.h>
#include <mesh.h>
#include <interpolation.h>

class BoneAnim
{
    private:
    	aiString boneName;
        //Keyframe* keyframeList;
        aiVectorKey* transList;
        aiVectorKey* scalList;
        aiQuatKey* rotList;
        //int nbKeyframe;
        int nbTrans,nbScal,nbRot;
        //int* indexKeyframeList;
        //int currentindex;
        int ciT,ciS,ciR;

    public:
        /*BoneAnim(int nbKf){
          nbKeyframe = nbKf;
          keyframeList = (Keyframe*)malloc(nbKf*sizeof(Keyframe));
          indexKeyframeList = (int*)malloc(nbKf*sizeof(int));
          currentindex=0;
          }*/

        BoneAnim(int nt, int nr, int ns, aiString name){
            boneName=name;
            nbTrans=nt;
            nbRot=nr;
            nbScal=ns;
            transList = (aiVectorKey*)malloc(nbTrans*sizeof(aiVectorKey));
            rotList = (aiQuatKey*)malloc(nbRot*sizeof(aiQuatKey));
            scalList = (aiVectorKey*)malloc(nbScal*sizeof(aiVectorKey));
            ciT=0;
            ciS=0;
            ciR=0;
        }

        void addTrans(aiVectorKey nT){
            if(ciT<nbTrans){
                transList[ciT]=nT;
                ciT++;
            }
        }

        void addScal(aiVectorKey nS){
            if(ciS<nbScal){
                scalList[ciS]=nS;
                ciS++;
            }
        }

        void addRot(aiQuatKey nR){
            if(ciR<nbRot){
                rotList[ciR]=nR;
                ciR++;
            }
        }
        aiString getName(){return boneName;};

        int getNbTrans(){return nbTrans;};
        int getNbScal(){return nbScal;};
        int getNbRot(){return nbRot;};

        aiVectorKey* getTrans(){return transList;};
        aiVectorKey* getScal(){return scalList;};
        aiQuatKey* getRot(){return rotList;};


        /*void addKeyFrame(Keyframe nKeyframe){
          int nIndex=nKeyframe.getIndex();
          if(currentindex<nbKeyframe){
          keyframeList[currentindex]=nKeyframe;
          indexKeyframeList[currentindex]=nIndex;
          currentindex++;
          }
          }

          Keyframe* getKeyframes(){
          return keyframeList;
          };

          int* getIndexKeyframes(){
          return indexKeyframeList;
          };

          int getNbKeyframes(){
          return nbKeyframe;
          }*/

};

#endif
