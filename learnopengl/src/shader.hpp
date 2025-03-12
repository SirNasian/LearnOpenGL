#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <utility>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
	public:
		Shader(const char *vertex_source, const char *fragment_source, const char *shader_name);
		~Shader();
		GLuint getId() { return this->id; };
		void setUniform1i(const GLchar *name, const GLint value);
		void setUniformMatrix4fv(const GLchar *name, const GLsizei count, const glm::mat4 &value);
		void use() { glUseProgram(this->id); };
	private:
		GLuint id = 0;
		std::vector<std::pair<std::string, GLuint>> uniform_locations;
		GLuint compileShader(const GLenum shader_type, const char *shader_source, const char *shader_name);
		GLuint getUniformLocation(const GLchar *name);
};

namespace BasicShaderSource {
	const static char *VERTEX = R"(
		#version 330 core

		uniform mat4 model_matrix;
		uniform mat4 view_matrix;
		uniform mat4 projection_matrix;

		layout (location = 0) in vec3 vertex_position;
		layout (location = 1) in vec3 vertex_normal;
		layout (location = 2) in vec2 vertex_uv;

		out vec2 fragment_uv;

		void main() {
			gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);
			fragment_uv = vertex_uv;
		}
	)";
	const static char *FRAGMENT = R"(
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
