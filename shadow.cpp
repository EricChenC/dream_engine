#include "shadow.h"

Shadow::Shadow()
{
}


Shadow::~Shadow()
{
}

void Shadow::initializeGL()
{
	gl_->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	gl_->glGenVertexArrays(1, &vao_);
	gl_->glBindVertexArray(vao_);
}

void Shadow::paintGL(const int& time)
{
	gl_->glClear(GL_COLOR_BUFFER_BIT);

	gl_->glBindVertexArray(vao_);

	gl_->glFinish();

}

void Shadow::clearGL()
{
	gl_->glDeleteVertexArrays(1,&vao_);
}

void Shadow::set_gl(QOpenGLFunctions_4_3_Core * gl)
{
	gl_ = gl;
}
