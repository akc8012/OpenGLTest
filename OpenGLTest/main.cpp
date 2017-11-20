#include "main.h"
#include <iostream>

int main(int argc, char* argv[])
{
	GLFWwindow* window;
	
	try
	{
		instantiateGlfwWindow();
		window = tryCreateGlfwWindow();
		tryInitializeGlad();
	}
	catch (const char* message)
	{
		std::cout << message << std::endl;
		clearResources();

		system("pause");
		return -1;
	}

	initializeGlViewport(window);

	mainLoop(window);

	clearResources();
	return 0;
}

void instantiateGlfwWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

GLFWwindow* tryCreateGlfwWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
		throw("Failed to create GLFW window");

	glfwMakeContextCurrent(window);
	return window;
}

void tryInitializeGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw("Failed to initialize GLAD");
}

void initializeGlViewport(GLFWwindow* window)
{
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void mainLoop(GLFWwindow* window)
{
	Renderer* rendererA;
	Renderer* rendererB;

	try
	{
		float offsetA[] = { -0.6f, -0.0f, 0.0f };
		float offsetB[] = { 0.6f, 0.2f, 0.0f };

		Shader* rendererBShader = new Shader(false);

		char *yellowFragmentSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 1.0f, 0.4f, 1.0f);\n"
			"}\n\0";

		rendererBShader->setFragmentShaderSource(yellowFragmentSource);
		rendererBShader->setup();
		
		rendererA = new Renderer(NULL, offsetA);
		rendererB = new Renderer(rendererBShader, offsetB);
	}
	catch (const char* message)
	{
		std::cout << message << std::endl;
		system("pause");
		return;
	}
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rendererA->draw();
		rendererB->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete rendererA;
	delete rendererB;
}

void clearResources()
{
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{	
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
