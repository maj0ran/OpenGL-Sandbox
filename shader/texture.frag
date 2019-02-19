#version 330 core

in vec3 color;
in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D textureSample;

void main() {
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	FragColor = texture(textureSample, texCoords) * vec4(color, 1.0);
}
