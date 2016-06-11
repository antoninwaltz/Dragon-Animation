#ifndef __KEYFRAME_H__
#define __KEYFRAME_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>

class Keyframe{
	private:
		int index;
		aiVectorKey position;
		aiVectorKey scaling;
		aiQuatKey rotation;
		
	public:
		Keyframe(int i,aiVectorKey scal,aiQuatKey rot, aiVectorKey pos){
			index=i;
			scaling=scal;
			rotation=rot;
			position=pos;
		};

		Keyframe(){
		};

		aiQuatKey getRotation(){
			return rotation;
		};

		aiVectorKey getPosition(){
			return position;
		};

		aiVectorKey getScaling(){
			return scaling;
		};

};
#endif