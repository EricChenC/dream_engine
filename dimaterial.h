
#ifndef DIMATERIAL_H
#define DIMATERIAL_H

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

};
}

#endif // !DIMATERIAL_H




