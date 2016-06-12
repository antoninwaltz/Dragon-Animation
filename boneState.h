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

		VectInterpolation transInter;
		VectInterpolation scalInter;
		RotInterpolation rotInter;
	public:
		BoneState(){

		};

		aiVector3D* getCurrTrans(){return currTrans;};
		aiVector3D* getCurrScal(){return currScale;};
		aiQuaternion* getCurrRot(){return currRot;};

		aiString &getName(){ return boneName; };

};

#endif
