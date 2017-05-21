#ifndef BLINN_MATERIAL_H
#define BLINN_MATERIAL_H

#include "dmaterial.h"

class BlinnMaterial : public DMaterial
{
public:
	explicit BlinnMaterial();
	virtual ~BlinnMaterial();

	virtual void set_program();

	virtual void set_material_custom_loc();
	virtual void set_material_custom_data();
	virtual void clear_material_custom_data();

};


#endif // !BLINN_MATERIAL_H





