#ifndef __BONESTATE_H__
#define __BONESTATE_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vertice.h>
#include <bone.h>
#include <mesh.h>
#include <vectInterpolation.h>
#include <rotInterpolation.h>

class BoneState{
	private:

		aiString boneName;

		aiVector3D* currTrans;
		aiVector3D* currScale;
		aiQuaternion* currRot;

		VectInterpolation* transInter;
		VectInterpolation* scalInter;
		RotInterpolation* rotInter;

		int iT,iS,iR;
	public:
		BoneState(aiString name){
			boneName=name;
		}

		void initTrans(aiVectorKey* prev, aiVectorKey* next, float tps){
			int newIndex = (int)next->mTime*tps;
			transInter = new VectInterpolation(*prev, *next, 1, newIndex);
			currTrans = transInter->InterpolateVect(1);
			iT=2;
		}

		void initScal(aiVectorKey* prev, aiVectorKey* next, float tps){
			int newIndex = (int)next->mTime * tps;
			scalInter = new VectInterpolation(*prev, *next, 1, newIndex);
			currScale = scalInter->InterpolateVect(1);
			iS=2;
		}


		void initRot(aiQuatKey* prev, aiQuatKey* next, float tps){
			int newIndex = (int)next->mTime*tps;
			rotInter = new RotInterpolation(*prev, *next, 1, newIndex);
			currRot = rotInter->InterpolateRot(1);
			iR=2;
		}

		void updateTransLastKey(aiVectorKey* key, float tps){
			int newIndex = (int)key->mTime * tps;
			transInter->Update(*key,newIndex);
			iT++;
		}

		void updateScalLastKey(aiVectorKey* key, float tps){
			int newIndex = (int)key->mTime * tps;
			scalInter->Update(*key,newIndex);
			iS++;
		}

		void updateRotLastKey(aiQuatKey* key, float tps){
			int newIndex = (int)key->mTime * tps;
			rotInter->Update(*key,newIndex);
			iR++;
		}

		int getiT(){return iT;};
		int getiR(){return iR;};
		int getiS(){return iS;};

		void updateTransValue(int index){
			currTrans=transInter->InterpolateVect(index);
		}

		void updateScalValue(int index){
			currScale=scalInter->InterpolateVect(index);
		}

		void updateRotValue(int index){
			currRot=rotInter->InterpolateRot(index);
		}

		int getTransLastIndex(){return transInter->getLastIndex();};
		int getScalLastIndex(){return scalInter->getLastIndex();};
		int getRotLastIndex(){return rotInter->getLastIndex();};


		aiVector3D* getCurrTrans(){return currTrans;};
		aiVector3D* getCurrScal(){return currScale;};
		aiQuaternion* getCurrRot(){return currRot;};

		aiString &getName(){ return boneName; };

};

#endif
