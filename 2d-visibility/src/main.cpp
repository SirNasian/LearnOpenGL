#include <cstdio>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "plane.hpp"

int main() {
	SDL_Window *window = SDL_CreateWindow("2D Visibility", 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_TRANSPARENT);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s", SDL_GetError());
		return 1;
	}

	SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(0);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	glViewport(0, 0, 600, 600);
	glClearColor(0.1f, 0.15f, 0.2f, 0.0f);

	Plane plane;
	float cursor_x, cursor_y;

	Uint64 _time = SDL_GetTicksNS();
	Uint64 _rate_ns = (1.0f / 250.0f) * 1000000000.0f;
	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
				break;
			}
		}

		Uint64 time = SDL_GetTicksNS();
		if ((time - _time) < _rate_ns) {
			SDL_DelayNS(_rate_ns - (time - _time));
			continue;
		}
		printf("fps: %.3f latency: %.3fms\n", 1000000000.0f / (time - _time), (time - _time) / 1000000.0f);
		_time = time;

		SDL_GetMouseState(&cursor_x, &cursor_y);
		cursor_x = 0.0f + (cursor_x / 600.0f);
		cursor_y = 1.0f - (cursor_y / 600.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		plane.render(glm::vec2(cursor_x, cursor_y));
		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
