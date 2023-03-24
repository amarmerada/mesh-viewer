//-----------------------------------------------------------
// Author: Abigail Marmer-Adams
// Date: 3/18/2023
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
      initBuffers(&_faces, &_positions, &_normals, &_texCoords);
   }

   PLYMesh::~PLYMesh() {
   }

   bool PLYMesh::load(const std::string& filename) {
     
        
  if (_positions.size() != 0) {
        std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
        return false;
    }

    ifstream myFile(filename);
    if (!myFile.is_open()) {
        return false;
    }

    string data;
    myFile >> data;
    if (data.compare("ply") != 0) {
        return false;
    }

    int numVtx = 0;
    int numFace = 0;
    while ((data.compare("end_header") != 0)) {
        getline(myFile, data);
        stringstream strstr;
        strstr << data;
        string section;
        string part;
        int num;
        strstr >> section;
        strstr >> part;
        strstr >> num;
        if (section.compare("element") == 0 ) {
            strstr >> num;
            if (part.compare("vertex") == 0) {
                numVtx = num;
            }
            else if (part.compare("face") == 0) {
                numFace = num;
            }
        }
    }

    GLfloat maxx = -100000;
    GLfloat maxy = -100000;
    GLfloat maxz = -100000;
    GLfloat minx = 100000;
    GLfloat miny = 100000;
    GLfloat minz = 100000;
    for (int i = 0; i < numVtx; i++) {
        getline(myFile, data);
        stringstream strstr;
        strstr << data;
        float a, b, c, d, e, f, u, v;
        strstr >> a;
        strstr >> b;
        strstr >> c;
        minx = glm::min(a, minx);
        miny = glm::min(b, miny);
        minz = glm::min(c, minz);
        maxx = glm::max(a, maxx);
        maxy = glm::max(b, maxy);
        maxz = glm::max(c, maxz);
        _positions.push_back(a);
        _positions.push_back(b);
        _positions.push_back(c);
        strstr >> d;
        strstr >> e;
        strstr >> f;
        _normals.push_back(d);
        _normals.push_back(e);
        _normals.push_back(f);
        strstr >> u;
        strstr >> v;
        _texCoords.push_back(u);
        _texCoords.push_back(v);
    }

    maxB = { maxx, maxy, maxz };
    minB = { minx, miny, minz };

    for (int j = 0; j < numFace; j++) {
        int hold, a, b, c, d;
        myFile >> hold;
        myFile >> a;
        myFile >> b;
        myFile >> c;
        _faces.push_back(a);
        _faces.push_back(b);
        _faces.push_back(c);
        if (hold > 3) {
            hold = hold - 3;
            for (int k = 0; k < hold; k++) {
                myFile >> d;
                _faces.push_back(a);
                _faces.push_back(d);
                _faces.push_back(d);
            }
        }
        
    }

    return true;
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

   void PLYMesh::clear(){
      _positions.clear();
      _normals.clear();
      _faces.clear();
   }
}
