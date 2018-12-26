#ifndef GLBASE_H
#define GLBASE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class GLBase
{
public:
	GLBase();
	virtual ~GLBase();
	virtual int gl_init() = 0;
	virtual void gl_resize(int width, int height) = 0;
	virtual void gl_draw() = 0;
	virtual const char* getTestName() = 0;
	virtual void gl_inputEvent(GLFWwindow *window);

};

#endif // GLBASE_H
