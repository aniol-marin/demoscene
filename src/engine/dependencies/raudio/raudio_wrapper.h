#ifndef MOLE_RAUDIO_WRAPPER_H
#define MOLE_RAUDIO_WRAPPER_H

#include <filesystem>
#include <queue>
#include <string_view>

#include "definitions.h"
#include "raudio.h"

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

#endif // !MOLE_RAUDIO_WRAPPER_H
