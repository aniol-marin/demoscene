export module effects;

import definitions;
import timer;
import <functional>;

namespace MoleDemo {

	export class Effect;
	export class Fire;
	export class Plasma;
	export class Solid;
	export class Gradient;
	export class Wheel;
	export class Stars;

	class Star;
}

class MoleDemo::Effect {

	PixelBuffer buffer;

protected:
	const Timer* const timer;
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

class MoleDemo::Plasma : public Effect {
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
};

class MoleDemo::Solid : public Effect {
	rgbaColor rgbColor;
public:
	Solid(Timer* timer, Screen* screen);
	~Solid();

	void SetColor(Color color);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetPixel(Point2D p) override;
	rgbaColor GetPixel(index index) override;
};

class MoleDemo::Gradient : public Effect {
	Color NE, NW, SW, SE;
public:
	Gradient(Timer* timer, Screen* screen);
	~Gradient();

	void SetColors(Color NE, Color NW, Color SW, Color SE);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
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

	void Update(milliseconds deltaTime, permille intensity);
	void Draw(std::function<void(Point2D pixel, rgbaColor color)> putPixel);
};