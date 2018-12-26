#ifndef SPACETEST_H
#define SPACETEST_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLBase.h" // Base class: GLBase
#include <Shader.h>

class SpaceTest : public GLBase
{
public:
	SpaceTest();
	~SpaceTest();
	// gl interface
	int gl_init();
	void gl_resize(int width, int height);
	void gl_draw();
	const char* getTestName() { return "Space Test Case"; }
private:
	GLuint VAO, VBO, EBO;
	Shader *shaderProgram;
};

#endif // SPACETEST_H
