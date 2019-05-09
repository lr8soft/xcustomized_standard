#pragma once
#ifndef _Render_group_
#define _Render_group_
#include <gl/glcorearb.h>
#include <GLFW/glfw3.h>
#include "util/XCGame/XCNormalAttack.h"
class PlayerRenderGroup {
private:
	xc_game::XCAttack se_test[7];
	float deltaTime = 0.0f,lastFrame = 0.0f;
	float deltaX = 0, deltaY = 0, deltaZ = 0;
	bool RenderDecisionPoint = false;
	GLuint vao[2], vbo[2], tbo,TboPL[3],tboPL;
	GLint program[2];
	enum {PLAYER,TX };
	void EveryRenderInit();
	void OGLSettingRenderStart();
	void OGLSettingRenderEnd();
	void ShaderLoader();
	void TextureLoader();
	void MoveTexSet(GLuint id);
public:
	PlayerRenderGroup() = default;
	~PlayerRenderGroup() = default;
	void GroupInit();
	void GroupRender();
	void GroupKeyCheck(GLFWwindow* screen);
};
#endif