#version 400

in vec3 result;
out vec4 FragColor;
void main()
{
   FragColor = vec4(result, 1.0);
}
