#pragma once
#ifndef _NormalAttack_
#define _NormalAttack_
#include "../ImageLoader.h"
#include "../ShaderReader.h"
namespace xc_game {
	class XCAttack {
	private:
		GLuint vao, vbo, tbo[3],program;
		enum ATTACK_STATE{START,MIDDLE,END};
		virtual void ShaderInit();
		virtual void TextureInit();
		virtual void BufferInit();
	public:
		XCAttack()=default;
		~XCAttack() = default;
		void AttackInit();
		virtual void AttackRender();
	};
}
#endif