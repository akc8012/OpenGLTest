#pragma once

#include "common.h"
#include <string>

class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	Shader();

	unsigned int getShaderProgram() { return shaderProgram; }

	void use() { glUseProgram(shaderProgram); }
	void setBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); }
	void setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); }
	void setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); }

	int getUniformLocation(const std::string &name) const { return glGetUniformLocation(shaderProgram, name.c_str()); }

private:

	unsigned int shaderProgram;

	void setup(const char* vertexSource, const char* fragmentSource);
	std::string readSourceFromFile(const char* path);
	unsigned int tryCreateShader(const char* source, GLenum shaderType);
	unsigned int tryCreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
