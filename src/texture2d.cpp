#include "texture2d.hpp"

Texture2D::~Texture2D() {
	if (this->id) glDeleteTextures(1, &this->id);
}

void Texture2D::load(const GLubyte *data, GLsizei width, GLsizei height) {
	if (this->id) glDeleteTextures(1, &this->id);
	glGenTextures(1, &this->id);
	this->bind(0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::bind(GLubyte unit) {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, this->id);
}
