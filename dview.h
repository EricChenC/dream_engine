#pragma once

#ifndef DIVEW_H
#define DIVEW_H

#include "diview.h"
#include "dplayercamera.h"
#include "dmodel.h"
#include "dshader.h"

#include <glm/glm.hpp>
#include <vector>

class DView : public de::DIView
{
public:
	explicit DView();
	virtual ~DView();

	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

	virtual void set_gl(QOpenGLFunctions_4_3_Core *gl);
	virtual void set_widget(QWidget *widget);
	virtual int get_w() const;
	virtual int get_h() const;

protected:
	QOpenGLFunctions_4_3_Core *gl_;
	QWidget *gl_widget_;
	de::DModel *model_;
	de::DShader *shader_;
	de::DPlayerCamera *player_camera_;

	bool pause_;
	
private:
	bool right_button_press_;
	bool init_mouse_pos_;
	QPoint mouse_last_pos_;

	int w_;
	int h_;

};

#endif // !DIVEW_H



