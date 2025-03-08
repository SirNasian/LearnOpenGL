#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader {
	public:
		Shader() { this->id = 0; };
		Shader(const char *vertex_source, const char *fragment_source, const char *shader_name);
		~Shader();
		GLuint getId() { return this->id; };
		void compile(const char *vertex_source, const char *fragment_source, const char *shader_name);
		void use() { glUseProgram(this->id); };
	private:
		GLuint id;
		GLuint compileShader(GLenum shader_type, const char *shader_source, const char *shader_name);
};

#endif
