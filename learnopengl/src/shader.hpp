#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader {
	public:
		Shader() {};
		~Shader();
		GLuint getId() { return this->id; };
		void compile(const char *vertex_source, const char *fragment_source, const char *shader_name);
		void use() { glUseProgram(this->id); };
	private:
		GLuint id = 0;
		GLuint compileShader(GLenum shader_type, const char *shader_source, const char *shader_name);
};

#endif
