#pragma once

#include "common.h"

class Triangle
{
public:

	Triangle();
	~Triangle();
	
	void drawTriangle();

private:

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	float vertices[12] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int shaderProgram;
	unsigned int vertexArrayObject;

	unsigned int tryCreateShader(const char* source, GLenum shaderType);
	unsigned int tryCreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	unsigned int createVertexBufferObject();
	void createVertexArrayObject();
	unsigned int createElementBufferObject();
};
