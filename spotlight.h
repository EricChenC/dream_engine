#pragma once

#ifndef SPOTLIHGIT_H
#define SPOTLIHGIT_H

#include "dview.h"

class SpotLight : public DView
{
public:
	SpotLight();
	~SpotLight();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void clearGL();

private:
	GLuint program_;

	GLuint mvp_loc_;
	GLuint light_position_loc_;

};

#endif // !SPOTLIHGIT_H




