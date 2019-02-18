#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;
void main()
{
  //  FragColor = vec4(1.0f, 0.07f, 0.57f, 1.0f);
    FragColor = ourColor;
}