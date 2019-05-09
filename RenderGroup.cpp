#include "RenderGroup.h"
#include "util/ImageLoader.h"
#include "util/ShaderReader.h"
#include "util/XCShape/XCDefaultShape.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
void RenderGroup::EveryRenderInit()
{
	MoveTexSet(TboPL[0]);
	RenderDecisionPoint = false;
}
void RenderGroup::OGLSettingRenderStart()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
void RenderGroup::OGLSettingRenderEnd()
{
	glDisable(GL_BLEND);
}
void RenderGroup::ShaderLoader()
{
	ShaderReader glpg,glpr,gltx;
	glpg.load_from_file("shader/vertex.glsl", GL_VERTEX_SHADER);
	glpg.load_from_file("shader/fragment.glsl", GL_FRAGMENT_SHADER);
	glpg.link_all_shader();
	program[BG] = glpg.get_program();

	gltx.load_from_file("shader/player/vertex_tx.glsl", GL_VERTEX_SHADER);
	gltx.load_from_file("shader/player/fragment_tx.glsl", GL_FRAGMENT_SHADER);
	gltx.link_all_shader();
	program[TX] = gltx.get_program();

	glpr.load_from_file("shader/player/vertex_player.glsl", GL_VERTEX_SHADER);
	glpr.load_from_file("shader/player/fragment_player.glsl", GL_FRAGMENT_SHADER);
	glpr.link_all_shader();
	program[PLAYER] = glpr.get_program();

}
void RenderGroup::TextureLoader()
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
void RenderGroup::MoveTexSet(GLuint id)
{
	tboPL = id;
}
void RenderGroup::GroupInit()
{
	ShaderLoader();
	TextureLoader();
	glGenVertexArrays(3, vao);
	glBindVertexArray(vao[BG]);
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[BG]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);

	auto vertex_loc = glGetAttribLocation(program[BG], "in_vertex");
	glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(vertex_loc);
	auto tex_loc = glGetUniformLocation(program[BG],"tex");
	glUniform1i(tex_loc, 0);

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
	auto tx_tex_loc = glGetUniformLocation(program[TX], "tex_tx");
	glUniform1i(tx_tex_loc, 0);
}

void RenderGroup::GroupRender()
{
	OGLSettingRenderStart();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program[BG]);
	glBindVertexArray(vao[BG]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[BG]);
	glBindTextureUnit(0, tbo);
	auto time_loc = glGetUniformLocation(program[BG], "time");
	glUniform1f(time_loc, (float)glfwGetTime());
	glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex)/sizeof(float));

//////////////////////////////////////////////////////////////////////////////
	glUseProgram(program[TX]);
	glBindVertexArray(vao[TX]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TX]);
	glBindTextureUnit(0, tboPL);
	glm::mat4 change_matrix, tx_matrix;
	tx_matrix = glm::translate(tx_matrix, glm::vec3(deltaX, deltaY, deltaZ));
	tx_matrix = glm::scale(tx_matrix, glm::vec3(0.08, 0.1, 0.1));//vec3(0.5,0.5,0.5));
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
		time_loc = glGetUniformLocation(program[PLAYER], "time");
		glUniform1f(time_loc, (float)glfwGetTime());

		change_matrix = glm::translate(change_matrix, glm::vec3(deltaX, deltaY, deltaZ));
		change_matrix = glm::rotate(change_matrix, glm::radians((float)glfwGetTime()*1440.0f), glm::vec3(0, 0, 1));
		change_matrix = glm::scale(change_matrix, glm::vec3(0.015, 0.015, 0.015));//vec3(0.5,0.5,0.5));
		auto rotate_loc = glGetUniformLocation(program[PLAYER], "rotate_mat");
		glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, glm::value_ptr(change_matrix));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
	}
}

void RenderGroup::GroupKeyCheck(GLFWwindow* screen)
{
	EveryRenderInit();
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(screen, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
	float moveSpeed = 1.5f*deltaTime; // adjust accordingly
	if (glfwGetKey(screen, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.5f;
		RenderDecisionPoint = true;
	}
	if (glfwGetKey(screen, GLFW_KEY_UP) == GLFW_PRESS) {
		deltaY += moveSpeed;
		MoveTexSet(TboPL[0]);
	}

	if (glfwGetKey(screen, GLFW_KEY_DOWN) == GLFW_PRESS) {
		deltaY -= moveSpeed;
		MoveTexSet(TboPL[0]);
	}
	if (glfwGetKey(screen, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		deltaX += moveSpeed;
		MoveTexSet(TboPL[2]);
	}

	if (glfwGetKey(screen, GLFW_KEY_LEFT) == GLFW_PRESS) {
		deltaX -= moveSpeed;
		MoveTexSet(TboPL[1]);
	}


}
