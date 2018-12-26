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
#include "CubeTest.h"


#define TEXTURE_BASE TEXTURE_FACE
#define TEXTURE_UP	TEXTURE_T1

#define SHADER_VERTEX "src/Cube/cube_shader.vs"
#define SHADER_FRAGMENT "src/Cube/cube_shader.fs"


CubeTest::CubeTest()
{
	cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
}

CubeTest::~CubeTest()
{
	if (shaderProgram)
		delete shaderProgram;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
}
// world space positions of our cubes
static glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

int CubeTest::gl_init()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	shaderProgram = new Shader(SHADER_VERTEX, SHADER_FRAGMENT);

	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 纹理属性
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	TextureLoader tl;
	int texture0 = tl.loadTexture(TEXTURE_BASE);
	int texture1 = tl.loadTexture(TEXTURE_UP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	// set the texture wrapping parameters
//	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

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

void CubeTest::gl_draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
	shaderProgram->use();


	// create transformations
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//	view       = glm::translate(view,  glm::vec3(0.0f, 0.0f, -3.0f));
//	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), //摄像机位置
//	                   glm::vec3(0.0f, 0.0f, 0.0f),				//目标位置
//	                   glm::vec3(0.0f, 1.0f, 0.5f));			//上向量
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	// pass transformation matrices to the shader
	shaderProgram->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shaderProgram->setMat4("view", view);


	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++) {
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model,(float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shaderProgram->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//glDrawElements(GL_TRIANGLES, 6 * 2 * 3, GL_UNSIGNED_INT, 0);

}

void CubeTest::gl_resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void CubeTest::gl_inputEvent(GLFWwindow *window)
{
	float cameraSpeed = 0.1f; // adjust accordingly

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
