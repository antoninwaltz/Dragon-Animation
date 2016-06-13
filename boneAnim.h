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
        aiVectorKey* transList;
        aiVectorKey* scalList;
        aiQuatKey* rotList;
        int ciT,ciS,ciR;
        int nbTrans, nbRot, nbScal;

    public:

        BoneAnim(int nt, int nr, int ns, const aiString &name){
            boneName = name;
            nbTrans = nt;
            nbRot = nr;
            nbScal = ns;
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

        aiString &getName() {return boneName; };

        int getNbTrans(){return nbTrans;};
        int getNbScal(){return nbScal;};
        int getNbRot(){return nbRot;};

        aiVectorKey getTrans(int i){return transList[i]; };
        aiVectorKey getScal(int i){return scalList[i]; };
        aiQuatKey getRot(int i) {return rotList[i]; };


        unsigned int findScaling(float AnimationTime) {
            assert(this->nbScal > 0);
            for (int i = 0 ; i < this->nbScal - 1 ; i++) {
                if (AnimationTime < (float)this->scalList[i + 1].mTime) {
                    return i;
                }
            }
            assert(0);
        }

        unsigned int findPosition(float AnimationTime) {
            assert(this->nbTrans > 0);
            for (int i = 0 ; i < this->nbTrans - 1 ; i++) {
                if (AnimationTime < (float)this->transList[i + 1].mTime) {
                    return i;
                }
            }
            assert(0);
        }

        unsigned int findRotation(float AnimationTime) {
            assert(this->nbRot > 0);
            for (int i = 0 ; i < this->nbRot - 1 ; i++) {
                if (AnimationTime < (float)this->rotList[i + 1].mTime) {
                    return i;
                }
            }
            assert(0);
        }

};

#endif
