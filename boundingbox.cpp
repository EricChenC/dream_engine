#include "boundingbox.h"
#include "dshader.h"

#include "glm/glm.hpp"


BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::initializeGL()
{
	de::ShaderInfo scene_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/bounding_box/bounding_box.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/bounding_box/bounding_box.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shader_->LoadShaders(scene_shaders);

	global_time_loc_ = gl_->glGetUniformLocation(program_, "iGlobalTime");
	resolution_loc_ = gl_->glGetUniformLocation(program_, "iResolution");

	gl_->glGenVertexArrays(1, &vao_);
	gl_->glBindVertexArray(vao_);

}

void BoundingBox::paintGL(const int & time)
{
	static double total_time = 0.0;

	if (!pause_)
		total_time += time * 0.001;

	float t = float(total_time);

	glm::vec2 resolution = glm::vec2(get_w(), get_h());

	gl_->glUseProgram(program_);

	gl_->glUniform1f(global_time_loc_, t);
	gl_->glUniform2fv(resolution_loc_, 1, &resolution[0]);

	gl_->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void BoundingBox::disableGL()
{
}

void BoundingBox::clearGL()
{
	gl_->glDeleteVertexArrays(1, &vao_);

	gl_->glDeleteProgram(program_);
}
