#ifndef _WAVEFRONT_OBJ_H_
#define _WAVEFRONT_OBJ_H_

#include <vector>
#include <array>
#include <utility>
#include <GLUT/glut.h>

class wavefront_obj_t  {
public:
	static constexpr GLuint gl_primitive_mode = GL_POLYGON;

	using double2 = std::array<double, 2>;
	using double3 = std::array<double, 3>;
	struct face_t {
		std::size_t idx_begin;
		std::size_t count;
		double3 normal;
	};
	std::vector<double3> vertices; // x, y, z
	std::vector<double3> normals; // x, y, z // unit vector or {0, 0, 0}
	std::vector<double2> texcoords; // u, v
	std::vector<face_t> faces;
	std::vector<int> vertex_indices;
	std::vector<int> normal_indices;
	std::vector<int> texcoord_indices;

	bool is_flat;
	std::pair<double3, double3> aabb; // bounding box

	wavefront_obj_t(char *path); // constructor: load from file
	void draw();
};


#endif // _WAVEFRONT_OBJ_H_
