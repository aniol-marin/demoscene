export module sound;

import std;
import definitions;
import raudio;

namespace MoleDemo
{
	export class SoundManager;
}

class MoleDemo::SoundManager : 
	public Initializable,
	public Loadable
{
	RAudio::AudioManager m{};
public:

	SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	SoundManager(SoundManager&&) = default;
	~SoundManager() = default;

	void Init();
	void Finalize();
	void Load(std::string file);
	void Unload();
	void Play();
	void Stop();
	void Update();
	permille GetCurrentIntensity();
	seconds GetMusicDuration();
};

void MoleDemo::SoundManager::Init() {
	m.Init();
}
void MoleDemo::SoundManager::Finalize() {
	m.Finalize();
}

void MoleDemo::SoundManager::Load(std::string file) {
	m.Load("resources/molelofi.mp3");
}
void MoleDemo::SoundManager::Unload() {
	m.Unload();
}

void MoleDemo::SoundManager::Play() {
	m.Play();
}


void MoleDemo::SoundManager::Stop() {
	m.Stop();
}


void MoleDemo::SoundManager::Update() {
	m.Update();
}

permille MoleDemo::SoundManager::GetCurrentIntensity() {
	return m.GetIntensity();
}

seconds MoleDemo::SoundManager::GetMusicDuration() { 
	return m.GetDuration();
}
