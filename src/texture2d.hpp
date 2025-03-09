#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

class Texture2D {
	public:
		Texture2D() {};
		~Texture2D();
		void load(const GLubyte *data, GLsizei width, GLsizei  height);
		void bind(GLubyte unit = 0);
	private:
		GLuint id = 0;
};

#endif
