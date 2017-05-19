#include "specular.h"
#include "dmodel.h"
#include "dplayercamera.h"
#include "specularmaterial.h"


Specular::Specular()
{
	specular_material_ = new SpecularMaterial(player_camera_);
}

Specular::~Specular()
{
	delete specular_material_;
}

void Specular::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	model_->set_material(specular_material_);
	model_->Load("models/ball.obj");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);
}

void Specular::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	model_->Render();
}

void Specular::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
}

void Specular::clearGL()
{
	model_->Free();
}
