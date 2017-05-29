#include "object_instanced.h"
#include "dmodel.h"
#include "dplayercamera.h"
#include "object_instanced_material.h"

#include "dopenglwidget.h"

#define INSTANCE_COUNT 4

ObjectInstanced::ObjectInstanced()
{
	instance_material_ = new ObjectInstancedMaterial();

	x_value_ = 0;
}

ObjectInstanced::~ObjectInstanced()
{
	instanced_pos_vec_.clear();
	delete instance_material_;
}

void ObjectInstanced::initializeGL()
{
	InitInstancedPosVec();

	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	instance_material_->GenMaterial(gl_);
	instance_material_->set_camera(player_camera_);

	const float light_pos[3] = { -20.0f, 0.0f, -10.0f};
	instance_material_->update_light_pos(light_pos);
	model_->set_material(instance_material_);
	model_->Load("models/nude.obj");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);

	gl_->glEnable(GL_BLEND);
	gl_->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);

}

void ObjectInstanced::paintGL(const int & time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	instance_material_->BindMaterial();
	instance_material_->set_material_data();

	model_->Render(GL_TRIANGLES, INSTANCE_COUNT);

}

void ObjectInstanced::disableGL()
{
	gl_widget_->makeCurrent();

	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
	gl_->glBlendFunc(GL_ONE, GL_ZERO);
	gl_->glDisable(GL_BLEND);

	gl_widget_->doneCurrent();
}

void ObjectInstanced::clearGL()
{
	model_->Free();
}

void ObjectInstanced::InitInstancedPosVec()
{
	static glm::vec3 position[INSTANCE_COUNT];

	int j = 0;
	for (int i = 0; i < INSTANCE_COUNT; i++) {
		if ((i + 1) % 3 == 0) {
			j = 0;
			x_value_ += 3.0f;
		}

		position[i].x = x_value_;
		position[i].y = 0.0f;
		position[i].z =  j * 4.0f;

		j++;
	}

	instance_material_->set_instanced_data(sizeof(position), position);
}
