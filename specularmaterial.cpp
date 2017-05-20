#include "specularmaterial.h"
#include "dshader.h"


SpecularMaterial::SpecularMaterial(de::DPlayerCamera* player)
{
	
}

SpecularMaterial::~SpecularMaterial()
{
	
}

void SpecularMaterial::set_program()
{
	de::ShaderInfo specular_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/specular_material/specular_material.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/specular_material/specular_material.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(specular_shaders);
}

void SpecularMaterial::set_material_custom_loc()
{
}

void SpecularMaterial::set_material_custom_data()
{
}

void SpecularMaterial::clear_material_custom_data()
{
}



