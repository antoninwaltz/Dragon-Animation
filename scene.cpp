/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>

#include <GL/gl.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <scene.h>

SceneHandler::~SceneHandler() {
    aiReleaseImport(scene);
}

bool SceneHandler::load_file(char *fName) {
    scene = aiImportFile(fName,aiProcessPreset_TargetRealtime_MaxQuality);

    if (!scene) {
        std::cerr << "Error importing file" << std::endl;
        return 1;
    }
    get_bounding_box();
    scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
    scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
    scene_center.z = (scene_min.z + scene_max.z) / 2.0f;

    float tmp = 0;
    tmp = scene_max.x-scene_min.x;
    tmp = max(scene_max.y - scene_min.y,tmp);
    tmp = max(scene_max.z - scene_min.z,tmp);
    scale = 2.f / tmp;

    angle = 0;
    initVerticeList();
    return 0;
}

void SceneHandler::initVerticeList(){
    const struct aiNode* nd=scene->mRootNode;
    unsigned int n=0,t,u;

    meshList = (Mesh*)malloc(nd->mNumMeshes*sizeof(Mesh));
    for (; n < nd->mNumMeshes; ++n) {
        const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        Mesh tmpMesh(mesh->mNumVertices,mesh->mNumBones);

        struct aiBone** bones = mesh->mBones;
        for (t = 0; t < mesh->mNumBones; ++t) {
            for(u=0; u<mesh->mNumVertices; u++){
               Vertice newVert(u,mesh->mVertices[u]);
               tmpMesh.addVertice(newVert,u); 
            }
            Bone tmpBone(bones[t]->mName);
            for(u=0; u<bones[t]->mNumWeights; u++){
                int vertID= bones[t]->mWeights[u].mVertexId;
                float weight =bones[t]->mWeights[u].mWeight;
                tmpBone.addVertice(vertID);
                tmpMesh.setVertBone(vertID,bones[t]->mName,weight);
            }
            tmpMesh.addBone(tmpBone,t);           
        }
        meshList[n]=tmpMesh;

     }
}

void SceneHandler::render() {
    glScalef(scale, scale, scale);

    glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

    angle += 0.9;
    glRotatef(angle, 0, 1, 0);
    recursive_render(scene->mRootNode);

}

void SceneHandler::recursive_render (const struct aiNode* nd)
{
    unsigned int i;
    unsigned int n = 0, t;
    aiMatrix4x4 m = nd->mTransformation;

    // update transform
    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);

    // draw all meshes assigned to this node
    for (; n < nd->mNumMeshes; ++n) {
        const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

        // apply_material(sc->mMaterials[mesh->mMaterialIndex]);

        if(mesh->mNormals == NULL) {
            glDisable(GL_LIGHTING);
        } else {
            glEnable(GL_LIGHTING);
        }

        for (t = 0; t < mesh->mNumFaces; ++t) {
            const struct aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch(face->mNumIndices) {
                case 1: face_mode = GL_POINTS; break;
                case 2: face_mode = GL_LINES; break;
                case 3: face_mode = GL_TRIANGLES; break;
                default: face_mode = GL_POLYGON; break;
            }

            glBegin(face_mode);

            for(i = 0; i < face->mNumIndices; i++) {
                int index = face->mIndices[i];
                if(mesh->mColors[0] != NULL)
                    glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                if(mesh->mNormals != NULL)
                    glNormal3fv(&mesh->mNormals[index].x);
                glVertex3fv(&mesh->mVertices[index].x);
            }

            glEnd();
        }

    }

    // draw all children
    for (n = 0; n < nd->mNumChildren; ++n) {
        recursive_render(nd->mChildren[n]);
    }

    glPopMatrix();
}

void SceneHandler::get_bounding_box_for_node (const aiNode* nd,
        aiMatrix4x4* trafo
        ){
    aiMatrix4x4 prev;
    unsigned int n = 0, t;

    prev = *trafo;
    aiMultiplyMatrix4(trafo,&nd->mTransformation);

    for (; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        for (t = 0; t < mesh->mNumVertices; ++t) {

            aiVector3D tmp = mesh->mVertices[t];
            aiTransformVecByMatrix4(&tmp,trafo);

            scene_min.x = min(scene_min.x,tmp.x);
            scene_min.y = min(scene_min.y,tmp.y);
            scene_min.z = min(scene_min.z,tmp.z);

            scene_max.x = max(scene_max.x,tmp.x);
            scene_max.y = max(scene_max.y,tmp.y);
            scene_max.z = max(scene_max.z,tmp.z);
        }
    }

    for (n = 0; n < nd->mNumChildren; ++n) {
        get_bounding_box_for_node(nd->mChildren[n], trafo);
    }
    *trafo = prev;
}



void SceneHandler::get_bounding_box ()
{
    aiMatrix4x4 trafo;
    aiIdentityMatrix4(&trafo);

    scene_min.x = scene_min.y = scene_min.z =  1e10f;
    scene_max.x = scene_max.y = scene_max.z = -1e10f;
    get_bounding_box_for_node(scene->mRootNode,&trafo);
}


