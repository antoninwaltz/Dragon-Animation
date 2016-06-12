#ifndef __BONEANIM_H__
#define __BONEANIM_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vertice.h>
#include <bone.h>
#include <mesh.h>
#include <interpolation.h>
#include <keyframe.h>
#include <vectorKey.h>
#include <rotKey.h>

class BoneAnim{
private:
	//Keyframe* keyframeList;
	VectorKey* transList;
	VectorKey* scalList;
	RotKey* rotList;
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

	BoneAnim(int nt, int ns, int nr){
		nbTrans=nt;
		nbScal=ns;
		nbRot=nr;
		transList = (VectorKey*)malloc(nbTrans*sizeof(VectorKey));
		scalList = (VectorKey*)malloc(nbscal*sizeof(VectorKey));
		rotList = (RotKey*)malloc(nbrot*sizeof(RotKey));
		ciT=0;
		ciS=0;
		ciR=0;
	}

	void addTrans(VectorKey nT){
		if(ciT<nbTrans){
			transList[ciT]=nT;
			ciT++;
		}
	}

	void addScal(VectorKey nS){
		if(ciS<nbScal){
			scalList[ciS]=nS;
			ciS++;
		}
	}

	void addRot(RotKey nR){
		if(ciR<nbRot){
			rotList[ciR]=nR;
			ciR++;
		}
	}

	int getNbTrans(){return nbTrans;};
	int getNbScal(){return nbScal;};
	int getNbRot(){return nbRot;};

	VectorKey* getTrans(){return transList;};
	VectorKey* getScal(){return scalList;};
	RotKey* getRot(){return rotList;};


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