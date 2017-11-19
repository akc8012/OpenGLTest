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
		cleanAndDeleteResources();

		system("pause");
		return -1;
	}

	initializeGlViewport(window);

	mainLoop(window);

	cleanAndDeleteResources();
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
	Triangle* triangle;

	try
	{
		triangle = new Triangle();
	}
	catch (const char* message)
	{
		std::cout << message << std::endl;
		system("pause");
		return;
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		triangle->drawTriangle();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete triangle;
}

void cleanAndDeleteResources()
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
