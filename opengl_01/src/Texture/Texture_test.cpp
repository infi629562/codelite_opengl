#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <memory>
#include "Shader.h"
#include "stb_image.h"
#include "../common.h"


static float vertices[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};


static GLuint VAO;
static std::shared_ptr<Shader> shaderProgram;

void texture_init()
{
	//build and compile our shader program

	shaderProgram = std::make_shared<Shader>("/home/infichen/workspace/codelite/gitbase/codelite_opengl/cmake-build-Debug/shader.vs", "/home/infichen/workspace/codelite/gitbase/codelite_opengl/cmake-build-Debug/shader.fs");
	PDBG(shaderProgram.get());
	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// clear all VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// clear all VAO
	glBindVertexArray(0);

}

void texture_draw()
{
	shaderProgram.get()->use();

	//glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
