#pragma once

#ifndef SHADOW_H
#define SHADOW_H

#include "dview.h"

#include <qopenglfunctions_4_3_core.h>

class Shadow : public DView
{
public:
	Shadow();
	virtual ~Shadow();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void clearGL();

private:
	GLuint vao_;

};

#endif // !SHADOW_H



