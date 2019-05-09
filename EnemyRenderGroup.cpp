#include "EnemyRenderGroup.h"
void EnemyRenderGroup::GroupInit()
{
	test_enemy[0].EnemyInit();
	test_enemy[0].SetGenerateAndVelocity(0.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
}

void EnemyRenderGroup::GroupRender()
{
	test_enemy[0].EnemyRender();
}
