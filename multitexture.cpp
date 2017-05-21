#include "multitexture.h"
#include "dmodel.h"
#include "dplayercamera.h"
#include "multitexture_material.h"


MultiTexture::MultiTexture()
{
	multi_tex_material_ = new MultiTextureMaterial();
}


MultiTexture::~MultiTexture()
{
	delete multi_tex_material_;
}

void MultiTexture::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	multi_tex_material_->set_camera(player_camera_);
	model_->set_material(multi_tex_material_);
	model_->Load("models/ball.obj");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);
}

void MultiTexture::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	static float time_value = 0.0f;
	time_value += time * 0.001f;

	multi_tex_material_->update_time(time_value);

	multi_tex_material_->BindMaterial();
	multi_tex_material_->set_material_data();

	model_->Render();


}

void MultiTexture::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
}

void MultiTexture::clearGL()
{
	model_->Free();
}
