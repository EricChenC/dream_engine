#pragma once

#ifndef DMODEL_H
#define DMODEL_H

#include "glm/glm.hpp";

#include <vector>
#include <map>
#include <qopenglfunctions_4_3_core.h>

namespace de {
	class DIMaterial;
}

namespace de {
class DModel
{
public:
	explicit DModel();
	~DModel();

	bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
	);

	void indexVBO(
		std::vector<glm::vec3> & in_vertices,
		std::vector<glm::vec2> & in_uvs,
		std::vector<glm::vec3> & in_normals,

		std::vector<unsigned short> & out_indices,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
	);

	void Load(const char * path);
	void Render(int type = GL_TRIANGLES, unsigned int instances = 0);
	void Free();
	void set_gl(QOpenGLFunctions_4_3_Core* gl);
	void set_material(DIMaterial* material);

private:
	struct PackedVertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		bool operator<(const PackedVertex that) const {
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
		};
	};

	bool getSimilarVertexIndex_fast(
		PackedVertex & packed,
		std::map<PackedVertex, unsigned short> & VertexToOutIndex,
		unsigned short & result
	);

	QOpenGLFunctions_4_3_Core* gl_;
	DIMaterial* material_;
	
	GLuint vao_;
	GLuint index_bo_;
	GLuint vertex_bo_;
	GLuint uv_bo_;
	GLuint normal_bo_;

	int index_count_;

};
}


#endif // !DMODEL_H




