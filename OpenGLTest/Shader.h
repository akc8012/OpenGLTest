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
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

private:

	unsigned int shaderProgram;

	void setup(const char* vertexSource, const char* fragmentSource);
	std::string readSourceFromFile(const char* path);
	unsigned int tryCreateShader(const char* source, GLenum shaderType);
	unsigned int tryCreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
