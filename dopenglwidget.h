#pragma once

#ifndef DOPENGLWIDGET_H
#define DOPENGLWIDGET_H

#include <qtimer.h>
#include <qopenglwidget.h>

namespace de {
	class DIView;
}

class QOpenGLFunctions_4_3_Core;

class DOpenglWidget : public QOpenGLWidget
{
public:
	explicit DOpenglWidget(QWidget *parent = NULL);
	virtual ~DOpenglWidget();

	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	void set_view(de::DIView *view);
	void init_view();

private:
	QOpenGLFunctions_4_3_Core *gl_;
	de::DIView *view_;
	de::DIView *view_old_;
	QTimer timer_;

};

#endif // !DOPENGLWIDGET_H




