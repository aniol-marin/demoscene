module;

#include <string_view>

module sound;

import sdl_wrapper;

using namespace mole_def;

namespace MoleDemo
{
    SoundManager::SoundManager(SDL::SDLManager & m) : m{ m } {}

    void MoleDemo::SoundManager::Init()
    {
        // TO DO
    }
    void MoleDemo::SoundManager::Finalize()
    {
        // TO DO
    }

    void MoleDemo::SoundManager::Load(std::string_view file)
    {
        m.Load("resources/molelofi.mp3");
    }

    void MoleDemo::SoundManager::Unload()
    {
        // TO DO
    }

    void MoleDemo::SoundManager::Play()
    {
        // TO DO
    }

    void MoleDemo::SoundManager::Stop()
    {
        // TO DO
    }

    void MoleDemo::SoundManager::Update()
    {
        // TO DO
    }

    permille MoleDemo::SoundManager::GetCurrentIntensity()
    {
        return {};
    }

    seconds MoleDemo::SoundManager::GetMusicDuration()
    {
        return {};
    }
}
