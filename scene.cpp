/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>
#include <time.h>


#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <scene.h>
#include <utils.h>

using namespace std;

const aiNode *getNode(const aiScene *scene, aiString name) {
    if (name == scene->mRootNode->mName)
        return &(*scene->mRootNode);
    else
        return getChildNode(name, scene->mRootNode);
}

const aiNode *getChildNode(aiString name, const aiNode *node) {
    if (name == node->mName)
        return node;
    else {
        const aiNode *nd = NULL;
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            nd = getChildNode(name, node->mChildren[i]);
            if (nd != NULL) return nd;
        }
        return NULL;
    }
}


SceneHandler::~SceneHandler() {
    aiReleaseImport(scene);
}

SceneHandler::SceneHandler(char *fName, GLuint prog) {
    scene = aiImportFile(fName,aiProcessPreset_TargetRealtime_MaxQuality);

    if (!scene) {
        std::cerr << "Error importing file" << std::endl;
    } else {
        shaderProg = prog;

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
        meshNumber = 0;
        meshList = NULL;
        isAnimating=false;
        initMeshList(scene->mRootNode);

        // Shader variable
        m_WVPLocation = glGetUniformLocation(prog, "gWVP");
        m_WorldMatrixLocation = glGetUniformLocation(prog, "gWorld");
    }
}

void SceneHandler::initMeshList(const aiNode* nd){
    unsigned int i, j, k;

    meshList = (Mesh**) realloc(meshList, (nd->mNumMeshes + meshNumber) * sizeof(Mesh*));
    for (i = 0; i < nd->mNumMeshes; ++i) {
        const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[i]];
        Mesh *newMesh = new Mesh(i, mesh->mNumVertices, mesh->mNumBones, mesh->mNumFaces, shaderProg);
        for(j = 0; j < mesh->mNumVertices; j++){
            Vertice *newVert = new Vertice(j, mesh->mVertices[j]);
            if (mesh->mNormals != NULL) {
                newMesh->addVertice(newVert, mesh->mNormals+j, j);
            } else {
                newMesh->addVertice(newVert, NULL, j);
            }
        }
        for (j = 0; j < mesh->mNumFaces; ++j) {
            const struct aiFace* face = &mesh->mFaces[j];
            Face *newFace = new Face(face->mNumIndices);
            for(k = 0; k < face->mNumIndices; k++) {
                newFace->addIndex(face->mIndices[k]);
            }
            newMesh->addFace(newFace);
        }
        struct aiBone** bones = mesh->mBones;
        for (j = 0; j < mesh->mNumBones; ++j) {
            const aiNode *p = getNode(scene, bones[j]->mName);
            Bone *tmpBone = NULL;
            if (p != NULL) p = p->mParent;
            if (p != NULL) tmpBone = new Bone(bones[j]->mName, p->mName, bones[j]->mOffsetMatrix);
            else tmpBone = new Bone(bones[j]->mName, aiString(""), bones[j]->mOffsetMatrix);
            for(k = 0; k < bones[j]->mNumWeights; k++){
                int vertID = bones[j]->mWeights[k].mVertexId;
                float weight =bones[j]->mWeights[k].mWeight;
                tmpBone->addVertice(vertID);
                newMesh->setVertBone(vertID, bones[j]->mName, weight);
            }
            newMesh->addBone(tmpBone, j);
        }
        newMesh->initAnimList(scene);
        meshList[meshNumber++] = newMesh;
    }
    for (unsigned int n = 0; n < nd->mNumChildren; ++n) {
        initMeshList(nd->mChildren[n]);
    }

}

void SceneHandler::resetNumFrame(){
    numFrame=0;
    m_startTime = clock();
}

void SceneHandler::render() {
    int i;
    const aiNode *nd = scene->mRootNode;
    aiMatrix4x4 m = nd->mTransformation;

    double runningTime = double(clock() - m_startTime) / CLOCKS_PER_SEC;

    glScalef(scale, scale, scale);

    glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

    angle += 0.5;
    glRotatef(angle, 0, 1, 0);

    // add root node transform matrix
    aiMatrix4x4 wm;
    glGetFloatv(GL_MODELVIEW_MATRIX, &wm.a1);
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)&wm.a1);

    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)&m.a1);


    // draw all meshes
    for (i = 0; i < meshNumber; ++i) {
        aiMatrix4x4 ident;
        aiMatrix4x4::Scaling(aiVector3D(1, 1, 1), ident);
        Mesh *my_mesh = meshList[i];
        if (isAnimating) my_mesh->updateBoneStateList(runningTime, scene->mRootNode, ident);
        my_mesh->render(isAnimating);
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


