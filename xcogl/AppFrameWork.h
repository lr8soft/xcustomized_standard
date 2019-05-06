#pragma once
#ifndef _ogl_class_
#define _ogl_class_
#include <GLFW/glfw3.h>
namespace xc_ogl {
	class AppFrameWork
	{
	private:
		static AppFrameWork* app_ptr;
		const char* title;
		int width, height;
		bool have_init = false;
		GLuint vao, vbo,tbo;
		GLuint main_program;
		GLFWwindow* screen;
		static void screen_resize(GLFWwindow*,int,int);
		virtual void display();
		virtual void key_check();
		virtual void render();
		virtual void shader_init();
		
	public:
		AppFrameWork();
		AppFrameWork(int width,int height,const char* title);
		~AppFrameWork()=default;
		void finalizer();
		void init();
		virtual void message_loop();
	};
}

#endif
