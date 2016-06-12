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

class BoneAnim{
private:
	Keyframe* keyframeList;
	int nbKeyframe;
	int* indexKeyframeList;
	int currentindex;

public:
	BoneAnim(int nbKf){
		nbKeyframe = nbKf;
		keyframeList = (Keyframe*)malloc(nbKf*sizeof(Keyframe));
		indexKeyframeList = (int*)malloc(nbKf*sizeof(int));
		currentindex=0;
	}

	void addKeyFrame(Keyframe nKeyframe){
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
	}

};

#endif