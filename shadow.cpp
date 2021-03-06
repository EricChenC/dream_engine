#include "shadow.h"
#include "dmodel.h"
#include "dshader.h"
#include "dplayercamera.h"

#include "glm/gtc/matrix_transform.hpp"

#define DEPTH_TEXTURE_SIZE 2048

Shadow::Shadow()
{
	kAdvance_ = true;
}


Shadow::~Shadow()
{
	clearGL();
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

	if (kAdvance_) {
		AdvanceVersionInit();
	}
	else {
		SimpeVersionInit();
	}
	
	gl_->glGenFramebuffers(1, &depth_fbo_);
	gl_->glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo_);

	gl_->glGenTextures(1, &depth_texture_);
	gl_->glBindTexture(GL_TEXTURE_2D, depth_texture_);
	gl_->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
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

	gl_->glBindFramebuffer(GL_FRAMEBUFFER, 1);

}

void Shadow::paintGL(const int& time)
{
	InitData();

	gl_->glEnable(GL_CULL_FACE);
	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glDepthFunc(GL_LEQUAL);

	gl_->glUseProgram(depth_program_);
	gl_->glUniformMatrix4fv(depth_mvp_loc_, 1, GL_FALSE, &light_mvp_[0][0]);

	gl_->glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo_);
	gl_->glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);

	gl_->glClearDepth(1.0f);
	gl_->glClear(GL_DEPTH_BUFFER_BIT);

	gl_->glEnable(GL_POLYGON_OFFSET_FILL);
	gl_->glPolygonOffset(2.0f, 4.0f);

	model_->Render();

	gl_->glDisable(GL_POLYGON_OFFSET_FILL);

	gl_->glBindFramebuffer(GL_FRAMEBUFFER, 1);

	gl_->glViewport(0, 0, get_w(), get_h());

	if (kAdvance_) {
		AdvanceVersionPaint();
	}
	else {
		SimpeVersionPaint();
	}

	gl_->glActiveTexture(GL_TEXTURE0);
	gl_->glBindTexture(GL_TEXTURE_2D, depth_texture_);
	gl_->glGenerateMipmap(GL_TEXTURE_2D);

	model_->Render();

	gl_->glFinish();

}

void Shadow::disableGL()
{
	if (kAdvance_) {
		AdvanceVersionDisable();
	}
	else {
		SimpeVersionDisable();
	}
}

void Shadow::clearGL()
{
	if (kAdvance_) {
		AdvanceVersionClear();
	}
	else {
		SimpeVersionClear();
	}
}

void Shadow::InitData()
{
	// qt matrix is a row major
	// glm matrix is a column major
	m_ = player_camera_->get_m();
	v_ = player_camera_->get_v();

	mvp_ = player_camera_->get_mvp();

	// must can not is 0.0, so i write 0.001f
	light_position_ = glm::vec3(3.001f, 4.0f, 5.0f);
	glm::mat4 light_projection = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 light_view = glm::lookAt(light_position_, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 light_model = glm::mat4(1.0);

	glm::mat4 bias_matrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	light_mvp_ = light_projection * light_view * light_model;
	bias_light_mvp_ = bias_matrix * light_mvp_;

}

void Shadow::SimpeVersionInit()
{
	// simple version
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

	// simpe version
	gl_->glUseProgram(shadow_program_);
	gl_->glUniform1i(shadow_map_tex_loc_, 0);
}

void Shadow::AdvanceVersionInit()
{
	// advance version
	de::ShaderInfo advance_shadow_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/shadow/shadowmap_advance.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/shadow/shadowmap_advance.fs.glsl" },
		{ GL_NONE }
	};

	advance_shadow_program_ = shader_->LoadShaders(advance_shadow_shaders);
	advance_m_loc_ = gl_->glGetUniformLocation(advance_shadow_program_, "M");
	advance_v_loc_ = gl_->glGetUniformLocation(advance_shadow_program_, "V");
	advance_mvp_loc_ = gl_->glGetUniformLocation(advance_shadow_program_, "MVP");
	advance_bias_matrix_loc_ = gl_->glGetUniformLocation(advance_shadow_program_, "DepthBiasMVP");
	advance_shadow_tex_loc_ = gl_->glGetUniformLocation(advance_shadow_program_, "shadowMap");
	advance_light_pos_loc_ = gl_->glGetUniformLocation(advance_shadow_program_, "LightInvDirection_worldspace");
	
	//advance version
	gl_->glUseProgram(shadow_program_);
	gl_->glUniform1i(advance_shadow_tex_loc_, 0);

}

void Shadow::SimpeVersionPaint()
{
	// simple version
	gl_->glUseProgram(shadow_program_);
	gl_->glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	gl_->glUniformMatrix4fv(shadow_mvp_loc_, 1, GL_FALSE, mvp_.constData());
	gl_->glUniformMatrix4fv(shadow_bias_mvp_loc_, 1, GL_FALSE, &bias_light_mvp_[0][0]);
}

void Shadow::AdvanceVersionPaint()
{
	gl_->glUseProgram(advance_shadow_program_);
	gl_->glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	gl_->glUniformMatrix4fv(advance_m_loc_, 1, GL_FALSE, m_.constData());
	gl_->glUniformMatrix4fv(advance_v_loc_, 1, GL_FALSE, v_.constData());
	gl_->glUniformMatrix4fv(advance_mvp_loc_, 1, GL_FALSE, mvp_.constData());
	gl_->glUniformMatrix4fv(advance_bias_matrix_loc_, 1, GL_FALSE, &bias_light_mvp_[0][0]);
	gl_->glUniform3fv(advance_light_pos_loc_, 1, &light_position_[0]);
}

void Shadow::SimpeVersionDisable()
{
	gl_->glDisable(GL_CULL_FACE);
	gl_->glDisable(GL_DEPTH_TEST);
}

void Shadow::AdvanceVersionDisable()
{
	gl_->glDisable(GL_CULL_FACE);
	gl_->glDisable(GL_DEPTH_TEST);
}

void Shadow::SimpeVersionClear()
{
	gl_->glDeleteProgram(depth_program_);
	gl_->glDeleteProgram(shadow_program_);
	gl_->glDeleteTextures(1, &depth_texture_);
	gl_->glDeleteFramebuffers(1, &depth_fbo_);

	model_->Free();
}

void Shadow::AdvanceVersionClear()
{
	gl_->glDeleteProgram(depth_program_);
	gl_->glDeleteProgram(advance_shadow_program_);
	gl_->glDeleteTextures(1, &depth_texture_);
	gl_->glDeleteFramebuffers(1, &depth_fbo_);

	model_->Free();
}
