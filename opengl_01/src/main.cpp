#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "common.h"
#include "Space/SpaceTest.h"
#include "Cube/CubeTest.h"

GLBase *gltest = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
	gltest->gl_resize(width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	gltest->gl_inputEvent(window);
}



int main(int argc, char **argv)
{
	// --------------
//	SpaceTest *test = new SpaceTest;
	CubeTest *test = new CubeTest;
	gltest = static_cast<GLBase *> (test);
	// --------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, gltest->getTestName(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	// resize callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gltest->gl_init();

	// render loop
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		gltest->gl_draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete gltest;
	glfwTerminate();

	return 0;
}
