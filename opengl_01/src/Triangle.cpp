#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "common.h"


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
								 "layout (location = 1) in vec3 aColor;\n"
								 "out vec3 ourColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
								 "	ourColor = aColor;\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
								   "//uniform vec4 ourColor;\n"
								   "in vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "  // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
								   "   FragColor = vec4(ourColor, 1.0f);\n"
                                   "}\n\0";
#if 0
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};
#else
float vertices[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};
#endif
unsigned int VBO;
unsigned int VAO;
int shaderProgram;

int ask_vertex_max_number()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	return 0;
}

int buildShaderInternal(GLuint shader_type, const GLchar *const*string)
{
	std::string typeString;
	switch (shader_type) {
	case GL_VERTEX_SHADER:
		typeString.assign("VERTEX");
		break;
	case GL_FRAGMENT_SHADER:
		typeString.assign("FRAGMENT");
		break;
	default:
		LOGE("error shader type: %d", shader_type);
		return -1;
	}
	int shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, string, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::" <<typeString<< "::COMPILATION_FAILED\n"
		//          << infoLog << std::endl;
		LOGD("ERROR::SHADER::%s::COMPLATION_FAILED\n%s", typeString.c_str(), infoLog);

	}
	return shader;
}

int buildShaderProgram()
{
	int vertexShader  = buildShaderInternal(GL_VERTEX_SHADER, &vertexShaderSource);
	int fragmentShader = buildShaderInternal(GL_FRAGMENT_SHADER, &fragmentShaderSource);
	//link
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
		//          << infoLog << std::endl;
		LOGD("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void build_shader()
{
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
			          << infoLog << std::endl;
		}
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	{
		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
			          << infoLog << std::endl;
		}
	}


	//link
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
			          << infoLog << std::endl;
		}
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void triangle_init()
{
	//build and compile our shader program
	buildShaderProgram();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

#if 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#else
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
#endif
	// clear all VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// clear all VAO
	glBindVertexArray(0);
	ask_vertex_max_number();
}

void triangle_draw()
{
	// 更新uniform颜色
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
