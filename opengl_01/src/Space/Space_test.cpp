#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <memory>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <common.h>
#include "TextureLoader.h"


#define TEXTURE_BASE TEXTURE_T1
#define TEXTURE_UP	TEXTURE_FACE

#define SHADER_VERTEX "/home/infichen/workspace/codelite/gitbase/codelite_opengl/cmake-build-Debug/shader.vs"
#define SHADER_FRAGMENT "/home/infichen/workspace/codelite/gitbase/codelite_opengl/cmake-build-Debug/shader.fs"


static float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,  // 右上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,  // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f, // 左上
};
static unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

static GLuint VAO, VBO, EBO;
static std::shared_ptr<Shader> shaderProgram;


void space_init()
{
	//build and compile our shader program

	shaderProgram = std::make_shared<Shader>(SHADER_VERTEX, SHADER_FRAGMENT);
	PDBG(shaderProgram.get());

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	// 纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
	glEnableVertexAttribArray(2);

	TextureLoader tl;
	int texture0 = tl.loadTexture(TEXTURE_BASE);
	int texture1 = tl.loadTexture(TEXTURE_UP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	// set the texture wrapping parameters
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	shaderProgram.get()->use();
	// either set it manually like so:
	glUniform1i(glGetUniformLocation(shaderProgram.get()->ID, "texture0"), 0);
	// or set it via the texture class
	shaderProgram.get()->setInt("texture1", 1);



	// clear all VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// clear all VAO
	glBindVertexArray(0);

}

void space_draw()
{

	// create transformations
	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

	// get matrix's uniform location and set matrix
	shaderProgram.get()->use();
	unsigned int transformLoc = glGetUniformLocation(shaderProgram.get()->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// second transformation
	// ---------------------
	transform = glm::mat4(); // reset it to an identity matrix
	transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
	float scaleAmount = sin(glfwGetTime());
	transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]); // this time take the matrix value array's first element as its memory pointer value
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void space_exit()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
