#ifndef __MESH_H__
#define __MESH_H__

#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vectors.h>
#include <vertice.h>
#include <bone.h>

class Mesh{

	private:
		Vertice* verticeList;
        Bone* boneList;
        int nbVert,nbBone;

	public:
		Mesh(int vertSize, int boneSize){
			nbVert=vertSize;
			nbBone=boneSize;
			verticeList = (Vertice*)malloc(vertSize*sizeof(Vertice));
    		boneList = (Bone*)malloc(boneSize*sizeof(Bone));
		};

		void addVertice(Vertice vert,int index){
			if (index<nbVert){
				verticeList[index]=vert;
			}
		};

		void setVertBone(int index,aiString boneID,float weight){
			if(index<nbVert){
				verticeList[index].setBones(boneID,weight);
			}			
		};

		void addBone(Bone bone, int index){
			if (index<nbBone){
				boneList[index]=bone;
			}
		}

		int getNbVert(){return nbVert;};
		int getNbBone(){return nbBone;};

		Vertice* getVert(){return verticeList;};
		Bone* getBone(){return boneList;};
};

#endif