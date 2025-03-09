module;

#include <functional>
#include <memory>
#include <cstddef>

export module effects;

import definitions;
import timer;
/*
import <functional>;
import <memory>;
*/

namespace MoleDemo {

	/*
	export class Effect;
	// regular effects
	export class Stars;
	export class Fire;
	// customizables
	export class Plasma;
	export class Tunel;
	// texturizables
	export class Solid;
	export class Gradient;
	export class Wheel;
	export class ChessBoard;
	export class RandomNoise;

	class Star;
	*/
}

/*
class MoleDemo::Effect {

	PixelBuffer buffer;

protected:
	Timer* const timer;
	Screen* const screen;

	Effect(Timer* timer, Screen* screen);

	index GetPixelIndex(Point2D& point);
	index GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer);
	rgbaColor GetColorAt(Point2D point, PixelBuffer& pixelBuffer);
	void PutPixel(Point2D point, rgbaColor color);
	void PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer);

	void ReserveBuffer();
	void ClearBuffer(rgbaColor color);
	void ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer);

public:

	virtual ~Effect();

	virtual rgbaColor GetPixel(Point2D p);
	virtual rgbaColor GetPixel(index index);

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void Update(permille intensity, milliseconds delta) = 0;

	virtual void Cache(StencilBuffer& mask) = 0;
};

namespace MoleDemo {
	Effect::Effect(Timer* timer, Screen* screen) :
		timer{ timer },
		screen{ screen },
		buffer{} {

		ReserveBuffer();
	}

	Effect::~Effect() {};

	index Effect::GetPixelIndex(Point2D& point) {
		return GetPixelIndex(point, buffer);
	}

	index Effect::GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer) {
		return (size_t)screen->w * (size_t)point.y + (size_t)point.x;
	}

	rgbaColor Effect::GetColorAt(Point2D point, PixelBuffer& pixelBuffer) {
		return pixelBuffer[GetPixelIndex(point, pixelBuffer)];
	}

	void Effect::PutPixel(Point2D point, rgbaColor color) {
		PutPixel(point, color, buffer);
	}

	void Effect::PutPixel(Point2D point, rgbaColor color, PixelBuffer& buffer) {

		rgbaColor& pixel = buffer.at(GetPixelIndex(point));
		pixel = color;
	}

	void Effect::ReserveBuffer() {
		buffer.reserve(screen->GetPixelCount());
		ClearBuffer(transparent);
	}

	void Effect::ClearBuffer(rgbaColor color) {
		ClearBuffer(color, buffer);
	}

	void Effect::ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer) {
		pixelBuffer.assign(size_t{ screen->GetPixelCount() }, color);
	}

	rgbaColor Effect::GetPixel(Point2D p) {
		return GetPixel(GetPixelIndex(p));
	}

	rgbaColor Effect::GetPixel(index index) {
		return buffer[index];
	}
}
class MoleDemo::Fire : public Effect {

	PixelBuffer firstBuffer;
	PixelBuffer secondBuffer;
	std::vector<Color> palette;

	void GeneratePalette();
	void GenerateHotspots(PixelBuffer& buffer, permille intensity);
	void FilterPrevious(PixelBuffer& src, PixelBuffer& dest, milliseconds delta, permille intensity);

public:
	Fire(Timer* timer, Screen* screen);
	~Fire();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetPixel(Point2D p) override;
	rgbaColor GetPixel(index index) override;
};

class MoleDemo::Plasma :
	public Customizable,
	public Effect {
	long long accumulatedTime{};
	std::vector<channel> plasma1;
	std::vector<channel> plasma2;
	int Windowx1, Windowy1, Windowx2, Windowy2;
	long src1, src2;
	Color palette[256];

	void buildPalette(uint16_t time);

public:
	Plasma(Timer* timer, Screen* screen);
	~Plasma();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	constexpr Id TextureLimit() const override { return 2; }
	void AssignTexture(std::unique_ptr<Texturable> texture, Id id) override;
};

class MoleDemo::Tunel :
	public Customizable,
	public Effect {
	long long accumulatedTime{};
	std::vector<channel> Tunel1;
	std::vector<Point2D> uv;
	int Windowx1, Windowy1, Windowx2, Windowy2;
	long src1, src2;
	Color palette[256];
	std::unique_ptr<Texturable> texture;

	permille du, dv, speedU, speedV;

	void buildPalette(uint16_t time);

public:
	Tunel(Timer* timer, Screen* screen);
	~Tunel();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	constexpr Id TextureLimit() const override { return 1; }
	void AssignTexture(std::unique_ptr<Texturable> texture, Id id) override;
};

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

class MoleDemo::Gradient :
	public Texturable,
	public Effect {
	Color NE, NW, SW, SE;
public:
	Gradient();
	Gradient(Timer* timer, Screen* screen);
	~Gradient();

	void SetColors(Color NE, Color NW, Color SW, Color SE);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetMappedUV(CoordinateUV uv) override;
};

class MoleDemo::ChessBoard :
	public Texturable,
	public Effect {
	Color A, B;
	bunch repetitions;

public:
	ChessBoard();
	ChessBoard(Timer* timer, Screen* screen);
	~ChessBoard();

	void Set(Color A, Color B, bunch repetitions);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetMappedUV(CoordinateUV uv) override;
};

class MoleDemo::RandomNoise :
	public Texturable,
	public Effect {
	ChannelBuffer noise;
	Color A, B;
	bunch repetitions;

public:
	RandomNoise();
	RandomNoise(Timer* timer, Screen* screen);
	~RandomNoise();

	void Set(Color a, Color b, bunch repetitions);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetMappedUV(CoordinateUV uv) override;
};

class MoleDemo::Wheel : public Effect {
	Color color;
	Color base;
	Color top;
	rgbaColor rgbColor;
	double rotation;
	void SetColor();

public:
	Wheel(Timer* timer, Screen* screen);
	~Wheel();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetPixel(Point2D p) override;
	rgbaColor GetPixel(index index) override;
};

class MoleDemo::Stars : public Effect {
	const int maxStars = 100;
	const int newStarsPerFrame = 2;
	const speed maxSpeed = 100;
	std::vector<Star> stars;
public:
	Stars(Timer* timer, Screen* screen);
	~Stars();

	void Load() override;
	void Unload()  override;

	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask) override;
};

class MoleDemo::Star {

	const Screen& screen;
	const speed& maxSpeed;
	Color empty{ transparent };
	Color dessaturated{ white };
	Color color;
	Point2D position;
	int progress;
	permille brightness;
	speed currentSpeed;
	speed baseSpeed;
	Color currentColor;

	void Reset();

public:

	Star(const Screen& screen, const speed& maxSpeed);
	~Star();

	void Update(permille intensity, milliseconds delta);
	void Draw(std::function<void(Point2D pixel, rgbaColor color)> putPixel);
};
*/

