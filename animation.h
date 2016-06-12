#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vertice.h>
#include <bone.h>
#include <mesh.h>
#include <interpolation.h>
#include <keyframe.h>
#include <boneAnim.h>

class Animation{
private:
	BoneAnim* listBoneAnim;
	int nbBoneAnim;
	int currentindex;

public:
	Animation(int nbBone){
		nbBoneAnim = nbBone;
		listBoneAnim = (BoneAnim*)malloc(nbBone*sizeof(BoneAnim));
		currentindex=0;
	};

	void addBoneAnim(BoneAnim bone){
		if(currentindex<nbBoneAnim){
			listBoneAnim[currentindex]=bone;
			currentindex++;
		}
	}

	BoneAnim* getBonesAnims(){
		return listBoneAnim;
	}

	int getNbBonesAnim(){
		return nbBoneAnim;
	}

};

#endif