#ifndef MOLE_SOUND_H
#define MOLE_SOUND_H

#include "definitions.h"
#include "sdl_wrapper.h"

using namespace mole_def;

namespace MoleDemo
{
    class SoundManager final
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

        void Init() override;
        void Finalize() override;
        void Load(const std::string& file) override;
        void Unload() override;
        void Play();
        void Stop();
        void Update();
        permille GetCurrentIntensity();
        seconds GetMusicDuration();
    };
}

#endif //! MOLE_SOUND_H
