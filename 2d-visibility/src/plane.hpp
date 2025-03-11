#ifndef PLANE_HPP
#define PLANE_HPP

#include <glm/glm.hpp>

class Plane {
	public:
		Plane();
		void render();
	private:
		glm::vec3 position;
		void initShader();
		void initMesh();
};

#endif
