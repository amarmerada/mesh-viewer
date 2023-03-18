//--------------------------------------------------
// Author: Abbi Marmer-Adams
// Date: 3/18/23
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
    MeshViewer() : Window() {
    }

    void setup() {
        files = GetFilenamesInDir("../models", "ply");
        for (string each : files) {
            PLYMesh eachFile;
            eachFile.load("../models/" + each);
            meshList.push_back(eachFile);
        }
        mesh = meshList[0];
        renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
        renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
        renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
    }

    void mouseMotion(int x, int y, int dx, int dy) {
        if (click) {
            ele = ele - (dy * 0.05);
            if (ele > 6.283) {
                ele = 0;
            }
            if (ele < 0) {
                ele = 6.283;
            }
            az = az - (dx * 0.05);
            if (az < -3.1415) {
                az = 3.1415;
            }
            if (az > 3.1415) {
                az = -3.1415;
            }
            
            float x = radius * cos(az) * sin(ele);
            float y = radius * cos(ele);
            float z = radius * sin(az) * sin(ele);
            eyePos = vec3(x, y, z);
        }
    }

    void mouseDown(int button, int mods) {
        click = true;
    }

    void mouseUp(int button, int mods) {
        click = false;
    }

    void scroll(float dx, float dy) {
        radius = radius + dx + dy;
        float x = radius * cos(az) * sin(ele);
        float y = radius* cos(ele);
        float z = radius* sin(az) * sin(ele);
        eyePos = vec3(x, y, z);
    }

    void keyUp(int key, int mods) {
        if (key == GLFW_KEY_N) {
            models = (models + 1) % meshList.size();
            std::cout << files[models] << std::endl;
        }
        else if(key == GLFW_KEY_P){
            if (models != 0) {
                models = models - 1;
            }
            else {
                models = meshList.size() - 1;
            }
            std::cout << files[models] << std::endl;
        }
        else if(key == GLFW_KEY_S){
            if (shaders == shadernames.size()-1) {
                shaders = 0;
            }
            else {
                shaders++;
            }
        }
    }

    void draw() {
        mesh = meshList[models];
        float aspect = ((float)width()) / height();
        renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
        renderer.lookAt(eyePos, lookPos, up);
        renderer.beginShader(shadernames[shaders]);
        
        float a = 1;
        float b = 1;
        float c = 1; 
        GLfloat xrange = mesh.maxBounds().x - mesh.minBounds().x;
        GLfloat yrange = mesh.maxBounds().y - mesh.minBounds().y;
        GLfloat zrange = mesh.maxBounds().z - mesh.minBounds().z;
        if ((xrange > zrange) || (xrange > yrange)) {
            a = 5.0f / xrange;
            b = 5.0f / xrange;
            c = 5.0f / xrange;
        }
        else if (zrange > yrange) {
            a = 5.0f / zrange;
            b = 5.0f / zrange;
            c = 5.0f / zrange;
        }
        else if (yrange > zrange) {
            a = 5.0f / yrange;
            b = 5.0f / yrange;
            c = 5.0f / yrange;
        }
        renderer.scale(vec3(a, b, c));
        renderer.translate(vec3(0, 0, 0));
        renderer.lookAt(eyePos,lookPos, up);
        renderer.mesh(mesh);
    }

protected:
    std::vector<string> files;
    std::vector<string> shadernames = {"normals", "phong-pixel", "phong-vertex"}; 
    int shaders = 0;
    PLYMesh mesh;
    std::vector<PLYMesh> meshList;
    vec3 eyePos = vec3(10, 0, 0);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    bool click = false;
    float ele = 0;
    float az = 0;
    float radius = 10;
    int models = 0;
};

int main(int argc, char** argv)
{
    MeshViewer viewer;
    viewer.run();
    return 0;
}