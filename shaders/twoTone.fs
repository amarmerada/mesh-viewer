#version 400

uniform sampler2D diffuseTexture;

in vec3 color;
in vec2 vUv;
in vec3 norm;
out vec4 FragColor;

void main(){
	vec3 c = color * texture(diffuseTexture, vUv*10.0f).xyz * sin(norm.x);
	vec3 hold = color;
	if((c.x + c.y + c.z) < 0.75)
		hold = vec3(abs(color.x - 1), abs(color.y - 1), abs(color.z - 1));
		c = hold * texture(diffuseTexture, vUv*10.f).xyz * cos(norm.x);
	FragColor = vec4(c, 1.0);
}