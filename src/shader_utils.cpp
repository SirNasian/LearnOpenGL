#include "shader_utils.hpp"

#include <glad/glad.h>
#include <SDL3/SDL_log.h>

const char *getShaderTypeName(const GLenum shader_type) {
	switch (shader_type) {
		case GL_VERTEX_SHADER:   return "vertex";
		case GL_FRAGMENT_SHADER: return "fragment";
		default:                 return "unknown";
	}
}

namespace ShaderUtils {
	unsigned int compileShader(GLenum shader_type, const char *shader_source, const char *shader_name) {
		unsigned int shader = glCreateShader(shader_type);
		glShaderSource(shader, 1, &shader_source, NULL);
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char log[512];
			glGetShaderInfoLog(shader, 512, NULL, log);
			const char *message = "Failed to compile %s shader \"%s\"\n%s\n";
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, message, getShaderTypeName(shader_type), shader_name, log);
			return 0;
		}

		return shader;
	}
}
