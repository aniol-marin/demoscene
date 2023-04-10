module effects;

namespace MoleDemo {

	Solid::Solid(Timer* timer, Screen* screen) :
		Effect{ timer, screen } {}

	Solid::~Solid() {
	}

	void Solid::Load() {
		ClearBuffer(color.rgba());
	}

	void Solid::Unload() {
	}

	void Solid::Update(permille intensity, milliseconds delta) {
	}

	void Solid::Cache(StencilBuffer& mask) {
	}

	void Solid::SetColor(Color color) {
		this->color = color;
	}
}