#include "sdl_wrapper.h"

#include "SDL3/SDL.h"
#include <cstdint>
#include <exception>

using namespace mole_def;

namespace SDL
{
    bool SDLManager::Init(const Screen& screen)
    {
        g_screen = screen;

        if (SDL_InitSubSystem(SDL_INIT_VIDEO) >= 0)
        {

            window = SDL_CreateWindow("Mole Demo", screen.w, screen.h, SDL_WINDOW_KEYBOARD_GRABBED);
            surface = SDL_GetWindowSurface(window);
            initialized = surface != NULL;
        }

        return initialized;
    }

    void SDLManager::Finalize()
    {
        if (initialized)
        {
            SDL_DestroyWindow(window);
            SDL_Quit(); // assumes video is the last
        }

        initialized = false;
    }

    ProgramStatus SDLManager::PollSDLEvents()
    {
        SDL_Event events;

        ProgramStatus status(mole_def::PROGRAM_RUNNING);

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_EVENT_KEY_DOWN && events.key.scancode == SDL_SCANCODE_ESCAPE)
            {
		status = mole_def::PROGRAM_TERMINATE_OK;
            }
            // User requests quit
            else if (events.type == SDL_EVENT_QUIT)
            {
                status = mole_def::PROGRAM_TERMINATE_OK;
            }
        }

        return status;
    }

    void SDLManager::LockSurface()
    {
        if (!initialized)
        {
            throw std::exception();
        }

        SDL_LockSurface(surface);
        locked = true;
    }

    void SDLManager::UnlockSurface()
    {
        if (!initialized)
        {
            throw std::exception();
        }

        SDL_UnlockSurface(surface);
        locked = false;
    }

    void SDLManager::UpdateSurface()
    {
        if (!initialized)
        {
            throw std::exception();
        }

        if (!locked)
        {
            throw std::exception();
        }

        SDL_UpdateWindowSurface(window);
    }

    SDLManager::pixel& SDLManager::getPixel(offset x, offset y)
    {
        if (!initialized)
        {
            throw std::exception();
        }
        if (g_screen.w <= x || g_screen.h <= y)
        {
            throw std::exception();
        }

        return *reinterpret_cast<std::uint32_t*>((std::uint8_t*) surface->pixels + y * surface->pitch +
                                                 x * SDL_BYTESPERPIXEL(surface->format));
    }

    void SDLManager::PutPixel(const offset x, const offset y, const pixel rgba)
    {
        if (!initialized)
        {
            throw std::exception();
        }
        if (g_screen.w <= x || g_screen.h <= y)
        {
            throw std::exception();
        }

        pixel& pixel = getPixel(x, y);
        pixel = rgba;
    }
}
