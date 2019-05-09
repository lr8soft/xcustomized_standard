#pragma once
#ifndef _NormalAttack_
#define _NormalAttack_
#include <gl/glcorearb.h>
namespace xc_game {
	class XCAttack {
	private:
		bool should_render;
		const float finish_dist = 2.0f;
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float deltaX=0, deltaY=0, deltaZ=0,velocity=0,destY;
		GLuint vao, vbo, tbo[4],program,render_tbo;
		enum ATTACK_STATE{START,MIDDLE,END,FINISH};
		void ShaderInit();
		void TextureInit();
		void BufferInit();
	public:
		XCAttack() = default;
		~XCAttack() = default;
		void AttackInit();
		void AttackRender();
		void SetPositionAndVelocity(float x, float y, float z,float v);
		void SetAttack();
		void Reset();
	};
}
#endif