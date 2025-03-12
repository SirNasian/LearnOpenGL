#include "shader.hpp"

#include <algorithm>

#include <glm/ext.hpp>
#include <SDL3/SDL_log.h>

const char *getShaderTypeName(const GLenum shader_type) {
	switch (shader_type) {
		case GL_VERTEX_SHADER:   return "vertex";
		case GL_FRAGMENT_SHADER: return "fragment";
		default:                 return "unknown";
	}
}

Shader::Shader(const char *vertex_source, const char *fragment_source, const char *shader_name) {
	this->id = glCreateProgram();
	GLuint vertex_shader = this->compileShader(GL_VERTEX_SHADER, vertex_source, shader_name);
	GLuint fragment_shader = this->compileShader(GL_FRAGMENT_SHADER, fragment_source, shader_name);
	glAttachShader(this->id, vertex_shader);
	glAttachShader(this->id, fragment_shader);
	glLinkProgram(this->id);

	GLint success;
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar log[512];
		glGetProgramInfoLog(this->id, 512, NULL, log);
		const char *message = "Failed to link shader program \"%s\"\n%s\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, message, shader_name, log);
		glDeleteProgram(this->id);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader() {
	glDeleteProgram(this->id);
}

void Shader::setUniform1i(const GLchar *name, const GLint value) {
	const GLuint location = this->getUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::setUniformMatrix4fv(const GLchar *name, const GLsizei count, const glm::mat4 &value) {
	const GLuint location = this->getUniformLocation(name);
	glUniformMatrix4fv(location, count, GL_FALSE, glm::value_ptr(value));
}

static GLuint _id = 0;
void Shader::use() {
	if (this->id == _id) return;
	glUseProgram(this->id);
	_id = this->id;
}

GLuint Shader::compileShader(GLenum shader_type, const char *shader_source, const char *shader_name) {
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar log[512];
		glGetShaderInfoLog(shader, 512, NULL, log);
		const char *message = "Failed to compile %s shader \"%s\"\n%s\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, message, getShaderTypeName(shader_type), shader_name, log);
		return 0;
	}

	return shader;
}

GLuint Shader::getUniformLocation(const GLchar *name) {
	std::vector<std::pair<std::string, GLuint>>::iterator item = std::find_if(this->uniform_locations.begin(), this->uniform_locations.end(), [&name](const std::pair<std::string, GLuint> &item) { return std::string(name) == item.first; });
	if (item == this->uniform_locations.end()) {
		const GLuint location = glGetUniformLocation(this->id, name);
		this->uniform_locations.push_back(std::pair<std::string, GLuint>(name, location));
		return location;
	}
	return item->second;
}
