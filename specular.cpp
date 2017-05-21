#include "specular.h"
#include "dmodel.h"
#include "dplayercamera.h"
#include "specularmaterial.h"
#include "blinnmaterial.h"

#include <qmatrix4x4.h>

Specular::Specular()
{
	specular_material_ = new SpecularMaterial();
	blinn_material_ = new BlinnMaterial();

	nude_model_ = new de::DModel();
}

Specular::~Specular()
{
	delete specular_material_;
	delete blinn_material_;

	delete nude_model_;
}

void Specular::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	specular_material_->set_camera(player_camera_);
	model_->set_material(specular_material_);
	model_->Load("models/ball.obj");

	blinn_material_->set_camera(player_camera_);
	nude_model_->set_gl(gl_);
	nude_model_->set_material(blinn_material_);
	nude_model_->Load("models/nude.obj");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);
}

void Specular::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	specular_material_->BindMaterial();
	specular_material_->set_material_data();

	static int time_v;
	time_v += time;
	float angle_y = cos(time_v * 0.01f);
	float angel_z = sin(time_v * 0.01f) + 4.0f;
	const float light_pos[] = {0.0f, angle_y, -angel_z};
	specular_material_->update_light_pos(light_pos);
	model_->Render();

	blinn_material_->BindMaterial();
	blinn_material_->set_material_data();

	QMatrix4x4 model_mat = {
		1.0f, 0.0f, 0.0f, 5.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	const float light_pos[] = { 0.0f, 10.0f, -10.0f };
	blinn_material_->update_light_pos(light_pos);
	blinn_material_->update_m(model_mat.constData());
	nude_model_->Render();

}

void Specular::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
}

void Specular::clearGL()
{
	model_->Free();
	nude_model_->Free();
}
