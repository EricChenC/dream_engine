#include "dmaterial.h"
#include "dshader.h"
#include "dplayercamera.h"

#include <qmatrix4x4.h>


DMaterial::DMaterial()
{
	shaders_ = new de::DShader();
}


DMaterial::~DMaterial()
{
	delete shaders_;
}


void DMaterial::GenMaterial(QOpenGLFunctions_4_3_Core * gl)
{
	gl_ = gl;
	shaders_->set_gl(gl);

	set_program();
	set_material_loc();

}

void DMaterial::BindMaterial()
{
	gl_->glUseProgram(program_);
}

void DMaterial::DeleteMaterial()
{
	gl_->glDeleteProgram(program_);
	clear_material_custom_data();
}

void DMaterial::set_camera(de::DPlayerCamera * player)
{
	player_ = player;
}

void DMaterial::set_program()
{

}

void DMaterial::set_material_loc()
{
	set_material_default_loc();
	set_material_custom_loc();
}

void DMaterial::set_material_default_loc()
{
	m_loc_ = gl_->glGetUniformLocation(program_, "m");
	v_loc_ = gl_->glGetUniformLocation(program_, "v");
	p_loc_ = gl_->glGetUniformLocation(program_, "p");
	mv_loc_ = gl_->glGetUniformLocation(program_, "mv");
	mvp_loc_ = gl_->glGetUniformLocation(program_, "mvp");
	light_position_loc_ = gl_->glGetUniformLocation(program_, "light_pos");
}

void DMaterial::set_material_custom_loc()
{
}

void DMaterial::set_m()
{
	gl_->glUniformMatrix4fv(m_loc_, 1, GL_FALSE, m_mat_);
}

void DMaterial::set_v()
{
	gl_->glUniformMatrix4fv(v_loc_, 1, GL_FALSE, v_mat_);
}

void DMaterial::set_p()
{
	gl_->glUniformMatrix4fv(p_loc_, 1, GL_FALSE, p_mat_);
}

void DMaterial::set_mv()
{
	gl_->glUniformMatrix4fv(mv_loc_, 1, GL_FALSE, mv_mat_);
}

void DMaterial::set_mvp()
{
	gl_->glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, mvp_mat_);
}

void DMaterial::set_light_position()
{
	gl_->glUniform3fv(light_position_loc_, 1, light_pos_);
}

void DMaterial::set_material_data()
{
	set_material_default_data();
	set_material_custom_data();
}

void DMaterial::set_material_default_data()
{
	QMatrix4x4 model = player_->get_m();
	m_mat_ = model.constData();
	set_m();

	QMatrix4x4 view = player_->get_v();
	v_mat_ = view.constData();
	set_v();

	QMatrix4x4 proj = player_->get_p();
	p_mat_ = proj.constData();
	set_p();

	QMatrix4x4 mv_matrix = player_->get_mv();
	mv_mat_ = mv_matrix.constData();
	set_mv();

	QMatrix4x4 mvp_matrix = player_->get_mvp();
	mvp_mat_ = mvp_matrix.constData();
	set_mvp();

	const float light_pos[] = {10.0f, 10.0f, -10.0f};
	light_pos_ = light_pos;
	set_light_position();
}

void DMaterial::set_material_custom_data()
{
}

void DMaterial::clear_material_custom_data()
{
}

void DMaterial::update_m(const float * m)
{
	m_mat_ = m;
	set_m();
}

void DMaterial::update_v(const float * v)
{
	v_mat_ = v;
	set_v();
}

void DMaterial::update_p(const float * p)
{
	p_mat_ = p;
	set_p();
}

void DMaterial::update_mv(const float * mv)
{
	mv_mat_ = mv;
	set_mv();
}

void DMaterial::update_mvp(const float * mvp)
{
	mvp_mat_ = mvp;
	set_mvp();
}

void DMaterial::update_light_pos(const float * light_pos)
{
	light_pos_ = light_pos;
	set_light_position();
}
