export module sound;

import interfaces;
import <string>;

namespace MoleDemo {
	export class SoundManager :
		public Initializable,
		public Loadable {

	public:
		void Init() {}
		void Load(std::string file) {}
		void Play() {}
		void Update() {}
		void Unload() {}
		void Finalize() {}
		uint_fast16_t GetCurrentIntensity() { return 100; } // TODO send volume intensity
		uint_fast16_t GetMusicDuration() { return 30; } // TODO measure main track duration

	};
}