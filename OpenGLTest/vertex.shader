#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

uniform float offsetX;

out vec3 ourColor;
out vec3 ourPos;

void main()\
{
	vec3 newPos = vec3(aPos.x + offsetX, -aPos.y, aPos.z);
	gl_Position = vec4(newPos, 1.0);
	ourColor = aColor;
	ourPos = newPos;
}
