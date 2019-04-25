#pragma once
#ifndef _ogl_class_
#define _ogl_class_
#include <GLFW/glfw3.h>
namespace xc_ogl {
	class ogl_app
	{
	private:
		const char* title;
		int width, height;
		bool have_init = false;
		GLuint program;
		GLuint vao, vbo;
		GLFWwindow* screen;
		virtual void display();
		virtual void key_check();
		virtual void render();
		virtual void shader_init();
	public:
		ogl_app();
		ogl_app(int width,int height,const char* title);
		~ogl_app()=default;
		void finalizer();
		void init();
		virtual void message_loop();
	};
}

#endif
