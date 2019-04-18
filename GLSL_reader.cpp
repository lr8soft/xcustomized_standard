#include<iostream>
#include "GLSL_reader.h"
#include<string>
#include<fstream>
#include<sstream>
using std::stringstream;
using std::ifstream;
void xc_std::GLSL_reader::show_failed_info(string sre)
{
	GLsizei len;
	glGetProgramiv(temp_program, GL_INFO_LOG_LENGTH, &len);

	GLchar* log = new GLchar[len + 1];
	glGetProgramInfoLog(temp_program, len, &len, log);
	std::cerr << sre <<" failed: " << log << std::endl;
	delete[] log;
}
const GLchar * xc_std::GLSL_reader::read_from_file(const char* path)
{
	GLchar *ret = nullptr;
	ifstream io(path);
	if (!io) {
#ifdef _DEBUG
		std::cerr << "Unable to open file '" << path << "'" << std::endl;
#endif /* DEBUG */
	}
	else {
		string info, temp_info;
		while (std::getline(io, temp_info)) {
			info += '\n';
			info += temp_info;
		}
		io.close();
#ifdef _DEBUG
		std::cout << info<<std::endl;
#endif
		ret =new GLchar[info.length()+1];
		memcpy_s(ret,info.length(),info.c_str(),info.length());
		ret[info.length()] = '\0';
	}
	return const_cast<GLchar*>(ret);
}
xc_std::GLSL_reader::GLSL_reader()
{
	temp_program = glCreateProgram();
}

xc_std::GLSL_reader::GLSL_reader(GLuint program)
{
	temp_program = program;
}

GLboolean xc_std::GLSL_reader::load_from_file(const char *path, GLenum type)
{
	auto *source_ptr = read_from_file(path);
	GLuint temp_shader = glCreateShader(type);
	glShaderSource(temp_shader,1,&source_ptr,0);
	glCompileShader(temp_shader);

	GLint success;
	glGetShaderiv(temp_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef _DEBUG
		show_failed_info("Shader compilation");
#endif // DEBUG Mode
	}
	else {
		glAttachShader(temp_program, temp_shader);
		shader_count++;
	}
	delete[]source_ptr;
	return success;
}

GLboolean xc_std::GLSL_reader::load_from_info(const char *info,GLenum type)
{
	GLuint temp_shader=glCreateShader(type);//Create shader object
	auto source = const_cast<const GLchar*>(info);
#ifdef _DEBUG
	std::cout << *source << std::endl;
#endif
	glShaderSource(temp_shader,1, &source,0);
	glCompileShader(temp_shader);

	GLint success;
	glGetShaderiv(temp_shader,GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef _DEBUG
		show_failed_info("Shader compilation");
#endif // DEBUG Mode
	}
	else {
		glAttachShader(temp_program, temp_shader);
		shader_count++;	
	}
	
	return success;
}

GLboolean xc_std::GLSL_reader::add_new_shader(GLuint shader, GLenum type)
{
	GLint success=GL_FALSE;
	if (glIsShader(shader)) {
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef _DEBUG
			show_failed_info("Shader compilation");
#endif // DEBUG Mode
		}
		else {
			glAttachShader(temp_program, shader);
			shader_count++;
		}
	}
	return success;
}

GLuint xc_std::GLSL_reader::get_program()
{
	return temp_program;
}

GLboolean xc_std::GLSL_reader::link_all_shader()
{
	if (shader_count>0) {
		glLinkProgram(temp_program);
		GLint success;
		glGetProgramiv(temp_program, GL_LINK_STATUS, &success);
		if (!success) {
#ifdef _DEBUG
			show_failed_info("Shader linking");
#endif /* DEBUG */
			return GL_FALSE;
		}
		else {
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}
