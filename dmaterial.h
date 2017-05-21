#ifndef DREAM_ENGINE_DMATERIAL_H
#define DREAM_ENGINE_DMATERIAL_H

#include "dimaterial.h"

#include <qopenglfunctions_4_3_core.h>

namespace de {
	class DShader;
	class DPlayerCamera;
}

class DMaterial : public de::DIMaterial
{
public:
	explicit DMaterial();
	virtual ~DMaterial();

	virtual void GenMaterial(QOpenGLFunctions_4_3_Core* gl);
	virtual void BindMaterial();
	virtual void DeleteMaterial();

	virtual void set_camera(de::DPlayerCamera* player);
	virtual void set_program();

	virtual void set_material_loc();
	virtual void set_material_default_loc();
	virtual void set_material_custom_loc();

	virtual void set_material_data();
	virtual void set_material_default_data();
	virtual void set_material_custom_data();

	virtual void clear_material_custom_data();

	virtual void set_m();
	virtual void set_v();
	virtual void set_p();
	virtual void set_mv();
	virtual void set_mvp();
	virtual void set_light_position();

	virtual void update_m(const float* m);
	virtual void update_v(const float* v);
	virtual void update_p(const float* p);
	virtual void update_mv(const float* mv);
	virtual void update_mvp(const float* mvp);
	virtual void update_light_pos(const float* light_pos);

protected:
	QOpenGLFunctions_4_3_Core *gl_;
	GLuint program_;
	de::DShader *shaders_;

private:


	GLuint m_loc_;
	GLuint v_loc_;
	GLuint p_loc_;
	GLuint mv_loc_;
	GLuint mvp_loc_;
	GLuint light_position_loc_;

	const float* m_mat_;
	const float* v_mat_;
	const float* p_mat_;
	const float* mv_mat_;
	const float* mvp_mat_;
	const float* light_pos_;

	de::DPlayerCamera* player_;

};

#endif // !DREAM_ENGINE_DMATERIAL_H





