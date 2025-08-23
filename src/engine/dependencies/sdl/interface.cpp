module;

#include "SDL2/SDL.h"

export module sdl;

import std.compat;
import definitions;

namespace SDL
{
	export struct SDLManager;
}

namespace SDL {

	struct SDLManager
	{
		SDL_Window* window {};
		SDL_Surface* surface {};

		using pixel = uint32_t;
		using offset = uint_fast16_t;

		Screen g_screen { 0, 0 };
		bool initialized { false };
		bool locked { false };

		SDLManager() = default;
		SDLManager(const SDLManager&) = delete;
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

