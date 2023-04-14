module effects;

namespace MoleDemo {

	Solid::Solid() :
		Solid{ nullptr, &textureSize } {}

	Solid::Solid(Timer* timer, Screen* screen) :
		Texturable{},
		Effect{ timer, screen } {}

	Solid::~Solid() {
	}

	void Solid::Load() {
	}

	void Solid::Unload() {
	}

	void Solid::Update(permille intensity, milliseconds delta) {
	}

	void Solid::Cache(StencilBuffer& mask) {
	}

	void Solid::SetColor(Color color) {
		rgbColor = color.rgba();
	}

	rgbaColor Solid::GetPixel(Point2D p) {
		return rgbColor;
	}

	rgbaColor Solid::GetPixel(index index) {
		return rgbColor;
	}


	const Screen& Solid::GetDimensions() {
		return *screen;
	}
}