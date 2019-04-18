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
	glCreateBuffers(NumBuffers,Buffers);//创建1个缓冲空间
	glNamedBufferStorage(Buffers[ArrayBuffer],sizeof(vertice),vertice,0);//复制vertices进Buffers，并且进行命名

/*	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"triangles.vert"},
		{GL_FRAGMENT_SHADER,"triangles.frag"},
		{GL_NONE,NULL}//LoadShaders读取从这里结束
	};
	auto ret_program = LoadShaders(shaders);*/
	xc_std::GLSL_reader shader_reader;
	auto ret_program = shader_reader.load_from_file("triangles.vert", GL_VERTEX_SHADER);
	shader_reader.load_from_file("triangles.frag", GL_FRAGMENT_SHADER);
	shader_reader.link_all_shader();
	glUseProgram(ret_program);

	glCreateVertexArrays(1,&test_VAO);//创建（NumVAOs=1）一个VAO对象
	glBindVertexArray(test_VAO);//将创建的VAO对象绑定到OpenGL环境中，后续操作将作用于该VAO上
	glBindBuffer(GL_ARRAY_BUFFER,Buffers[ArrayBuffer]);//绑定VAO后，将分配的缓冲空间绑定到OpenGL环境

	glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(vPosition);
	
}
void display() {
	static const float black[] = {0.9,0,0.5,0};
	glClearBufferfv(GL_COLOR,0,black);
	glBindVertexArray(test_VAO);//绑定上文init()中创建的VAO对象(每次在使用VAO对象前需要绑定到OGL环境中)
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