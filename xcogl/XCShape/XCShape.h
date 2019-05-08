#pragma once
#ifndef _XCShape_h_
#define _XCShape_h_
#include <GL/glcorearb.h>
#include <functional>
#include "XCDefaultShape.h"
namespace xc_shape {
	class  XCShape {
	public:
		XCShape() = default;
		~XCShape() = default;
		virtual void RenderShape()=0;
		virtual void RenderShape(GLuint program, std::function<void(void)> callback_func) = 0;
		virtual void InitShape(GLint location, GLsizei data_length, GLsizei stride, void* ptr)=0;
		virtual void Finalizer() = 0;
	};;
}
#endif