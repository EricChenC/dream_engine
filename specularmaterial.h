#ifndef SPECULAR_MATERIAL_H
#define SPECULAR_MATERIAL_H

#include "dmaterial.h"

class SpecularMaterial : public DMaterial
{
public:
	explicit SpecularMaterial(de::DPlayerCamera* player = NULL);
	virtual ~SpecularMaterial();

};


#endif // !SPECULAR_MATERIAL_H





