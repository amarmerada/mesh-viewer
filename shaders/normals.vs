#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;


uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

out vec3 norm;

void main()
{
   norm = vNormal;
   gl_Position = MVP * vec4(vPos, 1.0);
}
