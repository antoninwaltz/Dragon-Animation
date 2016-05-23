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

/* Define split functions */

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

/* >> operator for class FaceVertex */
std::istream& operator>>(std::istream& is, FaceVertex& obj) {
    string s;
    is >> s;
    vector<string> tokens = split(s, '/');
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        std::istringstream ss(tokens[i]);
        ss >> obj.v[i];
        if(ss.bad())
            is.setstate(std::ios::badbit);
    }
    return is;
}


/* Model methods */

/* Main parsing function */
void Model::loadFile(const char *filename) {
    ifstream fileStream(filename);

    if (fileStream.is_open())
    {
        while (!fileStream.eof())
        {
            char buf[256];
            fileStream.getline(buf, 256, '\n');
            istringstream bufStream(buf);

            string type;
            bufStream >> type;
            /* If needed, add a material variable, that can be added to a non existent vertex class, and that would be a
             * pointer to the currently used material...
             */
            if (type == "v")
            {
                float x, y, z;
                bufStream >> x >> y >> z;
                Vec3 v(x, y, z);

                this->vertex_list.push_back(v);
            }
            else if (type == "vt")
            {
                float x, y;
                bufStream >> x >> y;
                Vec2 v(x, y);

                this->texture_list.push_back(v);
            }
            else if (type == "f")
            {
                FaceVertex v1, v2, v3;
                bufStream >> v1 >> v2 >> v3;
                this->face_list.push_back(Face(v1, v2, v3));
            }
            else if (type == "#" || type == "") // "#" defines a comment in obj files. Also skip empty lines
            {
                continue;
            }
            else
            {
                cout << "Unknown type: " << type << endl;
            }
        }
    } else {
        cout << "Can not open file" << endl;
    }
}

void Model::printVertex() {
    for (unsigned int i = 0; i < this->vertex_list.size(); i++)
    {
        cout << "Vertex: " << this->vertex_list[i] << "\n";
    }
    for (unsigned int i = 0; i < this->texture_list.size(); i++)
    {
        cout << "Texture: " << this->texture_list[i] << "\n";
    }
    for (unsigned int i = 0; i < this->face_list.size(); i+=3)
    {
        cout << "Face: " << this->face_list[i] << "\n";
    }
}


