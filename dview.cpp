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
	delete player_camera_;
	delete model_;
	delete shader_;
}

void DView::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	model_->Load("models/nude.obj");

	de::ShaderInfo scene_shaders[] =
	{
		{ GL_VERTEX_SHADER, "shaders/dview/dview.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/dview/dview.fs.glsl" },
		{ GL_NONE }
	};

	program_ = shader_->LoadShaders(scene_shaders);
	
	mvp_loc_ = gl_->glGetUniformLocation(program_, "mvp");
	mv_loc_ = gl_->glGetUniformLocation(program_, "mv");
	light_loc_ = gl_->glGetUniformLocation(program_, "light_pos");

	gl_->glEnable(GL_DEPTH_TEST);
	gl_->glEnable(GL_CULL_FACE);
	gl_->glCullFace(GL_BACK);

}

void DView::resizeGL(int w, int h)
{
	player_camera_->UpdateProjectionRatio((float)w / h);
}

void DView::paintGL(const int& time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	gl_->glUseProgram(program_);
	QMatrix4x4 mvp = player_camera_->get_mvp();
	gl_->glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, mvp.constData());

	QMatrix4x4 mv = player_camera_->get_mv();
	gl_->glUniformMatrix4fv(mv_loc_, 1, GL_FALSE, mv.constData());

	const float light_pos[3] = {5.0f, 5.0f, -5.0f};
	gl_->glUniform3fv(light_loc_, 1, light_pos);


	model_->Render();
	
}

void DView::clearGL()
{
	gl_->glDisable(GL_DEPTH_TEST);
	gl_->glDisable(GL_CULL_FACE);
	gl_->glDeleteProgram(program_);
	
	model_->Free();
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
