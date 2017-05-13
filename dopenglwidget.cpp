#include "dopenglwidget.h"

#include <qopenglfunctions_4_3_core.h>
#include <qsurfaceformat.h>

DOpenglWidget::DOpenglWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	QSurfaceFormat surface;
	surface.setSamples(8);
	setFormat(surface);

	view_ = NULL;

	connect(&timer_, SIGNAL(timeout()), this, SLOT(update()));
	timer_.start(10);

}

DOpenglWidget::~DOpenglWidget()
{
	delete gl_;
}

void DOpenglWidget::initializeGL()
{
	gl_ = new QOpenGLFunctions_4_3_Core();
	gl_->initializeOpenGLFunctions();
	init_view();
}

void DOpenglWidget::resizeGL(int w, int h)
{
	view_->resizeGL(w, h);
}

void DOpenglWidget::paintGL()
{
	view_->paintGL(timer_.interval());
}

void DOpenglWidget::keyPressEvent(QKeyEvent * event)
{
	view_->keyPressEvent(event);
}

void DOpenglWidget::keyReleaseEvent(QKeyEvent * event)
{
	view_->keyReleaseEvent(event);
}

void DOpenglWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
	view_->mouseDoubleClickEvent(event);
}

void DOpenglWidget::mouseMoveEvent(QMouseEvent * event)
{
	view_->mouseMoveEvent(event);
}

void DOpenglWidget::mousePressEvent(QMouseEvent * event)
{
	view_->mousePressEvent(event);
}

void DOpenglWidget::mouseReleaseEvent(QMouseEvent * event)
{
	view_->mouseReleaseEvent(event);
}

void DOpenglWidget::wheelEvent(QWheelEvent * event)
{
	view_->wheelEvent(event);
}

void DOpenglWidget::set_view(de::DIView * view)
{
	view_ = view;
}

void DOpenglWidget::init_view()
{
	makeCurrent();
	view_->set_gl(gl_);
	view_->set_widget(this);
	view_->initializeGL();
	doneCurrent();
}