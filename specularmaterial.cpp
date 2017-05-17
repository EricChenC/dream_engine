#include "specularmaterial.h"
#include "dshader.h"

SpecularMaterial::SpecularMaterial()
{
	shaders_ = new de::DShader();
}


SpecularMaterial::~SpecularMaterial()
{
	delete shaders_;
}

void SpecularMaterial::GenMaterial(QOpenGLFunctions_4_3_Core* gl)
{
	gl_ = gl;
	shaders_->set_gl(gl);

	de::ShaderInfo specular_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/specular_material/specular_material.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/specular_material/specular_material.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(specular_shaders);

	mvp_loc_ = gl_->glGetUniformLocation(program_, "mvp");
	mv_loc_ = gl_->glGetUniformLocation(program_, "mv");
	light_position_loc_ = gl_->glGetUniformLocation(program_, "light_pos");

}

void SpecularMaterial::BindMaterial()
{
	gl_->glUseProgram(program_);
}

void SpecularMaterial::DeleteMaterial()
{
	gl_->glDeleteProgram(program_);
}

void SpecularMaterial::set_mvp(const float * mvp)
{
	gl_->glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, mvp);
}

void SpecularMaterial::set_mv(const float * mv)
{
	gl_->glUniformMatrix4fv(mv_loc_, 1, GL_FALSE, mv);
}

void SpecularMaterial::set_light_position(const float * light_position)
{
	gl_->glUniform3fv(light_position_loc_, 1, light_position);
}
