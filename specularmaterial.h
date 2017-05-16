#ifndef SPECULAR_MATERIAL_H
#define SPECULAR_MATERIAL_H

#include "dimaterial.h"

#include <qopenglfunctions_4_3_core.h>

namespace de {
	class DShader;
}

class SpecularMaterial : public de::DIMaterial
{
public:
	explicit SpecularMaterial();
	virtual ~SpecularMaterial();

	virtual void GenMaterial();
	virtual void BindMaterial();
	virtual void DeleteMaterial();

private:
	GLuint program_;

	de::DShader *shaders_;

};


#endif // !SPECULAR_MATERIAL_H





