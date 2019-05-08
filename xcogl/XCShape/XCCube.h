#pragma once
#include "XCShape.h"
namespace xc_shape {
	class XCCube :
		public XCShape
	{
	private:
		void *shape_vertex;
		GLuint  vertex_size, bind_vao, bind_vbo;
		GLboolean SimpleDefine;
	public:
		XCCube(GLuint VAO, GLint XCShapeTYPE);
		XCCube(GLuint VAO, GLuint data_size, void *input_vertex);
		/*! Auto bind VAO at first
			and render the shape*/
		void RenderShape() override;
		void RenderShape(GLuint program, std::function<void(void)> callback_func) override;
		void RenderShape(GLuint program, std::function<void(void)> callback_func,GLsizei vertex_count);
		void InitShape(std::function<void(void)> callback_func);
		void InitShape(GLint location, GLsizei data_length, GLsizei stride, void* ptr) override;
		void Finalizer() override;
	};
}


