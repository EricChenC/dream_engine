#include "simpletriangle.h"
#include "dshader.h"


SimpleTriangle::SimpleTriangle()
{
}

SimpleTriangle::~SimpleTriangle()
{
}

void SimpleTriangle::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	GLfloat  vertices[6][3] = {
		{ -0.5f, -0.5f, 0.0f },
		{ 0.49f, -0.5f, 0.0f },
		{ -0.5f, 0.49f, 0.0f },  // Triangle 1

		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f }   // Triangle 2
	};

	de::ShaderInfo scene_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/simple_triangle/triangle.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/simple_triangle/triangle.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shader_->LoadShaders(scene_shaders);
	gl_->glUseProgram(program_);

	gl_->glGenVertexArrays(1, &vao_);
	gl_->glBindVertexArray(vao_);

	gl_->glGenBuffers(1, &vbo_);
	gl_->glBindBuffer(GL_ARRAY_BUFFER,vbo_);
	gl_->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	gl_->glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 0, NULL);
	gl_->glEnableVertexAttribArray(0);

}

void SimpleTriangle::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	gl_->glBindVertexArray(vao_);

	gl_->glDrawArrays(GL_TRIANGLES, 0, 6);

}

void SimpleTriangle::disableGL()
{
}

void SimpleTriangle::clearGL()
{
	gl_->glDeleteProgram(program_);
	gl_->glDeleteBuffers(1, &vbo_);
	gl_->glDeleteVertexArrays(1, &vao_);
}
