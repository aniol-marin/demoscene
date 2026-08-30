export module sdl_wrapper;

import std;
import definitions;

extern "C" struct SDL_Window;
extern "C" struct SDL_Surface;

namespace SDL
{
    using namespace mole_def;
    export struct SDLManager
    {
        SDL_Window* window{};
        SDL_Surface* surface{};

        using pixel = std::uint32_t;
        using offset = std::uint_fast16_t;

        bool initialized{ false };
        bool locked{ false };

        SDLManager() = default;
        SDLManager(const SDLManager&) = delete ("a single instance is allowed, move it instead");
        SDLManager(SDLManager&&) noexcept = default;
        ~SDLManager() = default;

        bool Init(const Screen& screen);
        void Finalize();
        ProgramStatus PollSDLEvents();

        void LockSurface();
        void UnlockSurface();
        void UpdateSurface();

        void PutPixel(offset x, offset y, const pixel rgba);

    private:
        Screen m_screen{ 0, 0 };

        pixel& getPixel(offset x, offset y);
    };
}
