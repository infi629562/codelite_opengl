#pragma once
#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();
	int loadImage(const char *path);
	int loadTexture(const char *path);
public:
	unsigned char *data;
	int width;
	int height;
	int nrChannels;
};

#endif // TEXTURELOADER_HPP
