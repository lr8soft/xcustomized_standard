#pragma once
#ifndef _Normal_Enemy_
#define _Normal_Enemy_
#include <gl/glcorearb.h>
#include <glfw/glfw3.h>
namespace xc_game {
	class XCEnemy {
	private:
		bool should_render=false,should_positive,first_move=true;
		float deltaX, deltaY, deltaZ;
		float destX, destY, destZ, velocity;//velocity是相对x而言
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float slope_k, parameter_b;//y=kx+b里的k和b
		GLuint vao, vbo, tbo[2], use_tbo,program;
		enum type { FAIRY,HAIRBALL };
		float GetCoordY();
		void ShaderInit();
		void BufferInit();
		void TextureInit();
		void SetUseTBO(GLuint tbo);
		void CheckShouldEnd();
		void OGLSettingRenderStart();
		void OGLSettingRenderEnd();
	public:
		XCEnemy() = default;
		~XCEnemy() = default;
		void EnemyInit();
		void EnemyRender();
		void SetGenerateAndVelocity(float x,float y,float z,float dx,float dy,float dz,float v);
	};
}
#endif