#include <SDL.h>

export module sdl;

import definitions;

namespace MoleDemo {
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event events;
	export Uint8;
	export Uint16;
	export Uint32;
	export SDL_Surface;

	using Pixel = Uint32;

	export bool InitSDL() {
		if (SDL_Init(SDL_INIT_VIDEO) >= 0) {

			window = SDL_CreateWindow("Stars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
			surface = SDL_GetWindowSurface(window);
		}

		return window != nullptr;
	}
	export void FinalizeSDL() {
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	export ProgramStatus PollSDLEvents() {
		ProgramStatus status = ProgramStatus::RUNNING;
		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_KEYDOWN) {
				if (events.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					status = ProgramStatus::TERMINATE_OK;
				}
			}
			//User requests quit
			if (events.type == SDL_QUIT)
			{
				status = ProgramStatus::TERMINATE_OK;
			}
		}

		return status;
	}

	export void FillRect(SDL_Surface* surface, Color color) {
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x0, 0x5, 0x10));
	}
	export void LockSurface() {
		SDL_LockSurface(surface);
	}
	export void UnlockSurface() {
		SDL_UnlockSurface(surface);
	}
	export void UpdateSurface() {
		SDL_UpdateWindowSurface(window);
	}

	export Pixel* getPixel(Uint16 x, Uint16 y) {
		return reinterpret_cast<Uint32*>((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);

	}
	export void putPixel(Pixel& pixel, const Color& color) {
		pixel = color.rgba();
	}
}
