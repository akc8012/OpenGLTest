#pragma once

#include "common.h"
#include "Shader.h"

class Renderer
{
public:

	Renderer(const float offset[3]);
	~Renderer();
	
	void draw();

private:

	Shader* shader;
	unsigned int vertexArrayObject;

	unsigned int bindVertexArrayObject();
	unsigned int copyVerticesArrayToVertexBuffer(const float offset[3]);
	unsigned int copyIndexArrayToElementBuffer();
	void specifyVertexInterpretation();
};
