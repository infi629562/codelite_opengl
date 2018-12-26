#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
int main(int argc, char **argv)
{
	printf("hello world\n");
	LOGD("hello world");
#if 1

	int width, height, nrChannels;

	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("/home/infichen/workspace/codelite/gitbase/codelite_opengl/opengl_01/src/Textures/wall.jpg", &width, &height, &nrChannels, 0);
	if (data) {

	} else {

	}
	stbi_image_free(data);
#endif
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
// 之后将不再进行提示
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;


	long corner[10] = { 1,1,1,};
	PDBG(corner);
	int *p;
	p = (int *)corner;
	PDBG(p);
	PDBG(++p);


	return 0;
}
