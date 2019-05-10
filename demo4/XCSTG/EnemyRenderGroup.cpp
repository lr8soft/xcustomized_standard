#include "EnemyRenderGroup.h"

void EnemyRenderGroup::GroupInit()
{
/*	test_enemy[0].EnemyInit();
	test_enemy[0].SetGenerateAndVelocity(0, 0, 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
	test_enemy[1].EnemyInit();
	test_enemy[1].SetGenerateAndVelocity(0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 0.0f, 0.015f);
	AllEnemyInfo.AddEnemyToVector(&test_enemy[0]);
	AllEnemyInfo.AddEnemyToVector(&test_enemy[1]);*/
	for (int i = 0; i < 256;i++) {
		test_enemy[i].EnemyInit();
		if(i%2==0)
			test_enemy[i].SetGenerateAndVelocity(rand()/double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		else if(i%3==0)
			test_enemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		else if(i%5==0)
			test_enemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		else
			test_enemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		AllEnemyInfo.AddEnemyToVector(&test_enemy[i]);
	}
}

void EnemyRenderGroup::GroupRender()
{
	for (int i = 0; i < 256; i++) 
		test_enemy[i].EnemyRender();
}

xc_game::XCEnemyInfo * EnemyRenderGroup::GetEnemyInfoGroup()
{
	return &AllEnemyInfo;
}
