#include "dmodel.h"
#include "ddir.h"
#include "dimaterial.h"

#include <map>

namespace de {
DModel::DModel()
	: material_(NULL)
{
}


DModel::~DModel()
{
}

bool DModel::loadOBJ(const char * path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	de::DDir *dir = new de::DDir();
	char* full_path = dir->get_dir(path);

	printf("Loading OBJ file %s...\n", full_path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(full_path, "r");
	delete dir;

	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			if (matches == 12) 
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[2]);
				uvIndices.push_back(uvIndex[3]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);
			}
			else if(matches == 9)
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else
			{
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}

	return true;
}

bool DModel::getSimilarVertexIndex_fast(
	PackedVertex & packed,
	std::map<PackedVertex, unsigned short> & VertexToOutIndex,
	unsigned short & result
) {
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void DModel::indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<unsigned short>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i<in_vertices.size(); i++) {

		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };


		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

void DModel::Load(const char * path)
{
	std::vector<glm::vec3> vertexs;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool load_obj = loadOBJ(path, vertexs, uvs, normals);

	std::vector<unsigned short> indexs;
	std::vector<glm::vec3> out_vertexs;
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;

	indexVBO(vertexs, uvs, normals, indexs, out_vertexs, out_uvs, out_normals);

	index_count_ = indexs.size();

	gl_->glGenVertexArrays(1, &vao_);
	gl_->glBindVertexArray(vao_);

	gl_->glGenBuffers(1, &index_bo_);
	gl_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_bo_);
	gl_->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs.size() * sizeof(unsigned short), &indexs[0], GL_STATIC_DRAW);
	
	gl_->glGenBuffers(1, &vertex_bo_);
	gl_->glBindBuffer(GL_ARRAY_BUFFER, vertex_bo_);
	gl_->glBufferData(GL_ARRAY_BUFFER, out_vertexs.size() * sizeof(glm::vec3), &out_vertexs[0], GL_STATIC_DRAW);
	gl_->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_->glEnableVertexAttribArray(0);

	gl_->glGenBuffers(1, &uv_bo_);
	gl_->glBindBuffer(GL_ARRAY_BUFFER, uv_bo_);
	gl_->glBufferData(GL_ARRAY_BUFFER, out_uvs.size() * sizeof(glm::vec2), &out_uvs[0], GL_STATIC_DRAW);
	gl_->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_->glEnableVertexAttribArray(1);

	gl_->glGenBuffers(1, &normal_bo_);
	gl_->glBindBuffer(GL_ARRAY_BUFFER, normal_bo_);
	gl_->glBufferData(GL_ARRAY_BUFFER, out_normals.size() * sizeof(glm::vec3), &out_normals[0], GL_STATIC_DRAW);
	gl_->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	gl_->glEnableVertexAttribArray(2);

	if (material_ != NULL) {
		material_->GenMaterial(gl_);
	}

	gl_->glBindVertexArray(0);

}

void DModel::Render(int type, unsigned int instances)
{
	gl_->glBindVertexArray(vao_);

	if (instances > 0) {
		gl_->glDrawElementsInstanced(type, index_count_, GL_UNSIGNED_SHORT, NULL, instances);
	}
	else {
		gl_->glDrawElements(type, index_count_, GL_UNSIGNED_SHORT, NULL);
	}

	gl_->glBindVertexArray(0);
}

void DModel::Free()
{
	if (material_ != NULL) {
		material_->DeleteMaterial();
	}

	gl_->glDeleteBuffers(1, &index_bo_);
	gl_->glDeleteBuffers(1, &vertex_bo_);
	gl_->glDeleteBuffers(1, &uv_bo_);
	gl_->glDeleteBuffers(1, &normal_bo_);
	gl_->glDeleteVertexArrays(1, &vao_);
}

void DModel::set_gl(QOpenGLFunctions_4_4_Core * gl)
{
	gl_ = gl;
}

void DModel::set_material(DIMaterial * material)
{
	material_ = material;
}





}

