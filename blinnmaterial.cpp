#include "blinnmaterial.h"
#include "dshader.h"


BlinnMaterial::BlinnMaterial()
{
}


BlinnMaterial::~BlinnMaterial()
{
}

void BlinnMaterial::set_program()
{
	de::ShaderInfo specular_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/blinn_material/blinn_material.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/blinn_material/blinn_material.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(specular_shaders);
}

void BlinnMaterial::set_material_custom_loc()
{
}

void BlinnMaterial::set_material_custom_data()
{
}

void BlinnMaterial::clear_material_custom_data()
{
}
