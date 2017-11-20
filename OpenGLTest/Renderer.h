#pragma once

#include "common.h"
#include "Shader.h"

class Renderer
{
public:

	Renderer();
	~Renderer();
	
	void draw();

private:

	Shader* shader;
	unsigned int vertexArrayObject;

	unsigned int bindVertexArrayObject();
	unsigned int copyVerticesArrayToVertexBuffer();
	unsigned int copyIndexArrayToElementBuffer();
	void specifyVertexInterpretation();
};
