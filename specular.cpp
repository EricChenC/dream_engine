#include "specular.h"
#include "dmodel.h"
#include "dplayercamera.h"
#include "specularmaterial.h"


Specular::Specular()
{
	specular_material_ = new SpecularMaterial();
}

Specular::~Specular()
{
	delete specular_material_;
}

void Specular::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	specular_material_->GenMaterial(gl_);

	model_->Load("models/ball.obj");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);
}

void Specular::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	QMatrix4x4 mvp = player_camera_->get_mvp();
	QMatrix4x4 mv = player_camera_->get_mv();
	const float light_pos[3] = {0.0f, 0.0f, -4.0f};

	specular_material_->BindMaterial();
	specular_material_->set_mvp(mvp.constData());
	specular_material_->set_mv(mv.constData());
	specular_material_->set_light_position(light_pos);

	model_->Render();
}

void Specular::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
}

void Specular::clearGL()
{
	specular_material_->DeleteMaterial();

	model_->Free();
}
