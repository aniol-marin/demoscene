module;

#define SUPPORT_FILEFORMAT_MP3
#include "raudio.h"

export module raudio;


import std;
import definitions;

namespace RAudio
{
	export struct AudioManager
	{
		AudioManager() = default;
		AudioManager(const AudioManager&) = delete;
		AudioManager(AudioManager&&) = default;
		~AudioManager();

		void Init();
		void Finalize();
		void Load(std::string_view source);
		void Unload();

		void Play();
		void Stop();
		void Tick();

		seconds GetDuration();
		permille GetIntensity();
	private:
		bool initialized { false };
		bool loaded { false };
		Music music {};
		static permille intensity;

		static void SampleIntensity(void* buffer, unsigned int frames);
	};

	permille AudioManager::intensity = {};

	AudioManager::~AudioManager()
	{
		if (initialized) Finalize();
	}

	void AudioManager::SampleIntensity(void* buffer, unsigned int frames)
	{
		static std::queue<float> average {};
		float* intensities{ static_cast<float*>(buffer) };

		float accumulated{};
		for (int i = 0; i < frames; ++i)
		{
			accumulated += std::abs(intensities[i * 2 + 0]);
			accumulated += std::abs(intensities[i * 2 + 1]);
		}

		float current{ accumulated / frames };
		average.push(current);
		while (average.size() > 100)
		{
			average.pop();
		}

		float max{ current };
		for (int i = 0; i < average.size(); ++i)
		{
			max = max < average.front() ? average.front() : max;
			average.push(average.front());
			average.pop();
		}
		intensity = (permille)(max * permilleFactor);
	}

	void AudioManager::Init()
	{
		if (initialized)
		{
			std::cerr << "already initialized\n";
			throw std::exception{};
		}

		InitAudioDevice();
		SetAudioStreamBufferSizeDefault(4096);

		initialized = true;
	}

	void AudioManager::Finalize()
	{
		if (!initialized)
		{
			std::cerr << "already finalized\n";
			throw std::exception{};
		}

		StopMusicStream(music);
		CloseAudioDevice();

		initialized = false;
	}

	void AudioManager::Load(std::string_view source)
	{
		if (!initialized)
		{
			std::cerr << "load without initialization\n";
			throw std::exception{};
		}
		if (loaded)
		{
			std::cerr << "attempt at double load\n";
			throw std::exception{};
		}

		std::string s { source };
		std::cerr << "trying to load: [" << s << "]\n";
		/*
		music = LoadMusicStream(s.c_str());
		std::cerr << "load status: [" << (IsMusicReady(music) ? "OK" : "FAIL") << "]\n";
		AttachAudioStreamProcessor(music.stream, SampleIntensity);
		*/
		loaded = true;
	}

	void AudioManager::Unload()
	{
		if (!initialized)
		{
			std::cerr << "unload without initialization\n";
			throw std::exception{};
		}
		if (!loaded)
		{
			std::cerr << "attempt at double unload\n";
			throw std::exception{};
		}
		 loaded = false;

		/*
		DetachAudioStreamProcessor(music.stream, SampleIntensity);
		*/
		//UnloadMusicStream(music); // TODO fix exception while unloading
	}

	void AudioManager::Play()
	{
		if(!initialized)
		{
			std::cerr << "play without initialization\n";
			throw std::exception{};
		}

		/*
		PlayMusicStream(music);
		*/
	}

	void AudioManager::Stop()
	{
		if(!initialized)
		{
			std::cerr << "stop without initialization\n";
			throw std::exception{};
		}

		/*
		StopMusicStream(music);
		*/
	}

	void AudioManager::Tick()
	{
		if(!initialized)
		{
			std::cerr << "tick without initialization\n";
			throw std::exception{};
		}

		/*
		UpdateMusicStream(music);
		*/
	}

	seconds  AudioManager::GetDuration()
	{
		return (seconds)GetMusicTimeLength(music);
	}

	permille  AudioManager::GetIntensity()
	{
		return (permille)intensity;
	}
}
