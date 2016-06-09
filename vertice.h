#ifndef __VERTICE_H__
#define __VERTICE_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>

class Vertice{
	private:
		int ID;
		Vec3 position;
		int[] bonesID = new int[4];
		float[] bonesWeight = new float[4];

	public:
		/* Constructor */
		Vertice(int id,Vec3 pos, int* b_id, float* b_wght)
		{
			ID=id;
			position=pos;
			bonesID=b_id;
			bonesWeight=b_wght;
		}

		/*seter */
		void setPosition(Vec3 pos){position=pos}

		/*getter*/
		int getID(){return ID} 

		Vec3 getPosition(){return position}

		int* getBonesID(){return bonesID}

		float* getBonesWeight(){return bonesWeight}



};

#endif