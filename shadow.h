#pragma once

#ifndef SHADOW_H
#define SHADOW_H

#include "dview.h"
#include "glm/glm.hpp"

#include <qopenglfunctions_4_3_core.h>
#include <qmatrix4x4.h>

class Shadow : public DView
{
public:
	explicit Shadow();
	virtual ~Shadow();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

	void InitData();

	void SimpeVersionInit();
	void AdvanceVersionInit();
	void SimpeVersionPaint();
	void AdvanceVersionPaint();
	void SimpeVersionDisable();
	void AdvanceVersionDisable();
	void SimpeVersionClear();
	void AdvanceVersionClear();

private:
	GLuint depth_program_;
	GLuint shadow_program_;
	GLuint advance_shadow_program_;

	GLuint depth_mvp_loc_;

	GLuint depth_texture_;
	GLuint depth_fbo_;

	// simple version
	GLuint shadow_mvp_loc_;
	GLuint shadow_bias_mvp_loc_;
	GLuint shadow_map_tex_loc_;

	//advance version
	GLuint advance_m_loc_;
	GLuint advance_v_loc_;
	GLuint advance_mvp_loc_;
	GLuint advance_light_pos_loc_;
	GLuint advance_bias_matrix_loc_;
	GLuint advance_shadow_tex_loc_;

	bool kAdvance_;
	QMatrix4x4 m_;
	QMatrix4x4 v_;
	QMatrix4x4 mvp_;

	glm::vec3 light_position_;
	glm::mat4 light_mvp_;
	glm::mat4 bias_light_mvp_;


};

#endif // !SHADOW_H



