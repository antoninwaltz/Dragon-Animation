#ifndef __SCENE_H__
#define __SCENE_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define min(x,y) (x<y?x:y)
#define max(x,y) (y>x?y:x)

void recursive_render (const struct aiScene *sc, const struct aiNode* nd);
void get_bounding_box_for_node (const struct aiScene *sc, const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo);
void get_bounding_box (const struct aiScene *sc, aiVector3D* min, aiVector3D* max);

#endif
