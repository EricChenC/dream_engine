#ifndef DREAM_ENGINE_MULTI_TEXTURE_H
#define DREAM_ENGINE_MULTI_TEXTURE_H

#include "dview.h"

class MultiTextureMaterial;

class MultiTexture : public DView
{
public:
	explicit MultiTexture();
	virtual ~MultiTexture();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

private:
	MultiTextureMaterial* multi_tex_material_;

};


#endif // !DREAM_ENGINE_MULTI_TEXTURE_H



