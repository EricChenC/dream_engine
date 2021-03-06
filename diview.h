#pragma once

#ifndef DIVIEW_H
#define DIVIEW_H

#include <qobject.h>

class QKeyEvent;
class QMouseEvent;
class QMoveEvent;
class QWheelEvent;
class QOpenGLFunctions_4_4_Core;
class DOpenglWidget;

namespace de {
class DIView : public QObject
{
public:
	explicit DIView() {}
	virtual ~DIView() {}

	virtual void initializeGL() = 0;
	virtual void resizeGL(int w, int h) = 0;
	virtual void paintGL(const int& time) = 0;
	virtual void disableGL() = 0;
	virtual void clearGL() = 0;
	virtual void keyPressEvent(QKeyEvent *event) = 0;
	virtual void keyReleaseEvent(QKeyEvent *event) = 0;
	virtual void mouseDoubleClickEvent(QMouseEvent *event) = 0;
	virtual void mouseMoveEvent(QMouseEvent *event) = 0;
	virtual void mousePressEvent(QMouseEvent *event) = 0;
	virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
	virtual void wheelEvent(QWheelEvent *event) = 0;
	virtual void set_gl(QOpenGLFunctions_4_4_Core *gl) = 0;
	virtual void set_widget(DOpenglWidget *widget) = 0;
	virtual void set_polygon_mode(const int& mode) = 0;
	virtual int get_w() const = 0;
	virtual int get_h() const = 0;
};
}


#endif // !DIVIEW_H



