#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("LearnOpenGL", 800, 600, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s\n", SDL_GetError());
		return 1;
	}

	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				done = true;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
