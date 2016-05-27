/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2016
 */

#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include <vectors.h>


class FaceVertex
{
    private:
        int v[3];

    public:
        FaceVertex() { v[0] = 0; v[1] = 0; v[2] = 0; }
        friend std::ostream& operator<<(std::ostream& os, const FaceVertex& v) {
            return os << "(" << v.v[0] << ", " << v.v[1] << ", " << v.v[2] << ")";
        }
        friend std::istream& operator>>(std::istream& is, FaceVertex& obj);
        int getVertexIndex() { return v[0]; }

};

class Face
{
    private:
        FaceVertex v1, v2, v3;

    public:
        Face(FaceVertex V1, FaceVertex V2, FaceVertex V3) : v1(V1), v2(V2), v3(V3) {}
        friend std::ostream& operator<<(std::ostream& os, const Face& f) {
            return os << f.v1 << f.v2 << f.v3;
        }
        int getV1() { return v1.getVertexIndex(); }
        int getV2() { return v2.getVertexIndex(); }
        int getV3() { return v3.getVertexIndex(); }
};

class Model
{
    public:
        Model();
        void loadFile(const char *filename);
        void display();
        void updateScale();
        void updatePos();
        void printVertex();
        std::vector<Face> getFaceList() {
            return this->face_list;
        }
        Face getFace(int i) {
            return this->face_list[i];
        }
        std::vector<Vec3> getVertexList() {
            return this->vertex_list;
        }
        Vec3 getVertex(int i) {
            return this->vertex_list[i];
        }

    private:
        std::vector<Vec3> vertex_list;
        std::vector<Vec2> texture_list;
        std::vector<Face> face_list;

        float max_x;
        float min_x;
        float max_y;
        float min_y;
        float max_z;
        float min_z;

        float scale, angle;
        Vec3 center;
};

#endif

