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

	virtual void GenMaterial(QOpenGLFunctions_4_3_Core* gl);
	virtual void BindMaterial();
	virtual void DeleteMaterial();

	void set_mvp(const float* mvp);
	void set_mv(const float* mv);
	void set_light_position(const float* light_position);

private:
	GLuint program_;

	GLuint mvp_loc_;
	GLuint mv_loc_;
	GLuint light_position_loc_;

	de::DShader *shaders_;
	QOpenGLFunctions_4_3_Core *gl_;

};


#endif // !SPECULAR_MATERIAL_H





