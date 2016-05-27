/*
 * Skia < lordbanana25 AT mailoo DOT org >
 *
 * Beerware licensed software - 2016
 */
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <GL/gl.h>

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

Model::Model() {
    min_x = min_y = min_z = std::numeric_limits<float>::max();
    max_x = max_y = max_z = std::numeric_limits<float>::min();
    scale = 1;
    angle = 0;
}

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

                if (x < min_x) min_x = x;
                if (x > max_x) max_x = x;
                if (y < min_y) min_y = y;
                if (y > max_y) max_y = y;
                if (z < min_z) min_z = z;
                if (z > max_z) max_z = z;

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
        this->updateScale();
        this->updatePos();
    } else {
        cout << "Can not open file" << endl;
    }
}

void Model::updateScale() {
    float max = std::numeric_limits<float>::min();
    float x = max_x - min_x;
    float y = max_y - min_y;
    float z = max_z - min_z;

    if (x > max)
        max = x;
    if (y > max)
        max = y;
    if (z > max)
        max = z;

    scale = 2. / max;
}

void Model::updatePos() {
    center = Vec3(
            (max_x - min_x) / 2,
            (max_y - min_y) / 2,
            (max_z - min_z) / 2
            );
    cout << "Center: " << center << endl;
}

void Model::display() {
    glPushMatrix();
    glScalef(scale, scale, scale);
    glTranslatef(-center.x, -center.y, -center.z);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    angle += 0.9;

    glBegin(GL_TRIANGLES); // TODO maybe move that to some glDrawArray for optimization?
        unsigned int size = face_list.size();
        for (unsigned int i = 0; i < size; i++)
        {
            Face f = face_list[i];
            Vec3 v = vertex_list[f.getV1()-1];
            glColor3f((i%3)==0, (i%3)==1, (i%3)==2);
            glVertex3f(v.x, v.y, v.z);
            v = vertex_list[f.getV2()-1];
            glVertex3f(v.x, v.y, v.z);
            v = vertex_list[f.getV3()-1];
            glVertex3f(v.x, v.y, v.z);
        }
    glEnd();
    glPopMatrix();
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


