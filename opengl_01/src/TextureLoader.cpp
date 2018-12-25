#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#include <TextureLoader.h>

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{
	if (data)
		stbi_image_free(data);
	std::cout << "data released ..." << std::endl;
}

int TextureLoader::loadImage(const char *path)
{
	int ret;
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		ret = 0;
	} else {
		std::cout << "Failed to load texture: "<< path << std::endl;
		ret = -1;
	}

	return ret;
}

int TextureLoader::loadTexture(const char *path) {
	unsigned int texture;

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //缩小是使用GL_NEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	loadImage(path);

	if (data) {
		GLuint gl_format = GL_RGB;
		switch (nrChannels) {
		case 3:
			gl_format = GL_RGB;
			break;
		case 4:
			gl_format = GL_RGBA;
			break;
		default:
			std::cout << "error gl_format , nrChannels = " << nrChannels << std::endl;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	data = nullptr;

	return texture;
}

