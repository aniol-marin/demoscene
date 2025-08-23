module;

#include "raudio.h"

export module raudio;

import std;
import definitions;

namespace RAudio
{
	export struct AudioManager;
}

namespace RAudio
{
	struct AudioManager
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
		void Update();

		seconds GetDuration();
		permille GetIntensity();

	private:
		bool initialized { false };
		bool loaded { false };
		Music music {};
		static permille intensity;

		static void SampleIntensity(void* buffer, unsigned int frames);
	};
}

