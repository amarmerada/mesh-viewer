#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

out vec3 eyeNorm;
out vec4 eyePosit;

void main(){
	eyeNorm = normalize(NormalMatrix * vNormals);
	eyePosit = ModelViewMatrix * vec4(vPos, 1.0);
    gl_Position = MVP * vec4(vPos, 1.0);
}
