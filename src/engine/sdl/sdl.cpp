#include "sdl.h"

#include <string>
#include <iostream>
#include <exception>

/*
#include "SDL2/SDL.h"
*/

import definitions;

/*
namespace
{
	//TO DO avoid global state
	SDL_Window* window {};
	SDL_Surface* surface {};
}
*/

SDL::SDLManager::pixel dummy {};

SDL::SDLManager:: ~SDLManager()
{
}

bool SDL::SDLManager::Init(const Screen& screen)
{
	g_screen = screen;

	/*
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) >= 0) {

		window = SDL_CreateWindow("Mole Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_SHOWN);
		surface = SDL_GetWindowSurface(window);
		initialized = surface != nullptr;
	}
	*/
	initialized = true;//TO DO delete

	return initialized;
}

void SDL::SDLManager::Finalize()
{
	/*
	if (initialized)
	{
		SDL_DestroyWindow(window);
		SDL_Quit(); // assumes video is the last
	}

	initialized = false;
	*/
	initialized = true;//TO DO delete
}

ProgramStatus SDL::SDLManager::PollSDLEvents()
{
	/*
	SDL_Event events {};
	*/
	ProgramStatus status { ProgramStatus::RUNNING };

	/*
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

*/
	return status;
}

void SDL::SDLManager::LockSurface()
{
	if(!initialized)
	{
		throw std::exception{};
	}

	/*
	SDL_LockSurface(surface);
	*/
	locked = true;
}

void SDL::SDLManager::UnlockSurface()
{
	if(!initialized)
	{
		throw std::exception{};
	}

	/*
	SDL_UnlockSurface(surface);
	*/
	locked = false;
}

void SDL::SDLManager::UpdateSurface()
{
	if(!initialized)
	{
		throw std::exception{};
	}

	if (!locked)
	{
		throw std::exception();
	}

	/*
	SDL_UpdateWindowSurface(window);
	*/
}

SDL::SDLManager::pixel& SDL::SDLManager::getPixel(offset x, offset y)
{
	if(!initialized)
	{
		throw std::exception{};
	}
	if(g_screen.w <= x || g_screen.h <= y)
	{
		throw std::exception{};
	}

	/*
	return *reinterpret_cast<uint32_t*>((uint8_t*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
	*/
	return dummy;
}

void SDL::SDLManager::PutPixel(const offset x, const offset y, const pixel rgba)
{
	if(!initialized)
	{
		throw std::exception{};
	}
	if(g_screen.w <= x || g_screen.h <= y)
	{
		throw std::exception{};
	}

	pixel& pixel = getPixel(x, y);
	pixel = rgba;
}
