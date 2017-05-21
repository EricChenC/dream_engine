#include "multitexture_material.h"
#include "dshader.h"
#include "dtexture.h"


MultiTextureMaterial::MultiTextureMaterial()
	: time_(0.0f),
	text_one_path_("textures/multi_texture/test.dds"),
	text_two_path_("textures/multi_texture/test3.dds")
{
	dtexture_ = new de::DTexture();
}

MultiTextureMaterial::~MultiTextureMaterial()
{
	delete dtexture_;
}

void MultiTextureMaterial::set_program()
{
	de::ShaderInfo specular_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/multi_texture/multi_texture.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/multi_texture/multi_texture.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(specular_shaders);
}

void MultiTextureMaterial::set_material_custom_loc()
{
	dtexture_->set_gl(gl_);


	time_loc_ = gl_->glGetUniformLocation(program_, "time");
	tex_one_loc_ = gl_->glGetUniformLocation(program_, "tex1");
	tex_two_loc_ = gl_->glGetUniformLocation(program_, "tex2");

	gl_->glUseProgram(program_);

	gl_->glUniform1i(tex_one_loc_, 0);
	gl_->glUniform1i(tex_two_loc_, 1);

	vglImageData image;

	tex_one_ = dtexture_->vglLoadTexture(text_one_path_, 0, &image);

	gl_->glBindTexture(image.target, tex_one_);
	gl_->glTexParameteri(image.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	dtexture_->vglUnloadImage(&image);

	tex_two_ = dtexture_->vglLoadTexture(text_two_path_, 0, &image);

	dtexture_->vglUnloadImage(&image);
}

void MultiTextureMaterial::set_material_custom_data()
{
	gl_->glUniform1f(time_loc_, time_);

	gl_->glActiveTexture(GL_TEXTURE0);
	gl_->glBindTexture(GL_TEXTURE_2D, tex_one_);
	gl_->glActiveTexture(GL_TEXTURE1);
	gl_->glBindTexture(GL_TEXTURE_2D, tex_two_);
}

void MultiTextureMaterial::clear_material_custom_data()
{
	gl_->glDeleteTextures(1, &tex_one_);
	gl_->glDeleteTextures(1, &tex_two_);
}

void MultiTextureMaterial::update_tex_one_path(const char * path)
{
	text_one_path_ = path;
}

void MultiTextureMaterial::update_tex_two_path(const char * path)
{
	text_two_path_ = path;
}

void MultiTextureMaterial::update_time(const float & time)
{
	time_ = time;
}
