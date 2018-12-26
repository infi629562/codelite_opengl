#include "SpaceTest.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <common.h>
#include "TextureLoader.h"



#define TEXTURE_BASE TEXTURE_FACE
#define TEXTURE_UP	TEXTURE_T1

#define SHADER_VERTEX "src/Space/space_shader.vs"
#define SHADER_FRAGMENT "src/Space/space_shader.fs"

SpaceTest::SpaceTest()
{
}

SpaceTest::~SpaceTest()
{
	if (shaderProgram)
		delete shaderProgram;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

int SpaceTest::gl_init()
{
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 左上
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	shaderProgram = new Shader(SHADER_VERTEX, SHADER_FRAGMENT);


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

	shaderProgram->use();
	// either set it manually like so:
	//glUniform1i(glGetUniformLocation(shaderProgram->ID, "texture0"), 0);
	shaderProgram->setInt("texture0", 0);
	// or set it via the texture class
	shaderProgram->setInt("texture1", 1);

	// unbind all VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// unbind all VAO
	glBindVertexArray(0);

	return 0;
}

void SpaceTest::gl_draw()
{
	shaderProgram->use();

	// create transformations
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(shaderProgram->ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(shaderProgram->ID, "view");
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shaderProgram->setMat4("projection", projection);


	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void SpaceTest::gl_resize(int width, int height)
{
	glViewport(0, 0, width, height);
}
