#include <glad/glad.h>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>

const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 600;

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("LearnOpenGL", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	glad_glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				done = true;
		}
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DestroyContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
