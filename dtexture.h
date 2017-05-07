#pragma once

#ifndef DTEXTURE_H
#define DTEXTURE_H

#include "vdds.h"

namespace de {

class DTexture
{
public:
	explicit DTexture();
	~DTexture();

	void vglUnloadImage(vglImageData* image);
	GLuint vglLoadTexture(const char* filename,
		GLuint texture,
		vglImageData* image);

	void set_gl(QOpenGLFunctions_4_3_Core* gl);

private:
	bool vgl_DDSHeaderToImageDataHeader(const DDS_FILE_HEADER& header, vglImageData* image);
	GLsizei vgl_GetDDSStride(const DDS_FILE_HEADER& header, GLsizei width);
	GLenum vgl_GetTargetFromDDSHeader(const DDS_FILE_HEADER& header);
	void vglLoadDDS(const char* filename, vglImageData* image);
	void vglLoadImage(const char* filename, vglImageData* image);

	QOpenGLFunctions_4_3_Core* gl_;

};

}


#endif // !DTEXTURE_H




