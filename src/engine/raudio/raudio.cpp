module;

#include "raudio.h"

export module raudio;


import std;
import definitions;

namespace RAudio {

	export struct AudioManager;

	export void InitAudio();
	export void FinalizeAudio();

	export void LoadMusic(std::string_view source);
	export void UnloadMusic();

	export void PlayMusic();
	export void StopMusic();
	export void Update();

	export seconds GetMusicDuration();
	export permille GetMusicIntensity();

	Music music;
	permille intensity;
	std::queue<float> average;

	void SampleIntensity(void* buffer, unsigned int frames) {

		float* intensities{ static_cast<float*>(buffer) };

		float accumulated{};
		for (int i = 0; i < frames; ++i) {
			accumulated += std::abs(intensities[i * 2 + 0]);
			accumulated += std::abs(intensities[i * 2 + 1]);
		}

		float current{ accumulated / frames };
		average.push(current);
		while (average.size() > 100) {
			average.pop();
		}

		float max{ current };
		for (int i = 0; i < average.size(); ++i) {
			max = max < average.front() ? average.front() : max;
			average.push(average.front());
			average.pop();
		}
		intensity = (permille)(max * permilleFactor);
	}
}

struct RAudio::AudioManager
{
	AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = default;
	~AudioManager() { if (initialized) Finalize(); }

	void Init()
	{
		if (initialized)
		{
			throw std::exception{};
		}

		InitAudio();
		initialized = true;
	}
	void Finalize()
	{
		if (!initialized)
		{
			throw std::exception{};
		}

		FinalizeAudio();
		initialized = false;
	}
	void Load(std::string_view source) { LoadMusic(source); }
	void Unload() { UnloadMusic();}

	void Play() { PlayMusic(); }
	void Stop() { StopMusic(); }
	void Tick() { Update(); }

	seconds GetDuration() { return GetMusicDuration(); }
	permille GetIntensity() { return GetMusicIntensity(); }
private:
	bool initialized { false };
};

void RAudio::InitAudio() {
	InitAudioDevice();
	SetAudioStreamBufferSizeDefault(4096);
}

void RAudio::FinalizeAudio() {
	StopMusicStream(music);
}

void RAudio::LoadMusic(std::string_view source) {
	std::string s { source };
	music = LoadMusicStream(s.c_str());
	AttachAudioStreamProcessor(music.stream, SampleIntensity);
}

void RAudio::UnloadMusic() {
	DetachAudioStreamProcessor(music.stream, SampleIntensity);
	//UnloadMusicStream(music); // TODO fix exception while unloading
}

void RAudio::PlayMusic() {
	PlayMusicStream(music);
}

void RAudio::StopMusic() {
	StopMusicStream(music);
}

void RAudio::Update() {
	UpdateMusicStream(music);
}

export seconds  RAudio::GetMusicDuration() {
	return (seconds)GetMusicTimeLength(music);
}

export permille  RAudio::GetMusicIntensity() {
	return (permille)intensity;
}
