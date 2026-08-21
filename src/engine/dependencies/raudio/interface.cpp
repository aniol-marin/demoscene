module;

#include "raudio.h"

export module raudio_wrapper;

import std;
import definitions;

namespace raudio
{
    export struct AudioManager;
}

namespace raudio
{
    using namespace mole_def;
    struct AudioManager
    {
        AudioManager();
        AudioManager(const AudioManager&) = delete ("a single instance is allowed, move it instead");
        AudioManager(AudioManager&&) = default;
        ~AudioManager();

        void Init();
        void Finalize();
        void Load(std::filesystem::path source);
        void Unload();

        void Play();
        void Stop();
        void Update();

        seconds GetDuration();
        permille GetIntensity();

    private:
        bool initialized{ false };
        bool loaded{ false };
        Music music{};

        static void SampleIntensity(void* buffer, unsigned int frames);
    };
}
