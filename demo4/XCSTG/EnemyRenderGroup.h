#pragma once
#ifndef _Enemy_Render_group_
#define _Enemy_Render_group_
#include "util/XCGame/Enemy/XCNormalEnemy.h"
#include "util/XCEnemyInfo.h"
class EnemyRenderGroup
{
private:
	xc_game::XCEnemy test_enemy[2560];
	xc_game::XCEnemyInfo AllEnemyInfo;
public:
	EnemyRenderGroup()=default;
	~EnemyRenderGroup() = default;
	void GroupInit();
	void GroupRender();
	xc_game::XCEnemyInfo* GetEnemyInfoGroup();
};
#endif
