#ifndef SHADER_UTILS_HPP
#define SHADER_UTILS_HPP

#include <glad/glad.h>

namespace ShaderUtils {
	unsigned int compileShader(GLenum shader_type, const char *shader_source, const char *shader_name = "unknown");
}

#endif
