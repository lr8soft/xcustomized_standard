#include "XCCube.h"
#include <gl3/gl3w.h>
xc_shape::XCCube::XCCube(GLuint VAO, GLint XCShapeTYPE)
{
	bind_vao = VAO;
	switch (XCShapeTYPE) {
	case DEFAULT_CUBE_WITH_COLOR:
		shape_vertex = default_cube_color;
		vertex_size = sizeof(default_cube_color);
		break;
	
	default:
		throw ("[ERROR]Haven't this type of default shape.");
	}
	SimpleDefine = true;
}

xc_shape::XCCube::XCCube(GLuint VAO, GLuint data_size, void * input_vertex)
{
	shape_vertex = input_vertex;
	bind_vao = VAO;
	vertex_size = data_size;
	SimpleDefine = false;
}

void xc_shape::XCCube::RenderShape()
{
	if(SimpleDefine)
		glBindVertexArray(bind_vao);
		glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
		glDrawArrays(GL_TRIANGLES, 0, 36);
}

void xc_shape::XCCube::RenderShape(GLuint program, std::function<void(void)> callback_func)
{
	if (SimpleDefine)
		glUseProgram(program);
		glBindVertexArray(bind_vao);
		glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
		callback_func();
		glDrawArrays(GL_TRIANGLES, 0, 36);
}

void xc_shape::XCCube::RenderShape(GLuint program, std::function<void(void)> callback_func, GLsizei vertex_count)
{
	glUseProgram(program);
	glBindVertexArray(bind_vao);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	callback_func();
	glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void xc_shape::XCCube::InitShape(std::function<void(void)> callback_func)
{
	glBindVertexArray(bind_vao);
	glGenBuffers(1, &bind_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, shape_vertex, GL_STATIC_DRAW);
	callback_func();
}


void xc_shape::XCCube::InitShape(GLint location, GLsizei data_length, GLsizei stride, void * ptr)
{
	glBindVertexArray(bind_vao);

	glGenBuffers(1, &bind_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bind_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_size, shape_vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(location, data_length, GL_FLOAT, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(location);
}

void xc_shape::XCCube::Finalizer()
{
}
