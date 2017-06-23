#pragma once

#ifndef MDOELSHOW_H
#define MDOELSHOW_H

#include "dview.h"

#include <qopenglfunctions_4_4_core.h>

class ModelShow : public DView
{
public:
	explicit ModelShow();
	virtual ~ModelShow();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

private:
	GLuint program_;
	GLuint mvp_loc_;
	GLuint mv_loc_;
	GLuint light_loc_;

};

#endif // !MDOELSHOW_H




