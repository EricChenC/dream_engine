#include "simpletess_material.h"
#include "dshader.h"


SimpleTessMaterial::SimpleTessMaterial()
	: patch_num_(3),
	inner_(4.0f),
	outer_(4.0f)
{
}

SimpleTessMaterial::~SimpleTessMaterial()
{
}

void SimpleTessMaterial::set_program()
{
	de::ShaderInfo simpletess_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/simple_tess/simple_tess.vs.glsl" },
		{ GL_TESS_CONTROL_SHADER, "shaders/simple_tess/simple_tess.cont.glsl" },
		{ GL_TESS_EVALUATION_SHADER, "shaders/simple_tess/simple_tess.eval.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/simple_tess/simple_tess.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(simpletess_shaders);
}

void SimpleTessMaterial::set_material_custom_loc()
{
	/*inner_loc_ = gl_->glGetUniformLocation(program_, "Inner");
	outer_loc_ = gl_->glGetUniformLocation(program_, "Outer");*/
}

void SimpleTessMaterial::set_material_custom_data()
{
	gl_->glUseProgram(program_);

	/*gl_->glUniform1f(inner_loc_, inner_);
	gl_->glUniform1f(outer_loc_, outer_);*/

	gl_->glPatchParameteri(GL_PATCH_VERTICES, patch_num_);
}

void SimpleTessMaterial::clear_material_custom_data()
{

}
