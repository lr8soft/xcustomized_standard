#pragma once
#ifndef _GLSL_reader_
#define _GLSL_reader_
#include<GL3/gl3w.h>
#include<iostream>
using std::string;
namespace xc_ogl {
	class GLSL_reader {
	private:
		GLuint temp_program=0;
		size_t shader_count=0;
		void show_failed_info(string);
		const GLchar* read_from_file(const char*);
	public:
		GLSL_reader();
		GLSL_reader(GLuint program);
		GLuint load_from_file(const char* path,GLenum type);
		GLuint load_from_info(const char* info, GLenum type);
		GLuint add_new_shader(GLuint shader, GLenum type);
		GLboolean link_all_shader();
	};
}
#endif