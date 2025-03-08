#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glad/glad.h>

class Triangle {
	public:
		Triangle();
		void render();
	private:
		static GLuint shader;
		static GLuint vao;
		static GLuint vbo;
};

namespace TriangleGLSL {
	const static char *VERTEX_SOURCE = R"(
		#version 330 core
		layout (location = 0) in vec3 pos;
		void main() {
			gl_Position = vec4(pos, 1.0);
		}
	)";
	const static char *FRAGMENT_SOURCE = R"(
		#version 330 core
		out vec4 frag_color;
		void main()
		{
			frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";
}

#endif
