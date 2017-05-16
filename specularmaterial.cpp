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

void SpecularMaterial::GenMaterial()
{
	de::ShaderInfo depth_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/specular_material/specular_material.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/specular_material/specular_material.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(depth_shaders);


}

void SpecularMaterial::BindMaterial()
{
}

void SpecularMaterial::DeleteMaterial()
{
}
