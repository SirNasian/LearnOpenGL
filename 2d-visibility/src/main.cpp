#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "plane.hpp"

int main() {
	SDL_Window *window = SDL_CreateWindow("2D Visibility", 600, 600, SDL_WINDOW_OPENGL);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s", SDL_GetError());
		return 1;
	}

	SDL_GL_CreateContext(window);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	glViewport(0, 0, 600, 600);
	glClearColor(0.1f, 0.15f, 0.2f, 1.0f);

	Plane plane;
	float cursor_x, cursor_y;

	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
				break;
			}
		}

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
