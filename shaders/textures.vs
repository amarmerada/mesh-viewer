#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUV;


uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform vec3 matcolor;

out vec3 color;
out vec2 uv;

void main()
{
   color = matcolor;
   uv = vUV;
   gl_Position = MVP * vec4(vPos, 1.0);
}
