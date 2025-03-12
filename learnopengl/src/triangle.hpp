#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "texture2d.hpp"

class Triangle {
	public:
		glm::vec3 position;
		Triangle(glm::vec3 position);
		static void init();
		void render(Shader &shader, Texture2D &texture, const glm::mat4 &camera, const float time);
	private:
		static Texture2D texture;
		static GLuint vao;
		static GLuint vbo;
};

#endif
