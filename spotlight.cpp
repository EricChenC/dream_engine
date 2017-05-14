#include "spotlight.h"
#include "dmodel.h"
#include "dshader.h"
#include "dplayercamera.h"


SpotLight::SpotLight()
{
}


SpotLight::~SpotLight()
{
	clearGL();
}

void SpotLight::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	model_->Load("models/plane.obj");

	de::ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/spot_light/spot_light.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/spot_light/spot_light.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shader_->LoadShaders(shaders);
	mvp_loc_ = gl_->glGetUniformLocation(program_, "mvp");
	light_position_loc_ = gl_->glGetUniformLocation(program_, "light_position");

	gl_->glEnable(GL_DEPTH_TEST);
	
}

void SpotLight::paintGL(const int & time)
{

	float light_position[] = { 4.0f, 5.0f, 4.0f , 1.0f};

	QMatrix4x4 mvp = player_camera_->get_mvp();

	gl_->glUseProgram(program_);
	gl_->glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, mvp.constData());
	gl_->glUniform4fv(light_position_loc_, 1, light_position);

	model_->Render();

}

void SpotLight::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
}

void SpotLight::clearGL()
{
	gl_->glDeleteProgram(program_);

	model_->Free();
}
