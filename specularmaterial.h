#ifndef SPECULAR_MATERIAL_H
#define SPECULAR_MATERIAL_H

#include "dmaterial.h"

class SpecularMaterial : public DMaterial
{
public:
	explicit SpecularMaterial(de::DPlayerCamera* player = NULL);
	virtual ~SpecularMaterial();

	virtual void set_program();

	virtual void set_material_custom_loc();
	virtual void set_material_custom_data();
	virtual void clear_material_custom_data();

};


#endif // !SPECULAR_MATERIAL_H





