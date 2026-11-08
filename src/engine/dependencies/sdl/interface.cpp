export module sdl_wrapper;

import std;
import definitions;

extern "C" struct SDL_Window;
extern "C" struct SDL_Surface;
extern "C" struct MIX_Mixer;
extern "C" struct MIX_Audio;
extern "C" struct MIX_Track;

namespace SDL
{
    using namespace mole_def;
    export struct SDLManager
    {
        SDL_Window* window{};
        SDL_Surface* surface{};
        MIX_Mixer* mixer{};
        MIX_Audio* audio{};
        MIX_Track* track{};

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

        void Load(std::filesystem::path const& path);
        void Play();
        void Stop();
        seconds GetMusicDuration();

    private:
        Screen m_screen{ 0, 0 };

        pixel& getPixel(offset x, offset y);
    };
}
