module;

#include <filesystem>
#include <string_view>

#include "raudio.h"

export module raudio_wrapper;

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
        AudioManager() = default;
        AudioManager(const AudioManager&) = delete;
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
