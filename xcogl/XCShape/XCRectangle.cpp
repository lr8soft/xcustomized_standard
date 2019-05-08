#include "XCRectangle.h"
#include <GLFW/glfw3.h>
#include <gl3/gl3w.h>
#include <iostream>

xc_shape::XCRectangle::XCRectangle(GLuint VAO, GLint XCShapeTYPE)
{
	bind_vao = VAO;
	switch (XCShapeTYPE) {
	case FLAT_COVERED_PLANE:
		shape_vertex = covered_plane_vertex;
		vertex_size = sizeof(covered_plane_vertex);
		break;
	default:
		throw ("[ERROR]Haven't this type of default shape.");
	}
	SimpleDefined = false;
}

xc_shape::XCRectangle::XCRectangle( GLuint VAO,GLuint data_size,void *input_vertex)
{
	
	shape_vertex = input_vertex;
	bind_vao = VAO;
	vertex_size = data_size;
	SimpleDefined = false;
}	
void xc_shape::XCRectangle::RenderShape()
{
	glBindVertexArray(bind_vao);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	glDrawArrays(GL_TRIANGLES, 0, vertex_size/sizeof(float));
}
void xc_shape::XCRectangle::RenderShape(GLuint program, std::function<void(void)> callback_func)
{
	glUseProgram(program);
	glBindVertexArray(bind_vao);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	callback_func();/*use the callback function*/
	glDrawArrays(GL_TRIANGLES, 0, vertex_size / sizeof(float));
}


void xc_shape::XCRectangle::InitShape(std::function<void(void)> callback_func)
{
	glBindVertexArray(bind_vao);
	glGenBuffers(1, &bind_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, shape_vertex, GL_STATIC_DRAW);
	callback_func();
}

void xc_shape::XCRectangle::InitShape(GLint location, GLsizei data_length,GLsizei stride, void * ptr)
{
	glBindVertexArray(bind_vao);

	glGenBuffers(1, &bind_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, shape_vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(location, data_length, GL_FLOAT, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(location);
}


void xc_shape::XCRectangle::Finalizer()
{
}
