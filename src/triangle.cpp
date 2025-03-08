#include "triangle.hpp"
#include "shader_utils.hpp"

#include <glad/glad.h>

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

GLuint Triangle::shader = 0;
GLuint Triangle::vao = 0;
GLuint Triangle::vbo = 0;

Triangle::Triangle() {
	if (this->shader && this->vao && this->vbo)
		return;

	this->shader = ShaderUtils::createShaderProgram(TriangleGLSL::VERTEX_SOURCE,
		TriangleGLSL::FRAGMENT_SOURCE, "triangle");

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

void Triangle::render() {
	glBindVertexArray(this->vao);
	glUseProgram(this->shader);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
