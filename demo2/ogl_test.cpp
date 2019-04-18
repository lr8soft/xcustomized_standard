#include<iostream>
//#include <GLUtil/LoadShaders.h>
//#include <GLUtil/vgl.h>
#include "util/GLSL_reader.h"
#include <GLFW/glfw3.h>
using namespace std;
enum Buffer_IDs {ArrayBuffer,NumBuffers};
//				0         1
enum Attrib_IDs {vPosition,vPosition2};
GLuint test_VAO;
GLuint Buffers[NumBuffers];//1
const GLuint NumVertices = 6;
void init() {
	static const GLfloat vertice[NumVertices][2] = {
		{-0.90f,-0.90f},
		{0.85f ,-0.90f},
		{-0.90f, 0.85f},
		{0.90f, -0.85f},
		{0.90f,  0.90f},
		{-0.85f, 0.90f}
	};
	glCreateBuffers(NumBuffers,Buffers);//����1������ռ�
	glNamedBufferStorage(Buffers[ArrayBuffer],sizeof(vertice),vertice,0);//����vertices��Buffers�����ҽ�������

/*	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"triangles.vert"},
		{GL_FRAGMENT_SHADER,"triangles.frag"},
		{GL_NONE,NULL}//LoadShaders��ȡ���������
	};
	auto ret_program = LoadShaders(shaders);*/
	xc_std::GLSL_reader shader_reader;
	auto ret_program = shader_reader.load_from_file("triangles.vert", GL_VERTEX_SHADER);
	shader_reader.load_from_file("triangles.frag", GL_FRAGMENT_SHADER);
	shader_reader.link_all_shader();
	glUseProgram(ret_program);

	glCreateVertexArrays(1,&test_VAO);//������NumVAOs=1��һ��VAO����
	glBindVertexArray(test_VAO);//��������VAO����󶨵�OpenGL�����У����������������ڸ�VAO��
	glBindBuffer(GL_ARRAY_BUFFER,Buffers[ArrayBuffer]);//��VAO�󣬽�����Ļ���ռ�󶨵�OpenGL����

	glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(vPosition);
	
}
void display() {
	static const float black[] = {0.9,0,0.5,0};
	glClearBufferfv(GL_COLOR,0,black);
	glBindVertexArray(test_VAO);//������init()�д�����VAO����(ÿ����ʹ��VAO����ǰ��Ҫ�󶨵�OGL������)
	glDrawArrays(GL_TRIANGLES,0,NumVertices);
}
int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(640,480,"ogl window",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	gl3wInit();
	init();
	while (!glfwWindowShouldClose(window)) {
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}