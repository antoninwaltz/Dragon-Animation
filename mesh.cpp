/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2015
 */
#include <iostream>

#include <mesh.h>
#include <utils.h>

void Mesh::initAnimList(const aiScene *scene) {
    animList = (Animation**) malloc(scene->mNumAnimations * sizeof(Animation*));
    for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
        const aiAnimation *anim = scene->mAnimations[i];
        Animation *my_anim = new Animation(boneNb, scene->mAnimations[i]->mDuration, scene->mAnimations[i]->mTicksPerSecond);
        for (int j = 0; j < boneNb; j++) {
            const aiNodeAnim *nodeAnim = findNodeAnim(anim, getBone(j)->getName());
            BoneAnim *boneAnim = new BoneAnim(
                    nodeAnim->mNumPositionKeys,
                    nodeAnim->mNumRotationKeys,
                    nodeAnim->mNumScalingKeys,
                    getBone(j)->getName());
            for (unsigned int k = 0; k < nodeAnim->mNumPositionKeys; k++)
                boneAnim->addTrans(nodeAnim->mPositionKeys[k]);
            for (unsigned int k = 0; k < nodeAnim->mNumRotationKeys; k++)
                boneAnim->addRot(nodeAnim->mRotationKeys[k]);
            for (unsigned int k = 0; k < nodeAnim->mNumScalingKeys; k++)
                boneAnim->addScal(nodeAnim->mScalingKeys[k]);
            my_anim->addBoneAnim(boneAnim);
        }
        animList[animNb++] = my_anim;
    }
};

void Mesh::render(bool anim) {
    int i, j;
    bool use_normal = false;
    if (this->getNormal(0) != NULL) {
        use_normal = true;
    }

    if(use_normal) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }
    // glUniformMatrix4fv(shader_bones, this->getNbBone(), GL_TRUE, boneStateList);

    for (i = 0; i < this->getFaceNumber(); i++) {
        Face *f = this->getFace(i);
        glBegin(f->getType());
        for (j = 0; j < f->getIndexNumber(); j++) {
            // glPushMatrix();
            int index = f->getIndex(j);
            if (anim) {
                Vertice *v = this->getVertex(index);
                aiMatrix4x4 t[4];
                glVertexAttribPointer(shader_Normal, 3, GL_FLOAT, GL_FALSE, 0, &this->getNormal(index)->x);
                glVertexAttribPointer(shader_Weights, 3, GL_FLOAT, GL_FALSE, 0, v->getBonesWeights());
                for (int k = 0; k < v->getBoneNumber(); k++) {
                    t[k] = boneStateList[this->getBoneIndex(v->getBonesID(k))].Transpose();
                }
                glVertexAttribPointer(shader_Weights, 3, GL_FLOAT, GL_FALSE, 0, &t);
                if (this->getNormal(index) != NULL) {
                    glVertexAttribPointer(shader_Normal, 3, GL_FLOAT, GL_FALSE, 0, &this->getNormal(index)->x);
                }
                glVertexAttribPointer(shader_Position, 3, GL_FLOAT, GL_FALSE, 0, &(this->getVertex(index)->getPosition()).x);
            } else {
                if (this->getNormal(index) != NULL) {
                    glNormal3fv(&this->getNormal(index)->x);
                }
                glVertex3fv(&(this->getVertex(index)->getPosition()).x);
            }
        }
        glEnd();
    }
}

void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, BoneAnim* boneAnim)
{
    // we need at least two values to interpolate...
    if (boneAnim->getNbScal() == 1) {
        Out = boneAnim->getScal(0).mValue;
        return;
    }

    unsigned int ScalingIndex = boneAnim->findScaling(AnimationTime);
    unsigned int NextScalingIndex = (ScalingIndex + 1);
    float d = boneAnim->getScal(NextScalingIndex).mTime - boneAnim->getScal(ScalingIndex).mTime;
    float f = (AnimationTime - (float)boneAnim->getScal(ScalingIndex).mTime) / d;
    // assert(f >= 0.0f && f <= 1.0f);
    const aiVector3D& StartPositionV = boneAnim->getScal(ScalingIndex).mValue;
    const aiVector3D& EndPositionV = boneAnim->getScal(NextScalingIndex).mValue;
    Out = (1 - f) * StartPositionV + f * EndPositionV;
}
void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, BoneAnim* boneAnim)
{
    // we need at least two values to interpolate...
    if (boneAnim->getNbTrans() == 1) {
        Out = boneAnim->getTrans(0).mValue;
        return;
    }

    unsigned int PositionIndex = boneAnim->findPosition(AnimationTime);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    float d = boneAnim->getTrans(NextPositionIndex).mTime - boneAnim->getTrans(PositionIndex).mTime;
    float f = (AnimationTime - (float)boneAnim->getTrans(PositionIndex).mTime) / d;
    // assert(f >= 0.0f && f <= 1.0f);
    const aiVector3D& StartPositionV = boneAnim->getTrans(PositionIndex).mValue;
    const aiVector3D& EndPositionV = boneAnim->getTrans(NextPositionIndex).mValue;
    Out = (1 - f) * StartPositionV + f * EndPositionV;
    // *pos = (1-t)*prevKeyframe.mValue + t*nextKeyframe.mValue;
    //Out = Out.Normalize();
}
void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, BoneAnim* boneAnim)
{
    // we need at least two values to interpolate...
    if (boneAnim->getNbRot() == 1) {
        Out = boneAnim->getRot(0).mValue;
        return;
    }

    unsigned int RotationIndex = boneAnim->findRotation(AnimationTime);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    float d = boneAnim->getRot(NextRotationIndex).mTime - boneAnim->getRot(RotationIndex).mTime;
    float f = (AnimationTime - (float)boneAnim->getRot(RotationIndex).mTime) / d;
    // assert(f >= 0.0f && f <= 1.0f);
    const aiQuaternion& StartRotationQ = boneAnim->getRot(RotationIndex).mValue;
    const aiQuaternion& EndRotationQ = boneAnim->getRot(NextRotationIndex).mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, f);
    Out = Out.Normalize();
}

bool Mesh::updateBoneStateList(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform)
{
    aiString NodeName(pNode->mName.data);

    Animation* anim = animList[currentAnimation];
    if (anim->getDuration() <= AnimationTime) return false;

    aiMatrix4x4 NodeTransformation(pNode->mTransformation);

    BoneAnim* boneAnim = anim->getBoneAnim(NodeName);

    if (boneAnim) {
        // Interpolate scaling and generate scaling transformation matrix
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, boneAnim);
        aiMatrix4x4 ScalingM;
        aiMatrix4x4::Scaling(aiVector3D(Scaling.x, Scaling.y, Scaling.z), ScalingM);

        // Interpolate rotation and generate rotation transformation matrix
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, boneAnim);
        aiMatrix4x4 RotationM = aiMatrix4x4(RotationQ.GetMatrix());

        // Interpolate translation and generate translation transformation matrix
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, boneAnim);
        aiMatrix4x4 TranslationM;
        aiMatrix4x4::Translation(aiVector3D(Translation.x, Translation.y, Translation.z), TranslationM);

        // Combine the above transformations
        NodeTransformation = TranslationM * RotationM * ScalingM;
    }

    aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;

    int BoneIndex = -1;
    if ((BoneIndex = getBoneIndex(NodeName)) != -1) {
        boneStateList[BoneIndex] = GlobalTransformation * getBone(BoneIndex)->getOffset();
    }

    for (unsigned int i = 0 ; i < pNode->mNumChildren ; i++) {
        this->updateBoneStateList(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }
    return true;
}
