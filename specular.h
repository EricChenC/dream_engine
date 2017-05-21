#ifndef DREAM_ENGINE_SPECULAR_H
#define DREAM_ENGINE_SPECULAR_H

#include "dview.h"

namespace de {
	class DModel;
}

class SpecularMaterial;
class BlinnMaterial;

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
	BlinnMaterial* blinn_material_;

	de::DModel* nude_model_;

};

#endif // !DREAM_ENGINE_SPECULAR_H




