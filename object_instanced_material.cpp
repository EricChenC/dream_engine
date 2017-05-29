#include "object_instanced_material.h"
#include "dshader.h"


ObjectInstancedMaterial::ObjectInstancedMaterial()
{
}

ObjectInstancedMaterial::~ObjectInstancedMaterial()
{
}

void ObjectInstancedMaterial::set_program()
{
	de::ShaderInfo instanced_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/object_instanced/object_instanced.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/object_instanced/object_instanced.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shaders_->LoadShaders(instanced_shaders);
}

void ObjectInstancedMaterial::set_material_custom_loc()
{
	gl_->glUseProgram(program_);

	gl_->glGenBuffers(1, &instanced_pos_vbo_);
	gl_->glBindBuffer(GL_ARRAY_BUFFER, instanced_pos_vbo_);
	gl_->glBufferData(GL_ARRAY_BUFFER, size_, data_, GL_STATIC_DRAW);

	gl_->glVertexAttribDivisor(4, 1);
	gl_->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_->glEnableVertexAttribArray(4);

}

void ObjectInstancedMaterial::set_material_custom_data()
{
}

void ObjectInstancedMaterial::clear_material_custom_data()
{
}

void ObjectInstancedMaterial::set_instanced_data(GLsizeiptr size, GLvoid* data)
{
	size_ = size;
	data_ = data;
}
