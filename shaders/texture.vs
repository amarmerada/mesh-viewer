#version 400
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 posit;
out vec3 norm;
out vec2 text;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main(){
	text = vTexCoord;
	norm = normalize(NormalMatrix * vNormal);
	posit = vec3(ModelViewMatrix * vec4(vPosition, 1.0));
	gl_Position = MVP * vec4(vPosition, 1.0);
}