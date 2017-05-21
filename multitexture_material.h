#ifndef DREAM_ENGINE_MULTITEXTURE_MATERIAL_H
#define DREAM_ENGINE_MULTITEXTURE_MATERIAL_H

#include "dmaterial.h"

#include <qopenglfunctions_4_3_core.h>

namespace de {
	class DTexture;
}

class MultiTextureMaterial : public DMaterial
{
public:
	explicit MultiTextureMaterial();
	virtual ~MultiTextureMaterial();

	virtual void set_program();

	virtual void set_material_custom_loc();
	virtual void set_material_custom_data();
	virtual void clear_material_custom_data();

	virtual void update_tex_one_path(const char* path);
	virtual void update_tex_two_path(const char* path);

	virtual void update_time(const float& time);

private:
	GLuint time_loc_;
	GLuint tex_one_loc_;
	GLuint tex_two_loc_;

	float time_;
	GLuint tex_one_;
	GLuint tex_two_;

	const char* text_one_path_;
	const char* text_two_path_;

	de::DTexture* dtexture_;

};


#endif // !DREAM_ENGINE_MULTITEXTURE_MATERIAL_H
