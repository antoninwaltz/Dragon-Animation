#ifndef __SCENE_H__
#define __SCENE_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class SceneHandler;

#include <vertice.h>
#include <bone.h>
#include <mesh.h>
#include <interpolation.h>
#include <keyframe.h>
#include <boneAnim.h>
#include <utils.h>

#define min(x,y) (x<y?x:y)
#define max(x,y) (y>x?y:x)

const aiNode *getNode(const aiScene *scene, aiString name);
const aiNode *getChildNode(aiString name, const aiNode *node);

class SceneHandler
{
    private:
        const struct aiScene* scene;
        Mesh **meshList;
        int meshNumber;
        aiVector3D scene_min, scene_max, scene_center;
        float scale, angle;
        int numFrame;
        bool isAnimating;
        unsigned int numAnimation;
        clock_t m_startTime;

    public:
        virtual ~SceneHandler();
        bool load_file (char * fName);
        void initMeshList(const aiNode *nd);
        void render();
        void get_bounding_box_for_node (const aiNode* nd, aiMatrix4x4* trafo);
        void get_bounding_box ();
        void resetNumFrame();
        const aiScene *getScene() { return scene; };
        void activateAnimation(bool b){if(numAnimation<=scene->mNumAnimations){isAnimating=b;}};
        int getMeshNumber() { return meshNumber; };
        void setNumAnimation(int n) {
            for (int i = 0; i < meshNumber; i++) {
                meshList[i]->setCurrentAnim(n);
            }
            numAnimation=n;
        };
        bool getAnimating(){return isAnimating;};


};

#endif
