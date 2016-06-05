#ifndef __SCENE_H__
#define __SCENE_H__

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define min(x,y) (x<y?x:y)
#define max(x,y) (y>x?y:x)

class SceneHandler
{
    public:
        virtual ~SceneHandler();
        bool load_file (char * fName);
        void render();
        void recursive_render (const struct aiNode* nd);
        void get_bounding_box_for_node (const aiNode* nd, aiMatrix4x4* trafo);
        void get_bounding_box ();

    private:
        const struct aiScene* scene;
        aiVector3D scene_min, scene_max, scene_center;
        float scale, angle;
};

#endif
