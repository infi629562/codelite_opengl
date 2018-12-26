#ifndef CUBETEST_H
#define CUBETEST_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>
#include "GLBase.h" // Base class: GLBase

class CubeTest : public GLBase
{
public:
	CubeTest();
	~CubeTest();
	// gl interface
	int gl_init();
	void gl_resize(int width, int height);
	void gl_draw();
	const char* getTestName() { return "Cube Test Case"; }
	void gl_inputEvent(GLFWwindow *window);
private:
	GLuint VAO, VBO, EBO;
	Shader *shaderProgram;
	glm::vec3 cameraPos, cameraFront, cameraUp;
};

#endif // CUBETEST_H
