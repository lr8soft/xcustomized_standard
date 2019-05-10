#include "PlayerRenderGroup.h"
#include "util/ImageLoader.h"
#include "util/ShaderReader.h"
#include "util/XCShape/XCDefaultShape.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
void PlayerRenderGroup::EveryRenderInit()
{
	MoveTexSet(TboPL[0]);
	RenderDecisionPoint = false;
}
void PlayerRenderGroup::OGLSettingRenderStart()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
void PlayerRenderGroup::OGLSettingRenderEnd()
{
	glDisable(GL_BLEND);
}
void PlayerRenderGroup::ShaderLoader()
{
	ShaderReader glpr,gltx;
	gltx.load_from_file("shader/player/vertex_tx.glsl", GL_VERTEX_SHADER);
	gltx.load_from_file("shader/player/fragment_tx.glsl", GL_FRAGMENT_SHADER);
	gltx.link_all_shader();
	program[TX] = gltx.get_program();

	glpr.load_from_file("shader/player/vertex_player.glsl", GL_VERTEX_SHADER);
	glpr.load_from_file("shader/player/fragment_player.glsl", GL_FRAGMENT_SHADER);
	glpr.link_all_shader();
	program[PLAYER] = glpr.get_program();

}
void PlayerRenderGroup::TextureLoader()
{
	ImageLoader BGLoader,PRNormal, PRRight, PRLeft;
	BGLoader.LoadTextureData("image/bg/ogl.png");
	PRNormal.LoadTextureData("image/rin/rin_0.png");
	PRRight.LoadTextureData("image/rin/rin_1.png");
	PRLeft.LoadTextureData("image/rin/rin_2.png");
	tbo = BGLoader.GetTBO();
    TboPL[0] = PRNormal.GetTBO();
	TboPL[1] = PRRight.GetTBO();
	TboPL[2] = PRLeft.GetTBO();
	MoveTexSet(TboPL[0]);
}
void PlayerRenderGroup::MoveTexSet(GLuint id)
{
	tboPL = id;
}
void PlayerRenderGroup::GroupInit()
{
	ShaderLoader();
	TextureLoader();
	glGenVertexArrays(2, vao);
	glGenBuffers(2, vbo);

	glBindVertexArray(vao[PLAYER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[PLAYER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);
	auto player_loc = glGetAttribLocation(program[PLAYER], "player_pos");
	glVertexAttribPointer(player_loc,2,GL_FLOAT,GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(player_loc);
	

	glBindVertexArray(vao[TX]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex,GL_STATIC_DRAW);
	auto tx_loc = glGetAttribLocation(program[TX], "in_vertex");
	glVertexAttribPointer(tx_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(tx_loc);
	auto tx_tex_loc = glGetUniformLocation(program[TX], "tex");
	glUniform1i(tx_tex_loc, 0);

	for(int i=0;i<7;i++)
		base_attack[i].AttackInit();
}

void PlayerRenderGroup::GroupRender()
{
	OGLSettingRenderStart();
//////////////////////////////////////////////////////////////////////////////
	glUseProgram(program[TX]);
	glBindVertexArray(vao[TX]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TX]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tboPL);
	glm::mat4 change_matrix, tx_matrix;
	tx_matrix = glm::translate(tx_matrix, glm::vec3(deltaX, deltaY, deltaZ));
	tx_matrix = glm::scale(tx_matrix, glm::vec3(0.08, 0.1, 0.1));//Íæ¼Òw/h±ÈÀýÊÇ0.8
	auto tx_loc = glGetUniformLocation(program[TX], "transform_mat");
	glUniformMatrix4fv(tx_loc, 1, GL_FALSE, glm::value_ptr(tx_matrix));
	glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
	OGLSettingRenderEnd();
	//////////////////////////////////////////////////////////////////////////////
	if (RenderDecisionPoint) 
	{
		glUseProgram(program[PLAYER]);
		glBindVertexArray(vao[PLAYER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[PLAYER]);
		auto time_loc = glGetUniformLocation(program[PLAYER], "time");
		glUniform1f(time_loc, (float)glfwGetTime());

		change_matrix = glm::translate(change_matrix, glm::vec3(deltaX, deltaY, deltaZ));
		change_matrix = glm::rotate(change_matrix, glm::radians((float)glfwGetTime()*1620.0f), glm::vec3(0, 0, 1));
		change_matrix = glm::scale(change_matrix, glm::vec3(0.015, 0.015, 0.015));//vec3(0.5,0.5,0.5));
		auto rotate_loc = glGetUniformLocation(program[PLAYER], "rotate_mat");
		glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, glm::value_ptr(change_matrix));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
	}
	OGLSettingRenderStart();
	for (int i = 0; i < 7; i++)
		base_attack[i].AttackRender();
	OGLSettingRenderEnd();
}

void PlayerRenderGroup::GroupUpdateInfo()
{
	if (enemy_info == nullptr) return;
	auto enemy_render=enemy_info->GetRenderingEnemy();
	for (auto iter = enemy_render->begin(); iter != enemy_render->end();iter++) {
		auto enemy = *(iter);
		for (int i = 0; i < 7;i++) {
			if(base_attack[i].IsRunning())
				base_attack[i].CheckCollisionWithEnemy(enemy);
		}
	}
}

void PlayerRenderGroup::GroupKeyCheck(GLFWwindow* screen)
{
	EveryRenderInit();
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(screen, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
	float moveSpeed = base_speed *deltaTime; // adjust accordingly
	if (glfwGetKey(screen, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.5f;
		RenderDecisionPoint = true;
	}
	if (glfwGetKey(screen, GLFW_KEY_UP) == GLFW_PRESS) {
		if (deltaY+moveSpeed<1.0f) 
			deltaY += moveSpeed;
		MoveTexSet(TboPL[0]);
	}

	if (glfwGetKey(screen, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (deltaY - moveSpeed > -1.0f)
			deltaY -= moveSpeed;
		MoveTexSet(TboPL[0]);
	}
	if (glfwGetKey(screen, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (deltaX + moveSpeed <1.0f)
			deltaX += moveSpeed;
		MoveTexSet(TboPL[2]);
	}

	if (glfwGetKey(screen, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (deltaX - moveSpeed > -1.0f)
			deltaX -= moveSpeed;
		MoveTexSet(TboPL[1]);
	}

	if (glfwGetKey(screen, GLFW_KEY_Z) == GLFW_PRESS) {
		for (int i = 0; i < 7; i++) {//deltaX, deltaY + 0.12+0.3*i, deltaZ,12.0f
			base_attack[i].SetPositionAndVelocity(deltaX, deltaY + 0.3*i, deltaZ,12.0f);
			base_attack[i].SetAttack();
		}
	}
}

void PlayerRenderGroup::GroupInitInfo(xc_game::XCEnemyInfo * info)
{
	enemy_info = info;
}
