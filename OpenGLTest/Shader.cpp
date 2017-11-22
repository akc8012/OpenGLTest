#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	setup(readSourceFromFile(vertexPath).c_str(), readSourceFromFile(fragmentPath).c_str());
}

Shader::Shader()
{
	const char *defaultVertexSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0);\n"
		"}\0";

	const char *defaultFragmentSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(0.8f, 0.2f, 0.4f, 1.0f);\n"
		"}\n\0";

	setup(defaultVertexSource, defaultFragmentSource);
}

void Shader::setup(const char* vertexSource, const char* fragmentSource)
{
	unsigned int vertexShader = tryCreateShader(vertexSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = tryCreateShader(fragmentSource, GL_FRAGMENT_SHADER);

	shaderProgram = tryCreateShaderProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::string Shader::readSourceFromFile(const char* path)
{
	std::string code;
	std::ifstream file;

	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);
		std::stringstream stream;
		
		stream << file.rdbuf();
		file.close();
		
		code = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		throw("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}
	
	return code;
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
