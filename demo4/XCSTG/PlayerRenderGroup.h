#pragma once
#ifndef _Render_group_
#define _Render_group_
#include <gl/glcorearb.h>
#include <GLFW/glfw3.h>
#include "util/XCEnemyInfo.h"
#include "util/XCGame/XCNormalAttack.h"
#include "util/XCEnemyInfo.h"
class PlayerRenderGroup {
private:
	xc_game::XCEnemyInfo *enemy_info=nullptr;
	xc_game::XCAttack base_attack[7];
	const float base_speed = 1.45f;
	float deltaTime = 0.0f,lastFrame = 0.0f;
	float deltaX = 0, deltaY = 0, deltaZ = 0;
	bool RenderDecisionPoint = false;
	GLuint vao[2], vbo[2], tbo,TboPL[3],tboPL;
	GLint program[2];
	/*PLAYER:decision point program TX:texture progrm*/
	enum { PLAYER, TX };
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
	void GroupUpdateInfo();
	void GroupKeyCheck(GLFWwindow* screen);
	void GroupInitInfo(xc_game::XCEnemyInfo *info);
};
#endif