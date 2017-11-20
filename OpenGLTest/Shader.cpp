#include "Shader.h"

Shader::Shader()
{
	unsigned int vertexShader = tryCreateShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = tryCreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	shaderProgram = tryCreateShaderProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::tryCreateShader(const char * source, GLenum shaderType)
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

unsigned int Shader::tryCreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
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
