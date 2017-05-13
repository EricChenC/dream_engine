#include "shadow.h"

#define DEPTH_TEXTURE_SIZE 1024

Shadow::Shadow()
{
}


Shadow::~Shadow()
{
}

void Shadow::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	model_->Load("models/shadow_map.obj");

	de::ShaderInfo depth_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/shadow/shadow_depth.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/shadow/shadow_depth.fs.glsl" },
		{ GL_NONE }
	};

	depth_program_ = shader_->LoadShaders(depth_shaders);
	depth_mvp_loc_ = gl_->glGetUniformLocation(depth_program_, "mvp");

	de::ShaderInfo shadow_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/shadow/shadowmap.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/shadow/shadowmap.fs.glsl" },
		{ GL_NONE }
	};

	shadow_program_ = shader_->LoadShaders(shadow_shaders);
	shadow_mvp_loc_ = gl_->glGetUniformLocation(shadow_program_, "mvp");
	shadow_bias_mvp_loc_ = gl_->glGetUniformLocation(shadow_program_, "bias_mvp");
	shadow_map_tex_loc_ = gl_->glGetUniformLocation(shadow_program_, "shadowMap");

	gl_->glUseProgram(shadow_program_);
	gl_->glUniform1i(shadow_map_tex_loc_, 0);
	
	gl_->glGenFramebuffers(1, &depth_fbo_);
	gl_->glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo_);

	gl_->glGenTextures(1, &depth_texture_);
	gl_->glBindTexture(GL_TEXTURE_2D, depth_texture_);
	gl_->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl_->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl_->glBindTexture(GL_TEXTURE_2D, 0);

	gl_->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture_, 0);

	static const GLenum draw_buffers[] = { GL_DEPTH_ATTACHMENT };
	gl_->glDrawBuffers(1, draw_buffers);

	gl_->glBindTexture(GL_TEXTURE_2D, 0);
	gl_->glBindFramebuffer(GL_FRAMEBUFFER, 1);

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glDepthFunc(GL_LESS);
	gl_->glEnable(GL_CULL_FACE);


}

void Shadow::paintGL(const int& time)
{

	const QMatrix4x4 bias_matrix(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);

	QMatrix4x4 mvp = player_camera_->get_mvp();

	QMatrix4x4 light_proj;
	light_proj.frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 200.0f);

	QMatrix4x4 light_view;
	light_view.lookAt(QVector3D(0.0001f, 10.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

	QMatrix4x4 light_model;
	light_model.setToIdentity();

	QMatrix4x4 light_mvp = light_proj *light_view * light_model;
	QMatrix4x4 bias_light_mvp = bias_matrix * light_mvp;

	gl_->glUseProgram(depth_program_);
	gl_->glUniformMatrix4fv(depth_mvp_loc_, 1, GL_FALSE, light_mvp.constData());

	gl_->glBindFramebuffer(GL_FRAMEBUFFER, 1);
	gl_->glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);

	gl_->glClearDepth(1.0f);
	gl_->glClear(GL_DEPTH_BUFFER_BIT);

	gl_->glEnable(GL_POLYGON_OFFSET_FILL);
	gl_->glPolygonOffset(2.0f, 4.0f);

	model_->Render();

	//gl_->glDisable(GL_POLYGON_OFFSET_FILL);

	//gl_->glBindFramebuffer(GL_FRAMEBUFFER, 1);

	//gl_->glViewport(0, 0, 800, 600);

	//gl_->glUseProgram(shadow_program_);
	//gl_->glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//gl_->glUniformMatrix4fv(shadow_mvp_loc_, 1, GL_FALSE, mvp.constData());
	//gl_->glUniformMatrix4fv(shadow_bias_mvp_loc_, 1, GL_FALSE, light_mvp.constData());

	//gl_->glActiveTexture(GL_TEXTURE0);
	//gl_->glBindTexture(GL_TEXTURE_2D, depth_texture_);
	////gl_->glGenerateMipmap(GL_TEXTURE_2D);

	//model_->Render();

	gl_->glFinish();

}

void Shadow::clearGL()
{
	gl_->glDisable(GL_CULL_FACE);
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_POLYGON_OFFSET_FILL);

	gl_->glDeleteProgram(depth_program_);
	gl_->glDeleteProgram(shadow_program_);
	gl_->glDeleteTextures(1, &depth_texture_);
	gl_->glDeleteFramebuffers(1, &depth_fbo_);

	model_->Free();
}
