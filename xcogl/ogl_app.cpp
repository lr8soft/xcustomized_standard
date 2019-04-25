
#include <iostream>
#include "util/GLSL_reader.h"
#include "ogl_app.h"
#include <GL3/gl3w.h>
void xc_ogl::ogl_app::finalizer()
{
	glfwDestroyWindow(screen);
	glfwTerminate();
}

void xc_ogl::ogl_app::init()
{
	have_init = true;
	glfwInit();
	screen = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(screen);
	gl3wInit();
	shader_init();
}

void xc_ogl::ogl_app::display()
{
	while (!glfwWindowShouldClose(screen)) {
		key_check();
		render();
		glfwSwapBuffers(screen);
		glfwPollEvents();
	}
}

void xc_ogl::ogl_app::key_check()
{
	if (glfwGetKey(screen,GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
}
void xc_ogl::ogl_app::shader_init()
{
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
void xc_ogl::ogl_app::render()
{
	static float color[] = {10,10,255,255};
	glClearBufferfv(GL_COLOR, 0, color);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


xc_ogl::ogl_app::ogl_app() :height(720), width(1280), title("OGL Test")
{
	if (have_init)
		throw ("Can't create two OpenGL instance.");
}

xc_ogl::ogl_app::ogl_app(int w,int h,  const char* t):height(h),width(w),title(t)
{
	if (have_init)
		throw ("Can't create two OpenGL instance.");
}

void xc_ogl::ogl_app::message_loop()
{
	display();
}
