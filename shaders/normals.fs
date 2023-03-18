#version 400

in vec3 norm;
out vec4 FragColor;
void main()
{
   float r = (norm[0]+1) /2;
   float g = (norm[1]+1) /2;
   float b = (norm[2]+1) /2;
   FragColor = vec4(r, g, b, 1.0);
}
