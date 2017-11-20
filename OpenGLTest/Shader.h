#pragma once

#include "common.h"

class Shader
{
public:

	Shader(bool setupNow = true);
	void setup();
	
	unsigned int getShaderProgram() { return shaderProgram; }
	void setFragmentShaderSource(char *_fragmentShaderSource) { fragmentShaderSource = _fragmentShaderSource; }

private:

	unsigned int shaderProgram;

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	unsigned int tryCreateShader(const char* source, GLenum shaderType);
	unsigned int tryCreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
