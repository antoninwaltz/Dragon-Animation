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
	public:
		BoneState(aiString name){
			boneName=name;
		}

		void initTrans(aiVectorKey* prev, aiVectorKey* next, float tps){
			int newIndex = (int)next->mTime*tps;
			transInter = new VectInterpolation(*prev, *next, 1, newIndex);
			currTrans = transInter->InterpolateVect(1);
		}

		void initScal(aiVectorKey* prev, aiVectorKey* next, float tps){
			int newIndex = (int)next->mTime * tps;
			scalInter = new VectInterpolation(*prev, *next, 1, newIndex);
			currScale = scalInter->InterpolateVect(1);
		}


		void initRot(aiQuatKey* prev, aiQuatKey* next, float tps){
			int newIndex = (int)next->mTime*tps;
			rotInter = new RotInterpolation(*prev, *next, 1, newIndex);
			currRot = rotInter->InterpolateRot(1);
		}


		aiVector3D* getCurrTrans(){return currTrans;};
		aiVector3D* getCurrScal(){return currScale;};
		aiQuaternion* getCurrRot(){return currRot;};

		aiString &getName(){ return boneName; };

};

#endif
