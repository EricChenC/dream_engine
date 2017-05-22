#include "simpletess.h"
#include "dmodel.h"
#include "dplayercamera.h"
#include "simpletess_material.h"

SimpleTess::SimpleTess()
{
	tess_material_ = new SimpleTessMaterial();
}

SimpleTess::~SimpleTess()
{
	delete tess_material_;
}

void SimpleTess::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	tess_material_->GenMaterial(gl_);
	tess_material_->set_camera(player_camera_);
	/*model_->set_material(tess_material_);
	model_->Load("models/plane.obj");*/

	gl_->glGenVertexArrays(1, &vao_);
	gl_->glBindVertexArray(vao_);



	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);

}

void SimpleTess::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	tess_material_->BindMaterial();
	tess_material_->set_material_data();

	//model_->Render(GL_PATCHES);

	gl_->glDrawArrays(GL_PATCHES, 0, 3);

}

void SimpleTess::disableGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
}

void SimpleTess::clearGL()
{
	gl_->glDeleteVertexArrays(1, &vao_);


	//model_->Free();
}
