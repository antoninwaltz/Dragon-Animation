#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>
#include <keyframe.h>

class Interpolation{
	private:
		Keyframe prevKeyframe;
		int indexPrevKeyframe;
		Keyframe nextKeyframe;
		int indexNextKeyframe;
		int dist;

	public:
		Interpolation(Keyframe prev, Keyframe next, int prevI, int nextI){
			prevKeyframe=prev;
			nextKeyframe=next;
			indexPrevKeyframe=prevI;
			indexNextKeyframe=nextI;
			dist=indexNextKeyframe - indexPrevKeyframe;
		};

		void Update(Keyframe newK, int index){
			prevKeyframe=nextKeyframe;
			indexPrevKeyframe=indexNextKeyframe;
			nextKeyframe=newK;
			indexNextKeyframe=index;
			dist=indexNextKeyframe - indexPrevKeyframe;
		};

		float getPrevFactor(int currentIndex){
			float fact;
			fact=(float)(1-((currentIndex-indexPrevKeyframe)/dist));
			return fact;
		};

		float getNextFactor(int currentIndex){
			float fact;
			fact=(float)((currentIndex-indexPrevKeyframe)/dist);
			return fact;
		};
};
#endif