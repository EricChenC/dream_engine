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

	specular_material_->set_camera(player_camera_);
	model_->set_material(specular_material_);
	model_->Load("models/ball.obj");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);
}

void Specular::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	specular_material_->set_material_data();

	static int time_v;
	time_v += time;
	float angle_y = cos(time_v * 0.01f);
	float angel_z = sin(time_v * 0.01f) + 4.0f;
	const float light_pos[] = {0.0f, angle_y, -angel_z};
	specular_material_->update_light_pos(light_pos);
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
