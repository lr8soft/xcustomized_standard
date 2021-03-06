#include "XCNormalAttack.h"
#include "../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ImageLoader.h"
#include "../ShaderReader.h"
#include <glfw/glfw3.h>
using namespace xc_ogl;
bool xc_game::XCAttack::have_resource_init = false;
GLuint xc_game::XCAttack::tbo[4];
void xc_game::XCAttack::ShaderInit()
{
	ShaderReader SELoader;
	SELoader.load_from_file("shader/se/normalse.vert",GL_VERTEX_SHADER);
	SELoader.load_from_file("shader/se/normalse.frag",GL_FRAGMENT_SHADER);
	SELoader.link_all_shader();
	program = SELoader.get_program();
	glUseProgram(program);
}

void xc_game::XCAttack::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader SEStart, SEMiddle, SEEnd, SEFinish;
		SEStart.LoadTextureData("image/se/normal_attack.png");
		SEMiddle.LoadTextureData("image/se/middle_attack.png");
		SEEnd.LoadTextureData("image/se/end_attack.png");
		SEFinish.LoadTextureData("image/se/finish_attack.png");
		tbo[START] = SEStart.GetTBO();
		tbo[MIDDLE] = SEMiddle.GetTBO();
		tbo[END] = SEEnd.GetTBO();
		tbo[FINISH] = SEFinish.GetTBO();
		have_resource_init = true;
		glUniform1i(glGetUniformLocation(program,"tex"),0);
	}
	
}

void xc_game::XCAttack::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(covered_plane_vertex), covered_plane_vertex,GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program,"in_coord"),2,GL_FLOAT,GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_coord"));

}

void xc_game::XCAttack::AttackInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

void xc_game::XCAttack::AttackRender()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (should_render) {
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		if (destY- NowY< finish_dist/4) {
			render_tbo = tbo[FINISH];
		}
		else if (destY - NowY < finish_dist / 3&&destY- NowY>= finish_dist / 4) {
			render_tbo = tbo[END];
		}
		else if (destY - NowY < finish_dist / 2 && destY - NowY >= finish_dist / 3) {
			render_tbo = tbo[MIDDLE];
		}
		else {
			render_tbo = tbo[START];
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, render_tbo);
		glm::mat4 transform_mat;
		NowY += velocity * deltaTime;
		transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
		transform_mat = glm::scale(transform_mat, glm::vec3(0.06f, 0.06f, 0.06f));
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
		if (NowY > destY)//当Y值超过预定上限时候停止渲染，回到初始状态
			should_render = false;
	}

}

void xc_game::XCAttack::SetPositionAndVelocity(float x, float y, float z, float v)
{
	if (!should_render) {
		NowX = x;
		NowY = y;
		NowZ = z;
		velocity = v;
		should_render = true;
		destY = finish_dist+y;//超过屏幕一个身位
	}
}

void xc_game::XCAttack::CheckCollisionWithEnemy(xc_game::XCEnemy * enemy)
{
	auto *enemy_coord = enemy->GetNowCoord();
	float x = *(enemy_coord), y = *(enemy_coord + 1), z = *(enemy_coord + 2);
	if (x<NowX+ attack_width&&x>NowX-attack_width) {
		if (y < NowY + attack_height && y > NowY - attack_height) {
			enemy->SetDead();
			this->should_render = false;
		}
	}
	delete[] enemy_coord;
}

void xc_game::XCAttack::SetAttack()
{
	if (!should_render) {
		should_render = true;
	}

}

void xc_game::XCAttack::Reset()
{
	should_render = true;
	velocity = 0;
	NowX = NowY = NowZ = 0;
}

bool xc_game::XCAttack::IsRunning()
{
	return should_render;
}
