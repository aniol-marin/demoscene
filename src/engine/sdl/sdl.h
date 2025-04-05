

#ifndef DEMOSCENE_SDL_WRAPPER_H
#define DEMOSCENE_SDL_WRAPPER_H

#include <string>
#include <iostream>
#include <exception>
#include <cstdint>

import definitions;
/*
#include "SDL2/SDL.h"
*/


/*
namespace
{
	//TO DO avoid global state
	SDL_Window* window {};
	SDL_Surface* surface {};
}
*/

namespace SDL {

	struct SDLManager
	{
		using pixel = uint32_t;
		using offset = uint_fast16_t;

		Screen g_screen { 0, 0 };
		bool initialized { false };
		bool locked { false };

		SDLManager() = default;
		SDLManager(const SDLManager&) = default;
		SDLManager(SDLManager&&) = default;
		~SDLManager() = default;

		bool Init(const Screen& screen);
		void Finalize();
		ProgramStatus PollSDLEvents();

		void LockSurface();
		void UnlockSurface();
		void UpdateSurface();

		void PutPixel(offset x, offset y, const pixel rgba);

	private:

		pixel& getPixel(offset x, offset y);

	};
}
#endif // !DEMOSCENE_SDL_WRAPPER_H

