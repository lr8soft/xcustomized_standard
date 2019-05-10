#pragma once
#ifndef _Normal_Enemy_
#define _Normal_Enemy_
#include <gl/glcorearb.h>
#include <glfw/glfw3.h>
namespace xc_game {
	class XCEnemy {
	public:
		XCEnemy() = default;
		~XCEnemy() = default;
		virtual void EnemyInit();
		virtual void EnemyRender();
		virtual void SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v);
		virtual void SetDead();
		//As same as IsDead();
		bool IsRendering();
		float* GetNowCoord();
	protected:
		static bool have_resource_init;
		static GLuint tbo[2];
		bool should_render=false,should_positive,first_move=true;
		float deltaX, deltaY, deltaZ;
		float destX, destY, destZ, velocity;//velocity是相对x而言
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float slope_k, parameter_b;//y=kx+b里的k和b
		GLuint vao, vbo, use_tbo,program;
		enum type { FAIRY,HAIRBALL };
		virtual float GetCoordY();
		virtual void ShaderInit();
		virtual void BufferInit();
		virtual void TextureInit();
		virtual void SetUseTBO(GLuint tbo);
		virtual void CheckShouldEnd();
		virtual void OGLSettingRenderStart();
		virtual void OGLSettingRenderEnd();
	};
}
#endif