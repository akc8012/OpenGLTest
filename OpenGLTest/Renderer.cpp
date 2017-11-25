#include "Renderer.h"
#include <math.h>

Renderer::Renderer()
{
	shader = new Shader("vertex.shader", "fragment.shader");
	texture = new Texture();

	vertexArrayObject = bindVertexArrayObject();
	unsigned int vertexBufferObject = copyVerticesArrayToVertexBuffer();
	unsigned int elementBufferObject = copyIndexArrayToElementBuffer();
	specifyVertexInterpretation();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	delete shader;
}

void Renderer::drawRectangle()
{
	shader->use();
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::drawTriangle()
{
	shader->use();

	double greenValue = (sin(glfwGetTime()) / 2.0) + 0.5;
	int vertexColorLocation = shader->getUniformLocation("ourColor");
	glUniform4f(vertexColorLocation, 0.0f, (float)greenValue, 0.0f, 1.0f);
	
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

unsigned int Renderer::copyVerticesArrayToVertexBuffer()
{
	unsigned int VBO;
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	
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
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
