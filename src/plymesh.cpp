//-----------------------------------------------------------
// Author: Abigail Marmer-Adans
// Date: 3/2/2023
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include "plymesh.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

using namespace std;
using namespace glm;

namespace agl {

    PLYMesh::PLYMesh(const std::string& filename) {
        load(filename);
    }

    PLYMesh::PLYMesh() {
    }

    void PLYMesh::init() {
        assert(_positions.size() != 0);
        initBuffers(&_faces, &_positions, &_normals);
    }

    PLYMesh::~PLYMesh() {
    }

    bool PLYMesh::load(const std::string& filename) {
        if (_positions.size() != 0) {
            std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
            return false;
        }
        // todo: your code here
        //you need to load ALL your models at the start of the program, so you cant reuse a plymesh, you
        //need to make an array of plymeshes and load them in setup
        ifstream myFile;
        myFile.open(filename);
        if (!myFile.is_open()) {
            return false;
        }
        printf("here 1\n");
        string data;
        myFile >> data;
        if (data.compare("ply") != 0) {
            printf("here false\n");
            return false;
        }
        printf("here 2\n");
        while (data.compare("vertex") != 0) {
            myFile >> data;
        }
        myFile >> data;
        stringstream strstr;
        printf("here 3\n");
        int numVtx;
        strstr << data;
        strstr >> numVtx;
        while (data.compare("face") != 0) {
            myFile >> data;
        }
        printf("here 4\n");
        myFile >> data;
        int numFace;
        stringstream strstr2;
        strstr2 << data;
        strstr2 >> numFace;
        while (data.compare("end_header") != 0) {
            myFile >> data;
        }
        GLfloat maxx = -100000;
        GLfloat maxy = -100000;
        GLfloat maxz = -100000;
        GLfloat minx = 100000;
        GLfloat miny = 100000;
        GLfloat minz = 100000;
        for (int i = 0; i < numVtx; i++) {
            GLfloat a, b, c, d, e, f;
            myFile >> a;
            myFile >> b;
            myFile >> c;
            minx = std::min(a, minx);
            miny = glm::min(b, miny);
            minz = glm::min(c, minz);
            maxx = glm::max(a, maxx);
            maxy = glm::max(b, maxy);
            maxz = glm::max(c, maxz);
            myFile >> d;
            myFile >> e;
            myFile >> f;
            _positions.push_back(a);
            _positions.push_back(b);
            _positions.push_back(c);
            _normals.push_back(d);
            _normals.push_back(e);
            _normals.push_back(f);
            myFile >> data;
            myFile >> data;
        }
        maxB = vec3{ maxx, maxy, maxz };
        minB = vec3{ minx,miny,minz }; 
        for (int i = 0; i < numFace; i++) {
            myFile >> data;
            GLuint a, b, c;
            myFile >> a;
            myFile >> b;
            myFile >> c;
            _faces.push_back(a);
            _faces.push_back(b);
            _faces.push_back(c);
        }
        printf("loaded with %d verticies and %d faces\n", _positions.size()/3, _faces.size()/3);

        return false;
    }

    glm::vec3 PLYMesh::minBounds() const {
        return minB;
    }

    glm::vec3 PLYMesh::maxBounds() const {
        return maxB;
    }

    int PLYMesh::numVertices() const {
        return _positions.size()/3;
    }

    void PLYMesh::clear() {
        _positions.clear();
        _faces.clear();
        _normals.clear();
        maxB = vec3( - 100000, -100000, -100000);
        minB = vec3(100000, 100000, 100000);
    }

    int PLYMesh::numTriangles() const {
        return _faces.size()/3;
    }

    const std::vector<GLfloat>& PLYMesh::positions() const {
        return _positions;
    }

    const std::vector<GLfloat>& PLYMesh::normals() const {
        return _normals;
    }

    const std::vector<GLuint>& PLYMesh::indices() const {
        return _faces;
    }
}
