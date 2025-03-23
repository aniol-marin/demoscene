module;

#include <cstdint>
#include <iostream>
#include <functional>

export module solid;

import definitions;
import timer;
import effect;

namespace MoleDemo {
	export class Solid;
}

class MoleDemo::Solid :
	public Texturable,
	public Effect {
	rgbaColor rgbColor;
public:
	Solid(); // texturable-enfoced constructor
	Solid(Timer* timer, Screen* screen);
	~Solid();

	void SetColor(Color color);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetPixel(Point2D p) override;
	rgbaColor GetPixel(index index) override;
	rgbaColor GetMappedUV(CoordinateUV uv) override;
};

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

	rgbaColor Solid::GetMappedUV(CoordinateUV uv) {
		return rgbColor;
	}
}