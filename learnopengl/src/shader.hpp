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
		void use();
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

		out vec3 world_position;
		out vec3 world_normal;
		out vec2 fragment_uv;

		void main() {
			gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);
			world_position = vec3(model_matrix * vec4(vertex_position, 1.0));
			world_normal = mat3(transpose(inverse(model_matrix))) * normalize(vertex_normal);
			fragment_uv = vertex_uv;
		}
	)";
	const static char *FRAGMENT = R"(
		#version 330 core

		struct Material {
			sampler2D texture;
			vec3 emissive_colour;
		};

		struct Light {
			vec3 position;
		};

		uniform Material material;
		uniform Light[256] lights;
		uniform int lights_count;
		uniform vec3 camera_position;

		in vec3 world_position;
		in vec3 world_normal;
		in vec2 fragment_uv;

		out vec4 colour;

		void main()
		{
			vec3 ambient_colour = vec3(0.1);
			vec3 diffuse_colour = vec3(0.0);
			vec3 specular_colour = vec3(0.0);
			vec3 camera_direction = normalize(camera_position - world_position);

			for (int i = 0; i < lights_count; i++) {
				vec3 light_direction = normalize(lights[i].position - world_position);
				diffuse_colour += vec3(0.4) * max(dot(light_direction, world_normal), 0);

				vec3 reflect_direction = reflect(-light_direction, world_normal);
				specular_colour += vec3(0.5) * pow(max(dot(reflect_direction, camera_direction), 0), 64);
			}

			colour  = texture(material.texture, fragment_uv);
			colour *= vec4((ambient_colour + diffuse_colour + specular_colour), 1.0);
			if (dot(material.emissive_colour, material.emissive_colour) > 0.0)
				colour = vec4(material.emissive_colour, 1.0);
		}
	)";
}

#endif
