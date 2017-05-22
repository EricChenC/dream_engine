#ifndef DREAM_ENGINE_SIMPLETESS_MATERIAL_H
#define DREAM_ENGINE_SIMPLETESS_MATERIAL_H

#include "dmaterial.h"

#include <qopenglfunctions_4_3_core.h>

class SimpleTessMaterial : public DMaterial 
{
public:
	explicit SimpleTessMaterial();
	virtual ~SimpleTessMaterial();

	virtual void set_program();

	virtual void set_material_custom_loc();
	virtual void set_material_custom_data();
	virtual void clear_material_custom_data();

private:
	GLuint inner_loc_;
	GLuint outer_loc_;

	GLfloat inner_;
	GLfloat outer_;

	GLuint patch_num_;

};



#endif // !DREAM_ENGINE_SIMPLETESS_MATERIAL_H
