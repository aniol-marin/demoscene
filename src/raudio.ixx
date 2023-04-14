module;

export module raudio;

import definitions;
import <string>;
import <cstdint>;
import <queue>;

#define RAUDIO_STANDALONE
#define SUPPORT_MODULE_RAUDIO
#define SUPPORT_FILEFORMAT_MP3
extern "C" {
#include "external/raudio/src/raudio.h"
}

namespace RAudio {

	export void InitAudio();
	export void FinalizeAudio();

	export void LoadMusic(std::string source);
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

void RAudio::InitAudio() {
	InitAudioDevice();
	SetAudioStreamBufferSizeDefault(4096);
}

void RAudio::FinalizeAudio() {
	StopMusicStream(music);
}

void RAudio::LoadMusic(std::string source) {
	music = LoadMusicStream(source.c_str());
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