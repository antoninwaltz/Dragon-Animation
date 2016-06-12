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
		aiString name;
		aiString parentName;
		int* verticeIDList;
		int nbVertice;

	public:
		Bone(aiString id, aiString p);

        aiString getName() { return name; };
        aiString getParentName() { return parentName; };
		void addVertice(int vert_id);

		int* getListofVertices();
};
#endif
