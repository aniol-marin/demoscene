module;
#include <SDL.h>

export module sdl;

import definitions;
import <string>;
import <iostream>;

namespace SDL {

	export ProgramStatus PollSDLEvents();

	export bool InitVideo(const Screen& screen);
	export void FinalizeVideo();

	export void LockSurface();
	export void UnlockSurface();
	export void UpdateSurface();
	export void PutPixel(uint16_t x, uint16_t y, const uint32_t rgba);

	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event events;

	using Pixel = uint32_t;
	Pixel* getPixel(uint16_t x, uint16_t y);
}

bool SDL::InitVideo(const Screen& screen) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) >= 0) {

		window = SDL_CreateWindow("Mole Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN);
		surface = SDL_GetWindowSurface(window);
	}

	return window != nullptr;
}

void SDL::FinalizeVideo() {
	SDL_DestroyWindow(window);
	SDL_Quit(); // assumes video is the last
}

ProgramStatus SDL::PollSDLEvents() {
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

void SDL::LockSurface() {
	SDL_LockSurface(surface);
}

void SDL::UnlockSurface() {
	SDL_UnlockSurface(surface);
}

void SDL::UpdateSurface() {
	SDL_UpdateWindowSurface(window);
}

SDL::Pixel* SDL::getPixel(uint16_t x, uint16_t y) {
	return reinterpret_cast<uint32_t*>((uint8_t*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
}

void SDL::PutPixel(uint16_t x, uint16_t y, const uint32_t rgba) {
	Pixel* pixel = getPixel(x, y);
	*pixel = rgba;
}