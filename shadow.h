#pragma once

#ifndef SHADOW_H
#define SHADOW_H

#include "dview.h"

#include <qopenglfunctions_4_3_core.h>

class Shadow : public DView
{
public:
	explicit Shadow();
	virtual ~Shadow();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void clearGL();

private:
	GLuint depth_program_;
	GLuint shadow_program_;

	GLuint depth_mvp_loc_;
	GLuint shadow_mvp_loc_;
	GLuint shadow_bias_mvp_loc_;
	GLuint shadow_map_tex_loc_;

	GLuint depth_texture_;
	GLuint depth_fbo_;

};

#endif // !SHADOW_H



