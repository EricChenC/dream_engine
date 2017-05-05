#pragma once

#ifndef DIVEW_H
#define DIVEW_H

#include "diview.h"

class DView : public de::DIView
{
public:
	explicit DView();
	virtual ~DView();

	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL(const int& time);
	virtual void clearGL();
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void set_gl(QOpenGLFunctions_4_3_Core *gl);

private:
	QOpenGLFunctions_4_3_Core *gl_;
};

#endif // !DIVEW_H



