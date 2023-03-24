#version 400

in vec3 color;
in vec2 uv;
out vec4 FragColor;
void main()
{
   vec3 c = color * texture(diffuseTexture, uv*10.0f).xyz);
   FragColor = vec4(c, 1.0);
}
