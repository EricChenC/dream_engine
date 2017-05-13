#include "modelshow.h"



ModelShow::ModelShow()
{
}


ModelShow::~ModelShow()
{
}

void ModelShow::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	model_->Load("models/ball.obj");

	de::ShaderInfo scene_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/dview/dview.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/dview/dview.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shader_->LoadShaders(scene_shaders);

	mvp_loc_ = gl_->glGetUniformLocation(program_, "mvp");
	mv_loc_ = gl_->glGetUniformLocation(program_, "mv");
	light_loc_ = gl_->glGetUniformLocation(program_, "light_pos");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);
}

void ModelShow::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	gl_->glUseProgram(program_);
	QMatrix4x4 mvp = player_camera_->get_mvp();
	gl_->glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, mvp.constData());

	QMatrix4x4 mv = player_camera_->get_mv();
	gl_->glUniformMatrix4fv(mv_loc_, 1, GL_FALSE, mv.constData());

	const float light_pos[3] = { 5.0f, 5.0f, -5.0f };
	gl_->glUniform3fv(light_loc_, 1, light_pos);

	model_->Render();
}

void ModelShow::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
}

void ModelShow::clearGL()
{
	gl_->glDeleteProgram(program_);

	model_->Free();
}
