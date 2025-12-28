#ifndef MOLE_SDL_WRAPPER
#define MOLE_SDL_WRAPPER

#include "definitions.h"

#include <exception>
#include "SDL2/SDL.h"

namespace SDL
{
    using namespace mole_def;

    struct SDLManager
    {
        SDL_Window* window;
        SDL_Surface* surface;

        typedef unsigned int pixel;
        typedef unsigned short int offset;

        Screen g_screen;
        bool initialized;
        bool locked;

        SDLManager() {}
        SDLManager(const SDLManager&) { throw std::exception(); }
        ~SDLManager() {}

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

#endif // !MOLE_SDL_WRAPPER
