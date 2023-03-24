#version 400

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

in vec3 eyePosit;
in vec3 eyeNorm;
out vec4 FragColor;

const int level = 3;
const float scale = 1.0 / level;

vec3 toon(){
   vec3 s = normalize(vec3(lightCol.pos.xyz) - eyePosit);
   float cos = max(0.0, dot(s, eyeNorm));
   vec3 dif = ((matCol.kd + matCol.ks + matCol.ka)) * ceil(cos * level) * scale;
   return lightCol.la * (matCol.ka + dif);
}

void main(){
   FragColor = vec4(toon(), 1.0);
}