/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2016
 */

#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include <vectors.h>

class Model
{
    public:
        void loadFile(const char *filename);
        void saveModel();
        void printVertex();

    private:
        std::vector<Vec3> vertex_list;
        std::vector<int> face_index_list;

        float max_x;
        float min_x;
        float max_y;
        float min_y;
        float max_z;
        float min_z;
};

#endif

