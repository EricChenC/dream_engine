#ifndef DREAM_ENGINE_OBJECT_INSTANCED_H
#define DREAM_ENGINE_OBJECT_INSTANCED_H

#include "dview.h"

#include <qopenglfunctions_4_3_core.h>

#include "glm/glm.hpp"
#include <vector>

class ObjectInstancedMaterial;

class ObjectInstanced : public DView
{
public:
	explicit ObjectInstanced();
	virtual ~ObjectInstanced();

	virtual void initializeGL();
	virtual void paintGL(const int& time);
	virtual void disableGL();
	virtual void clearGL();

	void InitInstancedPosVec();

private:
	ObjectInstancedMaterial* instance_material_;

	std::vector<glm::vec3> instanced_pos_vec_;

	float x_value_;

};

#endif // !DREAM_ENGINE_OBJECT_INSTANCED_H
