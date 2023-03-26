#version 400

uniform sampler2D diffuseTexture;

in vec3 color;
in vec2 vUv;
in vec3 norm;
out vec4 FragColor;

void main(){
	vec3 c = color * texture(diffuseTexture, vUv*10.0f).xyz;
	FragColor = vec4(c, 1.0);
}