#pragma once

#ifndef DSHADER_H
#define DSHADER_H

#include <qopenglfunctions_4_3_core.h>

namespace de {

typedef struct {
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

class DShader
{
public:
	explicit DShader();
	~DShader();

	void set_gl(QOpenGLFunctions_4_3_Core* gl);
	const GLchar* ReadShader(const char* filename);
	GLuint LoadShaders(ShaderInfo* shaders);

private:
	QOpenGLFunctions_4_3_Core* gl_;

	

};
}


#endif // !DSHADER_H




