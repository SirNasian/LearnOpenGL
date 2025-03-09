#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glad/glad.h>

#include "shader.hpp"
#include "texture2d.hpp"

class Triangle {
	public:
		GLfloat x, y, z;
		Triangle(const GLfloat x, const GLfloat y, const GLfloat z);
		static void init();
		void render();
	private:
		static Shader shader;
		static Texture2D texture;
		static GLuint vao;
		static GLuint vbo;
};

namespace TriangleGLSL {
	const static char *VERTEX_SOURCE = R"(
		#version 330 core

		uniform vec3 vertex_offset;

		layout (location = 0) in vec3 vertex_pos;
		layout (location = 1) in vec2 vertex_uv;

		out vec2 fragment_uv;

		void main() {
			fragment_uv = vertex_uv;
			gl_Position = vec4(vertex_pos+vertex_offset, 1.0);
		}
	)";
	const static char *FRAGMENT_SOURCE = R"(
		#version 330 core

		uniform sampler2D fragment_texture;

		in vec2 fragment_uv;

		out vec4 colour;

		void main()
		{
			colour = texture(fragment_texture, fragment_uv);
		}
	)";
}

#endif
