export module sound;

import std;
import definitions;
import sdl_wrapper;

namespace MoleDemo
{
    export class SoundManager;
}

using namespace mole_def;

namespace MoleDemo
{
    class SoundManager
      : public Initializable
      , public Loadable
    {
        SDL::SDLManager& m;

    public:
        SoundManager() = delete;
        SoundManager(SDL::SDLManager& m);
        SoundManager(const SoundManager&) = delete;
        SoundManager(SoundManager&&) = default;
        ~SoundManager() = default;

        void Init();
        void Finalize();
        void Load(std::string_view file);
        void Unload();
        void Play();
        void Stop();
        void Update();
        permille GetCurrentIntensity();
        seconds GetMusicDuration();
    };
}
