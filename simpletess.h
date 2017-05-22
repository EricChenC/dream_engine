#ifndef DREAM_ENGINE_SIMPLETESS_H
#define DREAM_ENGINE_SIMPLETESS_H

#include "dview.h"

#include <qopenglfunctions_4_3_core.h>

class SimpleTessMaterial;

class SimpleTess : public DView
{
public:
	explicit SimpleTess();
	virtual ~SimpleTess();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

private:
	SimpleTessMaterial* tess_material_;

	GLuint vao_;

};


#endif // !DREAM_ENGINE_SIMPLETESS_H
