#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

void main()
{
    //FragColor = vec4(0.0f, 1.0f, 0.2f, 1.0f);
    FragColor = vertexColor;
}