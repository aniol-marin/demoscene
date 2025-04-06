export module sound;

import std;
import definitions;
import raudio;
/*
import <string>;
*/

namespace MoleDemo {

	export class SoundManager;
}

class MoleDemo::SoundManager :
	public Initializable,
	public Loadable {

public:
	void Init() {
		RAudio::InitAudio();
	}
	void Finalize() {
		RAudio::FinalizeAudio();
	}

	void Load(std::string file) {
		RAudio::LoadMusic(std::string("resources/molelofi.mp3"));
	}
	void Unload() {
		RAudio::UnloadMusic();
	}

	void Play() {
		RAudio::PlayMusic();
	}
	

	void Stop() {
		RAudio::StopMusic();
	}


	void Update() {
		RAudio::Update();
	}

	permille GetCurrentIntensity() {
		return RAudio::GetMusicIntensity();
	}
	seconds GetMusicDuration() { 
		return RAudio::GetMusicDuration();
	}
};
