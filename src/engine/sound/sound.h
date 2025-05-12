#ifndef MOLE_SOUND
#define MOLE_SOUND

#include <string>

#include "definitions.h"
#include "raudio_wrapper.h"

namespace MoleDemo
{
	class SoundManager;
}

using namespace mole_def;

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

#endif//!MOLE_SOUND

