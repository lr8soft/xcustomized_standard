#pragma once
#ifndef _ogl_class_
#define _ogl_class_
#include <GLFW/glfw3.h>
#include "XCShape/XCRectangle.h"
#include "XCShape/XCCube.h"
namespace xc_ogl {
	class AppFrameWork
	{
	private:
		xc_shape::XCCube *cube;
		xc_shape::XCRectangle *rect;
		static AppFrameWork* app_ptr;
		const char* title;
		int width, height;
		bool have_init = false;
		GLuint vao,vao_bg ,vbo,vbo_bg,tbo,tbo_bg;
		GLuint program,program_bg;
		GLFWwindow* screen;
		static void screen_resize(GLFWwindow*,int,int);
		virtual void display();
		virtual void key_check();
		virtual void render();
		virtual void shader_init();
		enum{ VAOBG,VAOShape };
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
