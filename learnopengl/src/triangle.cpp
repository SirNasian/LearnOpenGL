#include "triangle.hpp"

#include <glm/ext.hpp>

static const GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,  0.5f, 1.0f,
};

GLuint Triangle::vao = 0;
GLuint Triangle::vbo = 0;

Triangle::Triangle(glm::vec3 position) {
	Triangle::init();
	this->position = position;
}

static bool _initialised = false;
void Triangle::init() {
	if (_initialised) return;

	glGenVertexArrays(1, &Triangle::vao);
	glBindVertexArray(Triangle::vao);

	glGenBuffers(1, &Triangle::vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle::vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	_initialised = true;
}

void Triangle::render(Shader &shader, Texture2D &texture, const float time) {
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, this->position);
	transform = glm::rotate(transform, time, glm::vec3(0.0f, 0.0f, 1.0f));

	shader.use();
	shader.setUniformMatrix4fv("model_matrix", 1, transform);
	shader.setUniform1i("fragment_texture", 0);

	texture.bind(0);

	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
