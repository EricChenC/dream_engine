#include "dshader.h"
#include "ddir.h"

#include <iostream>

namespace de {
DShader::DShader()
{
}


DShader::~DShader()
{
}

void DShader::set_gl(QOpenGLFunctions_4_4_Core * gl)
{
	gl_ = gl;
}

const GLchar* DShader::ReadShader(const char* filename)
{
	de::DDir *dir = new de::DDir();
	char* full_path = dir->get_dir(filename);

#ifdef WIN32
	FILE* infile;
	fopen_s(&infile, full_path, "rb");
#else
	FILE* infile = fopen(full_path, "rb");
#endif // WIN32

	if (!infile) {
#ifdef _DEBUG
		std::cerr << "Unable to open file '" << full_path << "'" << std::endl;
#endif /* DEBUG */
		return NULL;
	}

	delete dir;

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	GLchar* source = new GLchar[len + 1];

	fread(source, 1, len, infile);
	fclose(infile);

	source[len] = 0;

	return const_cast<const GLchar*>(source);
}

//----------------------------------------------------------------------------

GLuint DShader::LoadShaders(ShaderInfo* shaders)
{
	if (shaders == NULL) { return 0; }

	GLuint program = gl_->glCreateProgram();

	ShaderInfo* entry = shaders;
	while (entry->type != GL_NONE) {
		GLuint shader = gl_->glCreateShader(entry->type);

		entry->shader = shader;

		const GLchar* source = ReadShader(entry->filename);
		if (source == NULL) {
			for (entry = shaders; entry->type != GL_NONE; ++entry) {
				gl_->glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		gl_->glShaderSource(shader, 1, &source, NULL);
		delete[] source;

		gl_->glCompileShader(shader);

		GLint compiled;
		gl_->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
#ifdef _DEBUG
			GLsizei len;
			gl_->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			gl_->glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
#endif /* DEBUG */

			return 0;
		}

		gl_->glAttachShader(program, shader);

		++entry;
	}

	gl_->glLinkProgram(program);

	GLint linked;
	gl_->glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
#ifdef _DEBUG
		GLsizei len;
		gl_->glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		gl_->glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
#endif /* DEBUG */

		for (entry = shaders; entry->type != GL_NONE; ++entry) {
			gl_->glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	return program;
}
}

