module; 

#include <string_view>

module sound;

using namespace mole_def;

namespace MoleDemo
{
    void MoleDemo::SoundManager::Init()
    {
        m.Init();
    }
    void MoleDemo::SoundManager::Finalize()
    {
        m.Finalize();
    }

    void MoleDemo::SoundManager::Load(std::string_view file)
    {
        m.Load("resources/molelofi.mp3");
    }

    void MoleDemo::SoundManager::Unload()
    {
        m.Unload();
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
        m.Update();
    }

    permille MoleDemo::SoundManager::GetCurrentIntensity()
    {
        return m.GetIntensity();
    }

    seconds MoleDemo::SoundManager::GetMusicDuration()
    {
        return m.GetDuration();
    }
}
