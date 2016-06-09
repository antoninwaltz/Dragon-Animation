#ifndef __BONE_H__
#define __BONE_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>

class Bone{
	private:
		int ID;
		int* verticeIDList;
		int nbVertice;

	public:
		Bone(int id);

		void addVertice(int vert_id);

		int* getListofVertices();
};
#endif