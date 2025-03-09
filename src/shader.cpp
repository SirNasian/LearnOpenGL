#include "shader.hpp"

#include <glad/glad.h>
#include <SDL3/SDL_log.h>

const char *getShaderTypeName(const GLenum shader_type) {
	switch (shader_type) {
		case GL_VERTEX_SHADER:   return "vertex";
		case GL_FRAGMENT_SHADER: return "fragment";
		default:                 return "unknown";
	}
}

Shader::~Shader() {
	if (this->id) glDeleteProgram(this->id);
}

void Shader::compile(const char *vertex_source, const char *fragment_source, const char *shader_name) {
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
