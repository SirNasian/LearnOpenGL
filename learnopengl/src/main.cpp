#include <cstdio>

#include <glad/glad.h>
#include <glm/ext.hpp>
#include <SDL3/SDL.h>

#include "shader.hpp"
#include "triangle.hpp"

const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 600;

static const GLubyte texture_data[] = {
	0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF,
};

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("LearnOpenGL", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Shader shader(BasicShaderSource::VERTEX, BasicShaderSource::FRAGMENT, "basic");
	Texture2D texture(2, 2, texture_data);

	Triangle triangles[] = {
		Triangle(glm::vec3(-0.5f, 0.0f, 0.0f)),
		Triangle(glm::vec3( 0.5f, 0.0f, 0.0f)),
	};

	Uint64 last_render_time = SDL_GetTicksNS();
	Uint64 rate_ns = 1000000000 / 250;
	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				done = true;
		}

		Uint64 time_ns = SDL_GetTicksNS();
		Uint64 delta_ns = time_ns - last_render_time;
		if (delta_ns < rate_ns) {
			SDL_DelayNS(rate_ns - delta_ns);
			continue;
		}
		printf("fps: %.0f latency: %.3fms\n", 1000000000.0f / delta_ns, delta_ns / 1000000.0f);
		last_render_time = time_ns;

		float time  = time_ns  / 1000000000.0f;
		float delta = delta_ns / 1000000000.0f;

		glClear(GL_COLOR_BUFFER_BIT);

		float camera_distance = 6.0f;
		glm::vec3 camera_position(camera_distance * sin(time), 3.0f, camera_distance * cos(time));
		glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
		glm::mat4 camera(1.0f);

		camera *= glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);
		camera *= glm::lookAt(camera_position, camera_target, glm::vec3(0.0f, 1.0f, 0.0f));

		for (Triangle &t : triangles)
			t.render(shader, texture, camera, time);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DestroyContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
