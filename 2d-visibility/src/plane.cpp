#include "plane.hpp"

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <SDL3/SDL.h>

static const char *_vertex_shader_source = R"(
	#version 330 core

	layout (location = 0) in vec2 vertex_position;
	layout (location = 1) in vec2 vertex_uv;
	out vec2 fragment_uv;

	void main() {
		gl_Position = vec4(vertex_position, 0.0, 1.0);
		fragment_uv = vertex_uv;
	}
)";

static const char *_fragment_shader_source = R"(
	#version 330 core

	uniform sampler2D fragment_texture;
	uniform vec2 cursor_position;

	in vec2 fragment_uv;
	out vec4 fragment_colour;

	void main() {
		fragment_colour = vec4(0.0, 0.0, 0.0, 0.0);
		float distance = length(cursor_position - fragment_uv);
		float colour_multiplier = (0.8 - (distance * 1.6));

		if (texture(fragment_texture, fragment_uv).r > 0.0) {
			fragment_colour = vec4(1.0, 0.0, 0.0, 1.0) * colour_multiplier;
			return;
		}

		if (distance > 0.5) return;

		int max_steps = 1024;
		vec2 direction = (cursor_position - fragment_uv);
		for (int i = 0; i < max_steps; i++)
			if (texture(fragment_texture, fragment_uv + (i * direction / max_steps)).r > 0)
				return;

		fragment_colour = vec4(1.0, 1.0, 1.0, 1.0) * colour_multiplier;
	}
)";

static const GLubyte _texture_data[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static GLchar _log[512];
static GLsizei _log_length;

static GLuint _shader = 0;
static GLuint _texture = 0;
static GLuint _vao = 0;
static GLuint _vbo = 0;
static GLuint _ebo = 0;

static const GLfloat _vertices[] = {
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 1.0f,
};

static const GLuint _indices[] = {
	0, 1, 2,
	3, 2, 1,
};

Plane::Plane() {
	this->initMesh();
	this->initShader();
	this->initTexture();
}

void Plane::render(glm::vec2 cursor_position) {
	glUseProgram(_shader);
	glUniform2fv(glGetUniformLocation(_shader, "cursor_position"), 1, glm::value_ptr(cursor_position));
	glUniform1i(glGetUniformLocation(_shader, "fragment_texture"), 0);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Plane::initMesh() {
	if (_vao && _vbo && _ebo) return;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Plane::initShader() {
	if (_shader) return;

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &_vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderInfoLog(vertex_shader, 512, &_log_length, _log); 
	if (_log_length) SDL_LogError(SDL_LOG_CATEGORY_ERROR, "vertex_shader: %s", _log);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &_fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderInfoLog(fragment_shader, 512, &_log_length, _log); 
	if (_log_length) SDL_LogError(SDL_LOG_CATEGORY_ERROR, "fragment_shader: %s", _log);

	_shader = glCreateProgram();
	glAttachShader(_shader, vertex_shader);
	glAttachShader(_shader, fragment_shader);
	glLinkProgram(_shader);
	glGetProgramInfoLog(_shader, 512, &_log_length, _log);
	if (_log_length) SDL_LogError(SDL_LOG_CATEGORY_ERROR, "shader: %s", _log);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Plane::initTexture() {
	if (_texture) return;

	glGenTextures(1, &_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE0, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 8, 8, 0, GL_RED, GL_UNSIGNED_BYTE, _texture_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
