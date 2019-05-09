#pragma once
#ifndef _Enemy_Render_group_
#define _Enemy_Render_group_
#include "util/XCGame/Enemy/XCNormalEnemy.h"
class EnemyRenderGroup
{
private:
	xc_game::XCEnemy test_enemy[256];
public:
	EnemyRenderGroup()=default;
	~EnemyRenderGroup() = default;
	void GroupInit();
	void GroupRender();
};
#endif
