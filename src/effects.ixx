export module effects;

import definitions;
import timer;
import <vector>;
import <functional>;

namespace MoleDemo {

	export using PixelBuffer = std::vector<uint32_t>;

	export class Effect;
	export class Fire;
	export class Plasma;
	export class Stars;

	class Star;
}

class MoleDemo::Effect {

	PixelBuffer buffer;

protected:
	const Timer* const timer;
	Screen* const screen;

	Effect(Timer* timer, Screen* screen);

	uint_fast16_t GetPixelIndex(Point2D& point);
	uint_fast16_t GetPixelIndex(Point2D& point, PixelBuffer& pixelBuffer);
	void PutPixel(Point2D point, uint32_t color);

	void ReserveBuffer(size_t size);
	void ClearBuffer(uint32_t color);
	void ClearBuffer(uint32_t color, PixelBuffer& pixelBuffer);

public:

	virtual ~Effect();

	uint32_t GetPixel(Point2D p);
	PixelBuffer& GetBuffer();

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void Update(uint_fast16_t intensity) = 0;

	virtual void Cache(std::vector<bool>& mask) = 0;
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
	void Update(uint_fast16_t intensity) override;
	void Cache(std::vector<bool>& mask)  override;
};

class MoleDemo::Plasma : public Effect {
	long long accumulatedTime{};
	std::vector<uint8_t> plasma1;
	std::vector<uint8_t> plasma2;
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
	void Cache(std::vector<bool>& mask)  override;
};

class MoleDemo::Stars : public Effect {
	const int maxSpeed = 10;
	std::vector<Star> stars;
public:
	Stars(Timer* timer, Screen* screen);
	~Stars();

	void Load() override;
	void Unload()  override;

	void Update(uint_fast16_t intensity) override;
	void Cache(std::vector<bool>& mask) override;
};

class MoleDemo::Star {

	Screen* const screen;
	Point2D position;
	uint8_t speed;
	uint16_t miliBrightness;
	Color color;
	Color transparent;

	void Reset(const Screen& screen, const uint8_t maxSpeed, const bool initial);

public:

	Star(Screen* screenSize, const int maxSpeed);
	~Star();

	void Update(const Screen& screen, uint16_t deltaTime, const int maxSpeed);
	void Draw(std::function<void(Point2D pixel, uint32_t color)> putPixel);
};