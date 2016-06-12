#ifndef __SCENE_H__
#define __SCENE_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vertice.h>
#include <bone.h>
#include <mesh.h>
#include <interpolation.h>
#include <keyframe.h>
#include <animation.h>
#include <boneAnim.h>

#define min(x,y) (x<y?x:y)
#define max(x,y) (y>x?y:x)

class SceneHandler
{
    public:
        virtual ~SceneHandler();
        bool load_file (char * fName);
        void initMeshList(const aiNode *nd);
        void initAnimList(const aiNode *nd);
        void render();
        void get_bounding_box_for_node (const aiNode* nd, aiMatrix4x4* trafo);
        void get_bounding_box ();
        void resetNumFrame();
        void activateAnimation(bool b){if(numAnimation<=scene->mNumAnimations){isAnimating=b;}};
        int getMeshNumber() { return meshNumber; };
        void setNumAnimation(int n){numAnimation=n;};


    private:
        const struct aiScene* scene;
        Mesh **meshList;
        Animation* animList;
        int meshNumber, animNumber;
        aiVector3D scene_min, scene_max, scene_center;
        float scale, angle;
        int numFrame;
        bool isAnimating;
        unsigned int numAnimation;

};

#endif
