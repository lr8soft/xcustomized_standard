#include "XCNormalAttack.h"
using namespace xc_ogl;
void xc_game::XCAttack::ShaderInit()
{
	ShaderReader SELoader;
	SELoader.load_from_file("shader/se/normalse.vert",GL_VERTEX_SHADER);
	SELoader.load_from_file("shader/se/normalse.frag",GL_FRAGMENT_SHADER);
	SELoader.link_all_shader();
	program = SELoader.get_program();
}

void xc_game::XCAttack::TextureInit()
{

}

void xc_game::XCAttack::BufferInit()
{
}

void xc_game::XCAttack::AttackInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

void xc_game::XCAttack::AttackRender()
{
}
