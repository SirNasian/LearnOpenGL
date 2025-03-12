#ifndef BOX_HPP
#define BOX_HPP

#include <glm/glm.hpp>

#include "../shader.hpp"
#include "../texture2d.hpp"

class Box {
	public:
		Box(const glm::vec3 position = glm::vec3(), const glm::vec3 scale = glm::vec3(1.0f));
		void render(Shader &shader, Texture2D &texture, const float time);
	private:
		glm::vec3 position;
		glm::vec3 scale;
};

#endif
