#ifndef PLANE_HPP
#define PLANE_HPP

#include <glm/glm.hpp>

class Plane {
	public:
		Plane();
		void render(glm::vec2 cursor_position);
	private:
		glm::vec3 position;
		void initMesh();
		void initShader();
		void initTexture();
};

#endif
