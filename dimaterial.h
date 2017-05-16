
#ifndef DIMATERIAL_H
#define DIMATERIAL_H

namespace de {
class DIMaterial
{
public:
	explicit DIMaterial() {}
	virtual ~DIMaterial() {}

	virtual void GenMaterial() = 0;
	virtual void BindMaterial() = 0;
	virtual void DeleteMaterial() = 0;

};
}

#endif // !DIMATERIAL_H




