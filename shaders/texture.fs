#version 400

in vec3 posit;
in vec3 norm;
in vec2 text;

uniform sampler2D Tex1;

struct LightInfo{
	vec4 position;
	vec3 intensity;
};

uniform LightInfo light;

struct material{
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float shininess;
};

uniform material mat;

layout (location = 0) out vec4 FragColor;

void phongModel(vec3 pos, vec3 nor, out vec3 ambAndDiff, out vec3 specular){
	vec4 lightPosit = light.position;
	vec3 lightVec = normalize( light.position.xyz - pos );
	vec3 s = normalize( vec3( lightVec - pos ));
	vec3 v = normalize( -vec3( pos ));
	vec3 r = reflect( -s, pos );
	vec3 amb = light.intensity * mat.ka;
	vec3 diff = light.intensity * mat.kd * max(dot( s, nor ), 0.0);
	vec3 spec = vec3(0.0);
	if(dot(s, nor) > 0.0)
		spec = light.intensity * mat.ks * pow(max(dot( r, v ), 0.0), 0.3);

	ambAndDiff = amb + diff;
	specular = spec;
}

void main(){
	vec3 ambAndDiff, spec;
	vec4 texCol = texture(Tex1, text);
	phongModel(posit, norm, ambAndDiff, spec);
	FragColor = vec4(ambAndDiff, 1.0) * texCol + vec4(spec, 1.0);
}