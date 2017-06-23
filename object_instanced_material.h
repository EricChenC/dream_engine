#ifndef DREAM_ENGINE_OBJECT_INSTANCED_MATERIAL_H
#define DREAM_ENGINE_OBJECT_INSTANCED_MATERIAL_H

#include "dmaterial.h"
#include "glm/glm.hpp"

#include <qopenglfunctions_4_4_core.h>
#include <vector>

class ObjectInstancedMaterial : public DMaterial
{
public:
	explicit ObjectInstancedMaterial();
	~ObjectInstancedMaterial();

	virtual void set_program();

	virtual void set_material_custom_loc();
	virtual void set_material_custom_data();
	virtual void clear_material_custom_data();

	void set_instanced_data(GLsizeiptr size, GLvoid* data);

private:
	GLuint instanced_pos_vbo_;

	GLsizeiptr size_;
	GLvoid* data_;

};


#endif // !DREAM_ENGINE_OBJECT_INSTANCED_MATERIAL_H
