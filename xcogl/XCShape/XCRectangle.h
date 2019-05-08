#pragma once
#ifndef _XCRectangle_h_
#define _XCRectangle_h_
#include "XCShape.h"
namespace xc_shape {
	class XCRectangle :
		public XCShape
	{
	private:
		void *shape_vertex;
		GLuint  vertex_size,bind_vao,bind_vbo;
		GLboolean SimpleDefined;
	public:
		XCRectangle(GLuint VAO, GLint XCShapeTYPE);
		XCRectangle(GLuint VAO, GLuint data_size, void *input_vertex);
		/*! Auto bind VAO at first
			and render the shape*/
		void RenderShape() override;
		void RenderShape(GLuint program, std::function<void(void)> callback_func) override;
		/*!Transform info to shader!*/
		void InitShape(std::function<void(void)> callback_func);
		void InitShape(GLint location, GLsizei data_length,  GLsizei stride, void* ptr) override;
		void Finalizer() override;
	};
}
#endif

