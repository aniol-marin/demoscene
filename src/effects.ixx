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
	void PutPixel(Point2D point, rgbaColor color);

	void ReserveBuffer();
	void ClearBuffer(rgbaColor color);
	void ClearBuffer(rgbaColor color, PixelBuffer& pixelBuffer);

public:

	virtual ~Effect();

	rgbaColor GetPixel(Point2D p);
	rgbaColor GetPixel(index index);
	PixelBuffer& GetBuffer();

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void Update(permille intensity) = 0;

	virtual void Cache(StencilBuffer& mask) = 0;
};

class MoleDemo::Fire : public Effect {

	PixelBuffer first;
	PixelBuffer second;

	void GeneratePalette();
	void GenerateHotspots();
	void FilterPrevious();

public:
	Fire(Timer* timer, Screen* screen);
	~Fire();

	void Load() override;
	void Unload() override;
	void Update(permille intensity) override;
	void Cache(StencilBuffer& mask)  override;
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
	void Update(uint_fast16_t intensity) override;
	void Cache(StencilBuffer& mask)  override;
};

class MoleDemo::Solid : public Effect {
	Color color;
public:
	Solid(Timer* timer, Screen* screen);
	~Solid();

	void SetColor(Color color);

	void Load() override;
	void Unload() override;
	void Update(permille intensity) override;
	void Cache(StencilBuffer& mask)  override;
};

class MoleDemo::Gradient : public Effect {
	Color NE, NW, SW, SE;
public:
	Gradient(Timer* timer, Screen* screen);
	~Gradient();

	void SetColors(Color NE, Color NW, Color SW, Color SE);

	void Load() override;
	void Unload() override;
	void Update(permille intensity) override;
	void Cache(StencilBuffer& mask)  override;
};

class MoleDemo::Stars : public Effect {
	const int maxSpeed = 10;
	std::vector<Star> stars;
public:
	Stars(Timer* timer, Screen* screen);
	~Stars();

	void Load() override;
	void Unload()  override;

	void Update(permille intensity) override;
	void Cache(StencilBuffer& mask) override;
};

class MoleDemo::Star {

	Screen* const screen;
	const speed maxSpeed;
	Point2D position;
	speed speed;
	permille brightness;
	Color color;
	Color transparent;

	void Reset(const Screen& screen, const uint_fast16_t& maxSpeed, const bool initial);

public:

	Star(Screen* screenSize, const uint_fast16_t& maxSpeed);
	Star(const Star& star);
	~Star();

	void Update(const Screen& screen, milliseconds deltaTime, const int maxSpeed);
	void Draw(std::function<void(Point2D pixel, rgbaColor color)> putPixel);
};