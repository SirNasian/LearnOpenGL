#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

class Texture2D {
	public:
		Texture2D(const GLsizei width, const GLsizei height, const GLubyte *data);
		~Texture2D();
		void bind(GLubyte unit = 0);
	private:
		GLuint id = 0;
};

#endif
