export module sound;

import definitions;
import interfaces;
import <string>;

namespace MoleDemo {

	export class SoundManager;
}

class MoleDemo::SoundManager :
	public Initializable,
	public Loadable {

public:
	void Init() {}
	void Load(std::string file) {}
	void Play() {}
	void Update() {}
	void Unload() {}
	void Finalize() {}
	permille GetCurrentIntensity() { return 100; } // TODO send volume intensity
	seconds GetMusicDuration() { return 30; } // TODO measure main track duration

};
