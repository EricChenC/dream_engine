#ifndef DREAM_ENGINE_SPECULAR_H
#define DREAM_ENGINE_SPECULAR_H

#include "dview.h"

class SpecularMaterial;

class Specular : public DView
{
public:
	explicit Specular();
	virtual ~Specular();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

private:
	SpecularMaterial* specular_material_;

};

#endif // !DREAM_ENGINE_SPECULAR_H




