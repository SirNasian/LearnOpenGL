#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glad/glad.h>

#include "shader.hpp"

class Triangle {
	public:
		GLfloat x, y, z;
		Triangle(const GLfloat x, const GLfloat y, const GLfloat z);
		void render();
	private:
		static Shader shader;
		static GLuint vao;
		static GLuint vbo;
		static GLuint uniform_offset;
};

namespace TriangleGLSL {
	const static char *VERTEX_SOURCE = R"(
		#version 330 core
		layout (location = 0) in vec3 pos;
		uniform vec3 offset;
		out vec3 vertex_colour;
		void main() {
			gl_Position = vec4(pos+offset, 1.0);
			vertex_colour = vec3(0.5+pos.x, 0.5+pos.y, 1.0);
		}
	)";
	const static char *FRAGMENT_SOURCE = R"(
		#version 330 core
		in vec3 vertex_colour;
		out vec4 fragment_colour;
		void main()
		{
			// vec4(1.0f, 0.5f, 0.2f, 1.0f);
			fragment_colour = vec4(vertex_colour, 1.0f);
		}
	)";
}

#endif
