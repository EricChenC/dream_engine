#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "dview.h"

#include <qopenglfunctions_4_4_core.h>

class BoundingBox : public DView
{
public:
	explicit BoundingBox();
	virtual ~BoundingBox();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

private:
	GLuint vao_;

	GLuint program_;

	GLuint global_time_loc_;
	GLuint resolution_loc_;

};

#endif // !BOUNDING_BOX_H







