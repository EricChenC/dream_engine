#include "dview.h"

#include <qopenglfunctions_4_3_core.h>
#include <qwidget.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

DView::DView()
{
	right_button_press_ = false;
	init_mouse_pos_ = false;
	pause_ = false;

	player_camera_ = new de::DPlayerCamera();
	model_ = new de::DModel();
	shader_ = new de::DShader();
}

DView::~DView()
{
	clearGL();

	delete player_camera_;
	delete model_;
	delete shader_;
}

void DView::initializeGL()
{
	

}

void DView::resizeGL(int w, int h)
{
	w_ = w;
	h_ = h;

	player_camera_->UpdateProjectionRatio((float)w / h);
}

void DView::paintGL(const int& time)
{
	
	
}

void DView::disableGL()
{
	
}

void DView::clearGL()
{
	
}

void DView::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_W: // forward
		player_camera_->MoveForward();
		break;
	case Qt::Key_S: // back
		player_camera_->MoveBack();
		break;
	case Qt::Key_A: // left
		player_camera_->MoveLeft();
		break;
	case Qt::Key_D: // right
		player_camera_->MoveRight();
		break;
	case Qt::Key_Q: // down
		player_camera_->MoveDown();
		break;
	case Qt::Key_E: // up
		player_camera_->MoveUp();
		break;
	default:
		break;
	}

}

void DView::keyReleaseEvent(QKeyEvent * event)
{
}

void DView::mouseDoubleClickEvent(QMouseEvent * event)
{
	pause_ = !pause_;
}

void DView::mouseMoveEvent(QMouseEvent * event)
{
	if (!right_button_press_) {
		return;
	}

	if (!init_mouse_pos_) {
		init_mouse_pos_ = true;
		mouse_last_pos_ = event->pos();
		return;
	}

	QPoint mouse_pos = event->pos();
	QPoint move_span = mouse_last_pos_ - mouse_pos;
	mouse_last_pos_ = mouse_pos;

	player_camera_->RotateCamera(move_span);
}

void DView::mousePressEvent(QMouseEvent * event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		break;
	case Qt::RightButton:
	{
		right_button_press_ = true;
		gl_widget_->setCursor(Qt::BlankCursor);
		break;
	}	
	case Qt::MiddleButton:
		break;
	default:
		break;
	}
}

void DView::mouseReleaseEvent(QMouseEvent * event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		break;
	case Qt::RightButton:
	{
		right_button_press_ = false;
		init_mouse_pos_ = false;
		gl_widget_->setCursor(Qt::ArrowCursor);
		break;
	}
	case Qt::MiddleButton:
		break;
	default:
		break;
	}
}

void DView::wheelEvent(QWheelEvent * event)
{
	if (event->angleDelta().y() > 0) {
		player_camera_->MoveForward();
	}
	else {
		player_camera_->MoveBack();
	}
}

void DView::set_gl(QOpenGLFunctions_4_3_Core * gl)
{
	gl_ = gl;
	model_->set_gl(gl);
	shader_->set_gl(gl);
}

void DView::set_widget(QWidget * widget)
{
	gl_widget_ = widget;
}

int DView::get_w() const
{
	return w_;
}

int DView::get_h() const
{
	return h_;
}


