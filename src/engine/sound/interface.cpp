module;

#include <string_view>

export module sound;

import definitions;
import raudio_wrapper;

namespace MoleDemo
{
    export class SoundManager;
}

using namespace mole_def;

namespace MoleDemo
{
    class SoundManager final
      : public Initializable
      , public Loadable
    {
        raudio::AudioManager m{};

    public:
        SoundManager() = default;
        SoundManager(const SoundManager&) = delete;
        SoundManager(SoundManager&&) = default;
        ~SoundManager() = default;

        void Init() override;
        void Finalize() override;
        void Load(std::string_view file) override;
        void Unload() override;
        void Play();
        void Stop();
        void Update();
        permille GetCurrentIntensity();
        seconds GetMusicDuration();
    };
}
