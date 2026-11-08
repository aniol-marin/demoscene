module;

#include <string_view>

module sound;

import sdl_wrapper;

using namespace mole_def;

namespace MoleDemo
{
    SoundManager::SoundManager(SDL::SDLManager& m) : m{ m } {}

    void MoleDemo::SoundManager::Init()
    {
        // nothing to do
    }
    void MoleDemo::SoundManager::Finalize()
    {
        // nothing to do
    }

    void MoleDemo::SoundManager::Load(std::string_view file)
    {
        m.Load("resources/molelofi.mp3");
    }

    void MoleDemo::SoundManager::Unload()
    {
        // nothing to do
    }

    void MoleDemo::SoundManager::Play()
    {
        m.Play();
    }

    void MoleDemo::SoundManager::Stop()
    {
        m.Stop();
    }

    void MoleDemo::SoundManager::Update()
    {
        // nothing to do
    }

    permille MoleDemo::SoundManager::GetCurrentIntensity()
    {
        // TO DO
        return {};
    }

    seconds MoleDemo::SoundManager::GetMusicDuration()
    {
        return m.GetMusicDuration();
    }
}
