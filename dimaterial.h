
#ifndef DIMATERIAL_H
#define DIMATERIAL_H

#include <stdlib.h>

class QOpenGLFunctions_4_3_Core;

namespace de {
class DIMaterial
{
public:
	explicit DIMaterial() {}
	virtual ~DIMaterial() {}

	virtual void GenMaterial(QOpenGLFunctions_4_3_Core* gl) = 0;
	virtual void BindMaterial() = 0;
	virtual void DeleteMaterial() = 0;

	virtual void set_program() = 0;
	virtual void set_m(const float* m = NULL) = 0;
	virtual void set_v(const float* v = NULL) = 0;
	virtual void set_p(const float* p = NULL) = 0;
	virtual void set_mv(const float* mv = NULL) = 0;
	virtual void set_mvp(const float* mvp = NULL) = 0;
	virtual void set_light_position(const float* light_position = NULL) = 0;

};
}

#endif // !DIMATERIAL_H




