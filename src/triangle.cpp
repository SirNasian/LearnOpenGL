#include "triangle.hpp"

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

Triangle::Triangle(const GLfloat x, const GLfloat y, const GLfloat z) {
	Triangle::init();
	this->x = x;
	this->y = y;
	this->z = z;
}

static bool _initialised = false;
static GLuint _uniform_vertex_offset = 0;
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
	_uniform_vertex_offset = glGetUniformLocation(Triangle::shader.getId(), "vertex_offset");
	_uniform_fragment_texture = glGetUniformLocation(Triangle::shader.getId(), "fragment_texture");

	_initialised = true;
}

void Triangle::render() {
	this->shader.use();
	glUniform3f(_uniform_vertex_offset, this->x, this->y, this->z);

	this->texture.bind(0);
	glUniform1i(_uniform_fragment_texture, 0);

	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
