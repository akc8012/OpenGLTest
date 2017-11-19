#pragma once

#include "common.h"
#include "Triangle.h"

void instantiateGlfwWindow();

GLFWwindow* tryCreateGlfwWindow();

void tryInitializeGlad();

void initializeGlViewport(GLFWwindow* window);

void mainLoop(GLFWwindow* window);

void cleanAndDeleteResources();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);
