#include "Triangle.h"

Triangle::Triangle()
{
	setupShaders();
	setupVertices();
}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Triangle::drawTriangle()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Triangle::setupShaders()
{
	unsigned int vertexShader = tryCreateShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = tryCreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	shaderProgram = tryCreateShaderProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Triangle::setupVertices()
{
	vertexArrayObject = bindVertexArrayObject();
	unsigned int vertexBufferObject = copyVerticesArrayToVertexBuffer();
	unsigned int elementBufferObject = copyIndexArrayToElementBuffer();
	specifyVertexInterpretation();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);
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

unsigned int Triangle::bindVertexArrayObject()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	return VAO;
}

unsigned int Triangle::copyVerticesArrayToVertexBuffer()
{
	unsigned int VBO;
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return VBO;
}

unsigned int Triangle::copyIndexArrayToElementBuffer()
{
	unsigned int EBO;
	unsigned int indices[6] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return EBO;
}

void Triangle::specifyVertexInterpretation()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
