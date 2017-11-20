#include "Renderer.h"

Renderer::Renderer(const float offset[3])
{
	shader = new Shader();

	vertexArrayObject = bindVertexArrayObject();
	unsigned int vertexBufferObject = copyVerticesArrayToVertexBuffer(offset);
	specifyVertexInterpretation();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &vertexBufferObject);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	delete shader;
}

void Renderer::draw()
{
	glUseProgram(shader->getShaderProgram());
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int Renderer::bindVertexArrayObject()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	return VAO;
}

unsigned int Renderer::copyVerticesArrayToVertexBuffer(const float offset[3])
{
	unsigned int VBO;
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	for (int i = 0; i < 9; i++)
	{
		int divByThree = i % 3;
		
		if (divByThree == 0)
			vertices[i] += offset[0];
		else if (divByThree-1 == 0)
			vertices[i] += offset[1];
		else
			vertices[i] += offset[2];
	}
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return VBO;
}

unsigned int Renderer::copyIndexArrayToElementBuffer()
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

void Renderer::specifyVertexInterpretation()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
