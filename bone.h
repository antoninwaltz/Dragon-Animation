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
        aiMatrix4x4 offset;
		int* verticeIDList;
		int nbVertice;

	public:
		Bone(aiString id, aiString p, aiMatrix4x4 &o);

        aiString getName() { return name; };
        aiString getParentName() { return parentName; };
        aiMatrix4x4 getOffset() { return offset; };
		void addVertice(int vert_id);

		int* getListofVertices();
};
#endif
