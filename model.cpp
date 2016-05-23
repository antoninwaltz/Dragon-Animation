/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2016
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <model.h>

#include <vectors.h>

using namespace std;

void Model::loadFile(const char *filename) {
    ifstream fileStream(filename);

    if (fileStream.is_open()) {
        while (!fileStream.eof()) {
            char buf[256];
            fileStream.getline(buf, 256, '\n');
            istringstream bufStream(buf);

            string type;
            bufStream >> type;
            // cout << "Type: " << type << "\n";
            if (type == "v") {
                float x, y, z;
                bufStream >> x >> y >> z;
                Vec3 v(x, y, z);

                this->vertex_list.push_back(v);                      // save the values into the vector vertex_list of
                // cout << "Vertex: " << v << "\n";

                //cout << this->vertex_list.size() << endl;
            } else if (type == "f") {
                int f[3] = {0};
                bufStream >> f[0] >> f[1] >> f[2];
                this->face_index_list.push_back(f[0]);
                this->face_index_list.push_back(f[1]);
                this->face_index_list.push_back(f[2]);
            } else {
                cout << "Unknown type: " << type << endl;
            }
        }
    }
}

void Model::printVertex() {
    for (unsigned int i = 0; i < this->vertex_list.size(); i++) {
        cout << "Vertex: " << this->vertex_list[i] << "\n";
    }
    for (unsigned int i = 0; i < this->face_index_list.size(); i+=3) {
        cout << "Face: "
            << this->face_index_list[i]
            << " "
            << this->face_index_list[i+1]
            << " "
            << this->face_index_list[i+2]
            << "\n";
    }
}


