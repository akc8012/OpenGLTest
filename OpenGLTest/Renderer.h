#pragma once

#include "common.h"
#include "Shader.h"
#include "Texture.h"

class Renderer
{
public:

	Renderer();
	~Renderer();
	
	void drawRectangle();
	void drawTriangle();

private:

	Shader* shader;
	Texture* texture;
	unsigned int vertexArrayObject;

	unsigned int bindVertexArrayObject();
	unsigned int copyVerticesArrayToVertexBuffer();
	unsigned int copyIndexArrayToElementBuffer();
	void specifyVertexInterpretation();
};
