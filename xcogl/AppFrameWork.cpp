#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "ShaderReader.h"
#include "AppFrameWork.h"
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
static GLfloat vertex_group[]=
{
	 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
void xc_ogl::AppFrameWork::shader_init()
{
	xc_ogl::ShaderReader shader_reader;
	shader_reader.load_from_file("shader/vertex.vert",GL_VERTEX_SHADER);
	shader_reader.load_from_file("shader/fragment.frag", GL_FRAGMENT_SHADER);
	shader_reader.link_all_shader();
	main_program = shader_reader.get_program();
	glUseProgram(main_program);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(vao);

	int w, h, channls;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bg_data = stbi_load("bg/2.png", &w, &h, &channls, 4);
	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
	if (bg_data){ 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, bg_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
#ifdef _DEBUG
		std::cerr << "Failed to load background." << std::endl;
#endif
	}
	stbi_image_free(bg_data);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(main_program, "bg_1"), 0);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_group) , vertex_group, GL_STATIC_DRAW);

	auto pos_loc = glGetAttribLocation(main_program, "draw_pos");
	auto color_loc = glGetAttribLocation(main_program, "draw_color");
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(color_loc, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(pos_loc);
	glEnableVertexAttribArray(color_loc);

	glEnable(GL_DEPTH_TEST);
}
void xc_ogl::AppFrameWork::render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	auto transform_mat_loc = glGetUniformLocation(main_program, "transform");
#ifdef _vmath_h_
	vmath::vec4 m_p0 = { 1,0,0,0}, m_p1 = { 0,(float)cos(glfwGetTime()),(float)-sin(glfwGetTime()),0 },
		m_p2 = { 0,(float)sin(glfwGetTime()),(float)cos(glfwGetTime()),0}, m_p3 = { 0,0,0,1};
	vmath::mat4 t_mat = { m_p0,m_p1,m_p2,m_p3};
	vmath::mat4 t_scale = vmath::scale((float)tan(glfwGetTime())/3);
	vmath::mat4 t_mat2=vmath::translate((float)sin(glfwGetTime())/3, (float)sin(glfwGetTime())/3, (float)sin(glfwGetTime())/3);
	glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, t_scale*t_mat2*t_mat);
#else
	glm::mat4 mat_model, mat_view, mat_proj,mat_scale,mat_ortho;
	mat_model = glm::rotate(mat_model, glm::radians((float)sin(glfwGetTime())*360.0f), glm::vec3(1.0, 1.0, 1.0));
	mat_view = glm::translate(mat_view, glm::vec3(0, 0, 3*sin(glfwGetTime())-4));
	if (height > 0) {
		mat_proj = glm::perspective(glm::radians(45.0f), width / height * 1.0f, 0.01f, 100.0f);
		mat_scale = glm::scale(mat_scale, glm::vec3(width / height*1.0f));
	}
	mat_ortho = glm::ortho(0, width, 0, height);
	glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(mat_proj*mat_scale*mat_view*mat_model));

#endif
	//glProgramUniformMatrix4fv()

	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,tbo);

	glDrawArrays(GL_TRIANGLES, 0, 36);
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
