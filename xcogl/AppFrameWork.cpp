#include <iostream>
#include "ShaderReader.h"
#include "AppFrameWork.h"
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include "stb_image.h"
#ifndef _vmath_h_
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#else
#include "vmath.h"
#endif
xc_ogl::AppFrameWork* xc_ogl::AppFrameWork::app_ptr = nullptr;
void xc_ogl::AppFrameWork::finalizer()
{
	glfwDestroyWindow(screen);
	glfwTerminate();
}
void xc_ogl::AppFrameWork::screen_resize(GLFWwindow* screen, int w, int h)
{
	glViewport(0, 0, w, h);
	app_ptr->height = h;
	app_ptr->width = w;
#ifdef _DEBUG
	std::cout << "[INFO]Window resized " << app_ptr->height << "x" << app_ptr->width << std::endl;
#endif
}
void xc_ogl::AppFrameWork::init()
{
	have_init = true;
	glfwInit();
	screen = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(screen);
	glfwSetFramebufferSizeCallback(screen, screen_resize);
	gl3wInit();
	shader_init();
}

void xc_ogl::AppFrameWork::display()
{
	while (!glfwWindowShouldClose(screen)) {
	
		key_check();
		render();
		glfwSwapBuffers(screen);
		glfwPollEvents();
	}
}

void xc_ogl::AppFrameWork::key_check()
{
	if (glfwGetKey(screen,GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
}
void xc_ogl::AppFrameWork::shader_init()
{
	xc_ogl::ShaderReader sReader;	
	program_bg = sReader.get_program();
	sReader.load_from_file("shader/vertex_bg.vert", GL_VERTEX_SHADER);
	sReader.load_from_file("shader/fragment_bg.frag", GL_FRAGMENT_SHADER);
	sReader.link_all_shader();

	glGenVertexArrays(1, &vao_bg);
	static xc_shape::XCRectangle rect_temp(vao_bg,FLAT_COVERED_PLANE);
	auto init_lambda = [this] {
		auto location = glGetAttribLocation(program_bg, "draw_pos");
		glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);
		xc_ogl::ImageLoader ima_loader_bg;
		ima_loader_bg.LoadTextureData("image/bg/ogl.png");
		tbo_bg = ima_loader_bg.GetTBO();
		glUniform1i(glGetUniformLocation(program_bg, "tex"), 0);
	};
	rect = &rect_temp;rect->InitShape(init_lambda);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	xc_ogl::ShaderReader shader_reader;
	shader_reader.load_from_file("shader/vertex.vert", GL_VERTEX_SHADER);
	shader_reader.load_from_file("shader/fragment.frag", GL_FRAGMENT_SHADER);
	shader_reader.link_all_shader();
	program = shader_reader.get_program();

	glGenVertexArrays(1, &vao);
	xc_ogl::ImageLoader ima_loader;
	ima_loader.LoadTextureData("image/rin/rin_0.png");
	tbo=ima_loader.GetTBO();

	auto callback_lambda = [this] {
		glUniform1i(glGetUniformLocation(program, "bg_1"), 0);
		auto pos_loc = glGetAttribLocation(program, "draw_pos");
		auto color_loc = glGetAttribLocation(program, "draw_color");
		glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glVertexAttribPointer(color_loc, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(pos_loc);
		glEnableVertexAttribArray(color_loc);
	};
	static xc_shape::XCCube cube_temp(vao, DEFAULT_CUBE_WITH_COLOR); 
	cube = &cube_temp; cube->InitShape(callback_lambda);
	glUseProgram(0);
}
void xc_ogl::AppFrameWork::render()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	auto callback_func = [this]() ->void{
		glDisable(GL_DEPTH_TEST);//渲染背景，深度测试先给我离开这个舞台
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tbo_bg);
		auto pos_location = glGetUniformLocation(program_bg,"time");
		glUniform1f(pos_location, (float)glfwGetTime());
	};
	rect->RenderShape(program_bg,callback_func);
////////////////////////////////////////
	auto callback_lambda = [this] {
		glEnable(GL_DEPTH_TEST);//渲染方块，深度测试请你麻溜的滚回来;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tbo);
		auto transform_mat_loc = glGetUniformLocation(program, "transform");
		glm::mat4 mat_model, mat_view, mat_proj, mat_scale, mat_ortho;
		mat_model = glm::rotate(mat_model, glm::radians((float)sin(glfwGetTime())*360.0f), glm::vec3(1.0, 1.0, 1.0));
		mat_view = glm::translate(mat_view, glm::vec3(0, 0, -5 + sin(glfwGetTime())));
		if (height > 0) {
			mat_proj = glm::perspective(glm::radians(45.0f), width / height * 1.0f, 0.01f, 100.0f);
			mat_scale = glm::scale(mat_scale, glm::vec3(width / height * 1.0f));
		}
		mat_ortho = glm::ortho(0, width, 0, height);
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(mat_proj*mat_scale*mat_view*mat_model));
	};
	cube->RenderShape(program, callback_lambda);
}


xc_ogl::AppFrameWork::AppFrameWork() :height(720), width(1280), title("OGL Test")
{
	if (have_init)
		throw ("Can't create two OpenGL instance.");
	else
		app_ptr = this;
}

xc_ogl::AppFrameWork::AppFrameWork(int w,int h,  const char* t):height(h),width(w),title(t)
{
	if (have_init)
		throw ("Can't create two OpenGL instance.");
	else
		app_ptr = this;
}

void xc_ogl::AppFrameWork::message_loop()
{
	display();
}
