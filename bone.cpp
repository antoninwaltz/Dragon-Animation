#include <bone.h>

Bone::Bone(int id){
	ID=id;
	nbVertice=0;
	verticeIDList=(int*)malloc(nbVertice*sizeof(int));
}

void Bone::addVertice(int vert_id){
	int* tmp;
	tmp=(int*)realloc(verticeIDList,(nbVertice+1)*sizeof(int));
	verticeIDList=tmp;
	verticeIDList[nbVertice]=vert_id;
}

int* Bone::getListofVertices(){
	return verticeIDList;
}