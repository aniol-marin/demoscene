export module effects;

namespace Effects {

	export class Effect {
	public:
		virtual void Load() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

	};
}
