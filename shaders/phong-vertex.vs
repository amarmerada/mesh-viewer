#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

struct light{
   vec4 pos;
   vec3 la;
   vec3 ld;
   vec3 ls;
};

struct material{
   vec3 ka;
   vec3 kd;
   vec3 ks;
   float shine;
};

uniform light lightCol;
uniform material matCol;

out vec3 result;

vec3 phongModel(vec4 ep, vec3 en, vec3 ambient, vec3 diffuse, vec3 specular, vec3 lightCol){
	vec4 lightPosit = vec4( 5, 10, 0, 1 );
	vec4 lightVec = normalize( lightPosit - ep );

	vec3 s = normalize( vec3( lightVec - ep ));
	vec3 v = normalize( -vec3( ep ) );
	vec3 r = reflect( -s, en );
	vec3 amb = lightCol * ambient;
	vec3 diff = lightCol * diffuse * max( dot( s, en ), 0.0);

	vec3 spec = vec3(0.0);
	if( dot( s, en ) > 0.0)
		spec = lightCol * specular * pow( max( dot( r, v ), 0.0 ), 1.05);
	vec3 light = amb + diff + spec;
	return light;
}
void main()
{
	vec3 eyeNorm = normalize(NormalMatrix * vNormal);
	vec4 eyePosit = ModelViewMatrix * vec4(vPos, 1.0);
	vec3 color = (matCol.kd + matCol.ks + matCol.ka) * 0.334;
	vec3 ambL = lightCol.la;
	vec3 diffL = lightCol.ld;
	vec3 specL = lightCol.ls;
    result = phongModel(eyePosit, eyeNorm, ambL, diffL, specL, color);
    gl_Position = MVP * vec4(vPos, 1.0);
}