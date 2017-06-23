#pragma once

#ifndef SIMPLETRIANGLE_H
#define SIMPLETRIANGLE_H

#include "dview.h"

#include <qopenglfunctions_4_4_core.h>

class SimpleTriangle : public DView
{
public:
	explicit SimpleTriangle();
	virtual ~SimpleTriangle();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

private:
	GLuint vao_;
	GLuint vbo_;

	GLuint program_;

};

#endif // !SIMPLETRIANGLE_H




