#include "Triangle.h"

Triangle::Triangle()
{
	unsigned int vertexShader = tryCreateShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = tryCreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	shaderProgram = tryCreateShaderProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	unsigned int vertexBufferObject = createVertexBufferObject();
	createVertexArrayObject();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &vertexBufferObject);
}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Triangle::drawTriangle()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int Triangle::tryCreateShader(const char* source, GLenum shaderType)
{
	unsigned int shaderId;
	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);

	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		throw(infoLog);
	}

	return shaderId;
}

unsigned int Triangle::tryCreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		throw(infoLog);
	}

	return shaderProgram;
}

unsigned int Triangle::createVertexBufferObject()
{
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	return vertexBufferObject;
}

void Triangle::createVertexArrayObject()
{
	glGenVertexArrays(1, &vertexArrayObject);

	// 1. bind Vertex Array Object
	glBindVertexArray(vertexArrayObject);
	// 2. oh crap
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
