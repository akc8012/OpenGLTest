#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

void instantiateGlfwWindow();

GLFWwindow* tryCreateGlfwWindow();

void tryInitializeGlad();

void initializeGlViewport(GLFWwindow* window);

void renderLoop(GLFWwindow* window);

void cleanAndDeleteResources();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
