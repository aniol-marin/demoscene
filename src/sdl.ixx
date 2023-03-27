module;
#include <SDL.h>

export module sdl;

import definitions;

namespace SDL {
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event events;

	using Pixel = uint32_t;

	export bool Init(const Screen& screen) {
		if (SDL_Init(SDL_INIT_VIDEO) >= 0) {

			window = SDL_CreateWindow("Mole Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN);
			surface = SDL_GetWindowSurface(window);
		}

		return window != nullptr;
	}
	export void Finalize() {
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

	Pixel* getPixel(uint16_t x, uint16_t y) {
		return reinterpret_cast<uint32_t*>((uint8_t*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
	}

	export void PutPixel(uint16_t x, uint16_t y, const uint32_t rgba) {
		Pixel* pixel = getPixel(x, y);
		*pixel = rgba;
	}
}
