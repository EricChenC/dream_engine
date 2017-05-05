#include "dview.h"

#include <qopenglfunctions_4_3_core.h>

DView::DView()
{
}

DView::~DView()
{
}

void DView::initializeGL()
{
	gl_->glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
}

void DView::resizeGL(int w, int h)
{
}

void DView::paintGL(const int& time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	
}

void DView::clearGL()
{
}

void DView::keyPressEvent(QKeyEvent * event)
{
}

void DView::keyReleaseEvent(QKeyEvent * event)
{
}

void DView::mouseDoubleClickEvent(QMouseEvent * event)
{
}

void DView::mouseMoveEvent(QMouseEvent * event)
{
}

void DView::mousePressEvent(QMouseEvent * event)
{
}

void DView::mouseReleaseEvent(QMouseEvent * event)
{
}

void DView::wheelEvent(QWheelEvent * event)
{
}

void DView::set_gl(QOpenGLFunctions_4_3_Core * gl)
{
	gl_ = gl;
}
