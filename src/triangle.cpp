#include "triangle.hpp"

#include <chrono>

#include <glm/gtc/type_ptr.hpp>

static const GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,  0.5f, 1.0f,
};

static const GLubyte texture_data[] = {
	0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF,
};

Shader Triangle::shader;
Texture2D Triangle::texture;
GLuint Triangle::vao = 0;
GLuint Triangle::vbo = 0;

Triangle::Triangle(glm::vec3 position) {
	Triangle::init();
	this->position = position;
}

static bool _initialised = false;
static GLuint _uniform_vertex_transform = 0;
static GLuint _uniform_fragment_texture = 0;
void Triangle::init() {
	if (_initialised) return;

	glGenVertexArrays(1, &Triangle::vao);
	glBindVertexArray(Triangle::vao);

	glGenBuffers(1, &Triangle::vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle::vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Triangle::shader.compile(TriangleGLSL::VERTEX_SOURCE, TriangleGLSL::FRAGMENT_SOURCE, "triangle");
	Triangle::texture.load(texture_data, 2, 2);
	_uniform_vertex_transform = glGetUniformLocation(Triangle::shader.getId(), "vertex_transform");
	_uniform_fragment_texture = glGetUniformLocation(Triangle::shader.getId(), "fragment_texture");

	_initialised = true;
}

void Triangle::render() {
	unsigned int time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch()).count();

	this->shader.use();
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, this->position);
	transform = glm::rotate(transform, glm::radians(float((time / 8) % 360)), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(_uniform_vertex_transform, 1, GL_FALSE, glm::value_ptr(transform));

	this->texture.bind(0);
	glUniform1i(_uniform_fragment_texture, 0);

	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
