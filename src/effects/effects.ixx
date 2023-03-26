export module effects;

import definitions;
import timer;
import <vector>;
import <functional>;

namespace MoleDemo {

	export class Effect {
		std::vector<uint32_t> buffer;
	protected:
		const Timer* const timer;
		Screen* const screen;
		Effect(Timer* timer, Screen* screen) :
			timer{ timer },
			screen{ screen },
			buffer{} {}
		size_t GetPixelIndex(Point2D& point) {
			return (size_t)screen->w * (size_t)point.y + (size_t)point.x;
		}
		void PutPixel(Point2D point, uint32_t color) {
			size_t index = GetPixelIndex(point);
			if (index > buffer.size()) {
				int d = 0;
			}
			auto& position = buffer.at(GetPixelIndex(point));
			position = color;
		}
		void ReserveBuffer(size_t size) {
			ClearBuffer(0x0);
			//buffer.reserve(size);
		}
		void ClearBuffer(uint32_t color) {
			buffer.assign((size_t)screen->w * (size_t)screen->h, color);
		}

	public:
		virtual ~Effect() {};
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Update(uint_fast16_t intensity) = 0;
		virtual void Cache(std::vector<bool>& mask) = 0;
		uint32_t GetPixel(Point2D p) {
			return buffer[p.y];
		};
		std::vector<uint32_t>& GetBuffer() { return buffer; }
	};

	class Star {
		Screen* const screen;
		Point2D position;
		uint8_t speed;
		uint16_t miliBrightness;
		Color color;
		Color transparent;
		void Reset(const Screen& screen, const uint8_t maxSpeed, const bool initial) {
			position.x = initial * (rand() % screen.w);
			position.y = rand() % screen.h;
			speed = rand() % maxSpeed;
			miliBrightness = 1000 * speed / maxSpeed;
			color.SetRGBA(
				0xFF - (rand() % 0x3A),
				0xFF - (rand() % 0x5F),
				0xFF - (rand() % 0x2C),
				0xFF);
			transparent.SetRGBA(
				color.r(),
				color.g(),
				color.b(),
				0x0);
		}

	public:
		Star(Screen* screenSize, const int maxSpeed) :
			screen{ screenSize } {
			Reset(*screenSize, maxSpeed, true);
		}
		void Update(const Screen& screen, uint16_t deltaTime, const int maxSpeed) {
			position.x += 1 + speed * deltaTime * maxSpeed / 100; // position shift must be at least 1 in order to avoid stalling for very low delta times at very slow speeds
			if (position.x >= screen.w) {
				Reset(screen, maxSpeed, false);
			}
		}

		void Draw(std::function<void(Point2D pixel, uint32_t color)> putPixel) {

			int trail{ miliBrightness };
			uint8_t nextOffset{ 0 };
			while (trail > 0) {

				if (position.x - nextOffset >= 0) {
					putPixel(Point2D{ (uint16_t)(position.x - nextOffset), position.y },  color.mLerp(transparent, trail));
				}

				trail -= 20;
				nextOffset++;
			}
		}
	};

	export class Stars : public Effect {
		const int maxSpeed = 10;
		std::vector<Star> stars;
	public:
		Stars(Timer* timer, Screen* screen) :
			Effect{ timer, screen }
		{
			ClearBuffer(0x0);
		}
		void Load() override {
			int maxStars = 100;
			int maxSpeed = 10;
			srand(0);
			for (int i = 0; i < maxStars; i++) {
				Star star{ screen, maxSpeed };
				stars.push_back(star);
			}
		}
		void Unload()  override {}
		void Update(uint_fast16_t intensity)  override {

			uint16_t time = timer->GetDeltaTime();
			for (Star& star : stars) {
				star.Update(*screen, time, 1 + maxSpeed * intensity / 100);
			}
		}
		void Cache(std::vector<bool>& mask)  override {
			ClearBuffer(0x0);
			for (Star& star : stars) {
				star.Draw([&](Point2D point, uint32_t color) { PutPixel(point, color); });
			}
		}
	};

	export class Plasma : public Effect {
		long long accumulatedTime{};
		std::vector<uint8_t> plasma1;
		std::vector<uint8_t> plasma2;
		int Windowx1, Windowy1, Windowx2, Windowy2;
		long src1, src2;
		Color palette[256];

		void buildPalette(uint16_t time) {
			for (int i = 0; i < 256; i++)
			{
				palette[i].SetRGBA(
					(unsigned char)(128 + 127 * cos(i * PI / 128 + (double)time / 740)),
					(unsigned char)(128 + 127 * sin(i * PI / 128 + (double)time / 630)),
					(unsigned char)(128 - 127 * cos(i * PI / 128 + (double)time / 810))
				);
			}

		}

	public:
		Plasma(Timer* timer, Screen* screen) :
			Effect{ timer, screen }
		{
			ReserveBuffer(screen->w * screen->h);
		}

		void Load() override {
			buildPalette(0);
			for (int j = 0; j < screen->h * 2; ++j) {
				for (int i = 0; i < screen->w * 2; ++i) {
					plasma1.push_back(64 + 63 * (sin((double)hypot(screen->h - j, screen->w - i) / 16)));
					plasma2.push_back((unsigned char)(64 + 63 * sin((float)i / (37 + 15 * cos((float)j / 74)))
						* cos((float)j / (31 + 11 * sin((float)i / 57)))));
				}
			}
		}
		void Unload()  override {}
		void Update(uint_fast16_t intensity)  override {

			accumulatedTime += intensity;
			// setup some nice colours, different every frame
			// this is a palette that wraps around itself, with different period sine
			// functions to prevent monotonous colours
			buildPalette(intensity);

			// move plasma with more sine functions :)
			Windowx1 = (screen->w / 2) + (int)(((screen->w / 2) - 1) * cos((double)accumulatedTime / 970));
			Windowx2 = (screen->w / 2) + (int)(((screen->w / 2) - 1) * sin((double)-accumulatedTime / 1140));
			Windowy1 = (screen->h / 2) + (int)(((screen->h / 2) - 1) * sin((double)accumulatedTime / 1230));
			Windowy2 = (screen->h / 2) + (int)(((screen->h / 2) - 1) * cos((double)-accumulatedTime / 750));
			// we only select the part of the precalculated buffer that we need
			src1 = Windowy1 * (screen->w * 2) + Windowx1;
			src2 = Windowy2 * (screen->w * 2) + Windowx2;

		}
		void Cache(std::vector<bool>& mask)  override {
			int indexColor;
			for (uint16_t y = 0; y < screen->h; y++) {
				for (uint16_t x = 0; x < screen->w; x++) {

					indexColor = (plasma1[src1] + plasma2[src2]) % 256;
					PutPixel(Point2D{ x, y }, palette[indexColor].rgba());

					src1++; src2++;
				}
				// get the next line in the precalculated buffers
				src1 += screen->w; src2 += screen->w;
			}
		}
	};
}
