export module timeline;

import definitions;
import effects;
import sdl;
import <iostream>;
import <vector>;
import <cstdlib>;
import <bitset>;
import <thread>;
import <chrono>;
#include <ratio>

namespace MoleDemo {

	export class Timeline {

	public:
		int hi;
	};
}



export namespace Temp {

	using namespace MoleDemo;

	using Pixel = Uint32;

	using Clock = std::chrono::steady_clock;
	using Time = Clock::time_point;
	using ms = std::chrono::milliseconds;
	Uint16 delay(Time since, Time until) {
		return (until - since).count() / 1000000; //TODO cast properly to milliseconds
	}



	class Star {
		Point2D position;
		Uint8 speed;
		Uint16 miliBrightness;
		Color color;
		void Reset(const Screen& screen, const Uint8 maxSpeed, const bool initial) {
			position.x = initial * (rand() % screen.w);
			position.y = rand() % screen.h;
			speed = rand() % maxSpeed;
			miliBrightness = 1000 * speed / maxSpeed;
			color.r = 0xFF - (rand() % 0x3A);
			color.g = 0xFF - (rand() % 0x5F);
			color.b = 0xFF - (rand() % 0x2C);
			color.a = 0xFF;
		}
	public:
		Star() : Star{ Screen{640,480}, 10 } {} //TODO bind to factory
		Star(const Screen& screenSize, const int maxSpeed) {
			Reset(screenSize, maxSpeed, true);
		}
		void Update(const Screen& screen, Uint8 deltaTime, const int maxSpeed) {
			position.x += 1 + speed * deltaTime / 1000; // position shift must be at least 1 in order to avoid stalling for very low delta times at very slow speeds
			if (position.x >= screen.w) {
				Reset(screen, maxSpeed, false);
			}
		}

		void Draw() {

			int trail{ miliBrightness };
			Uint8 nextOffset{ 0 };
			while (trail > 0) {

				if (position.x - nextOffset >= 0) {
					putPixel(position.x - nextOffset, position.y, color.mLerp(trail));
				}

				trail -= 20;
				nextOffset++;
			}
		}
	};

	class Plasma {
		long long accumulatedTime{};
		std::vector<Uint8> plasma1;
		std::vector<Uint8> plasma2;
		int Windowx1, Windowy1, Windowx2, Windowy2;
		long src1, src2;
		Color palette[256];

		void buildPalette(Uint16 deltaTime) {
			for (int i = 0; i < 256; i++)
			{
				palette[i].r = (unsigned char)(128 + 127 * cos(i * PI / 128 + (double)deltaTime / 740));
				palette[i].g = (unsigned char)(128 + 127 * sin(i * PI / 128 + (double)deltaTime / 630));
				palette[i].b = (unsigned char)(128 - 127 * cos(i * PI / 128 + (double)deltaTime / 810));
			}

		}

	public:
		void Init(const Screen& screen, Uint16 currentTime) {
			buildPalette(currentTime);
			for (int j = 0; j < screen.h * 2; ++j) {
				for (int i = 0; i < screen.w * 2; ++i) {
					plasma1.push_back(64 + 63 * (sin((double)hypot(screen.h - j, screen.w - i) / 16)));
					plasma2.push_back((unsigned char)(64 + 63 * sin((float)i / (37 + 15 * cos((float)j / 74)))
						* cos((float)j / (31 + 11 * sin((float)i / 57)))));
				}
			}
		}

		void updatePlasma(const Screen& screen, Uint16 currentTime) {
			accumulatedTime += currentTime;
			// setup some nice colours, different every frame
			// this is a palette that wraps around itself, with different period sine
			// functions to prevent monotonous colours
			buildPalette(currentTime);

			// move plasma with more sine functions :)
			Windowx1 = (screen.w / 2) + (int)(((screen.w / 2) - 1) * cos((double)accumulatedTime / 970));
			Windowx2 = (screen.w / 2) + (int)(((screen.w / 2) - 1) * sin((double)-accumulatedTime / 1140));
			Windowy1 = (screen.h / 2) + (int)(((screen.h / 2) - 1) * sin((double)accumulatedTime / 1230));
			Windowy2 = (screen.h / 2) + (int)(((screen.h / 2) - 1) * cos((double)-accumulatedTime / 750));
			// we only select the part of the precalculated buffer that we need
			src1 = Windowy1 * (screen.w * 2) + Windowx1;
			src2 = Windowy2 * (screen.w * 2) + Windowx2;
		}

		void renderPlasma(Screen screen) {

			Uint32* pixel;
			int indexColor;
			for (Uint16 j = 0; j < screen.h; j++) {
				for (Uint16 i = 0; i < screen.w; i++) {

					indexColor = (plasma1[src1] + plasma2[src2]) % 256;
					putPixel(i, j, palette[indexColor].rgba());

					src1++; src2++;
				}
				// get the next line in the precalculated buffers
				src1 += screen.w; src2 += screen.w;
			}

		}
	};

	struct Data {
		const Screen screen;
		const Uint8 maxSpeed;
		const Uint8 maxStars;
		std::vector<Star> stars;
		Plasma plasma;
		ProgramStatus status;
		Data(Point2D screenSize, Uint8 speed, Uint8 stars, Uint8 fps) :
			screen{ screenSize.x, screenSize.y },
			maxSpeed{ speed },
			maxStars{ stars },
			fps{ fps },
			initialTime{ Clock::now() },
			previousTime{ Clock::now() }
		{}
		Uint16 GetDeltaTime() const { return deltaTime; }
		ms GetNextDelayTime() { return  std::chrono::milliseconds{ std::chrono::duration_cast<ms>(std::chrono::seconds(1 / fps)) }; }
		bool Running() const { return status == ProgramStatus::RUNNING; }
		void SetNextFrameTime() {
			deltaTime = delay(previousTime, Clock::now());
			previousTime = Clock::now();
		}
	private:
		Uint16 deltaTime;
		int fps;
		Time initialTime;
		Time previousTime;
	};

	void Init(Data& data);
	void Finalize(Data& data);
	void PollEvents(Data& data);
	void Update(Data& data);
	void Draw(Data& data);
	void Synch(Data& data);



	void Init(Data& data) {

		const bool initialized = MoleDemo::InitSDL();
		if (initialized) {

			srand(0);

			data.plasma.Init(data.screen, data.GetDeltaTime());

			for (int i = 0; i < data.maxStars; i++) {
				Star star{ data.screen, data.maxSpeed };
				data.stars.push_back(star);
			}

			data.status = ProgramStatus::RUNNING;
		}
		else {
			data.status = ProgramStatus::TERMINATE_ERROR;
		}
	}

	void Finalize(Data& data) {

		if (data.status == ProgramStatus::TERMINATE_OK) {
			MoleDemo::FinalizeSDL();
		}
	}

	void PollEvents(Data& data) {
		data.status = MoleDemo::PollSDLEvents();
	}

	void Update(Data& data) {

		for (Star& star : data.stars) {
			star.Update(data.screen, data.GetDeltaTime(), data.maxSpeed);
		}
		data.plasma.updatePlasma(data.screen, data.GetDeltaTime());
	}

	void Draw(Data& data) {

		MoleDemo::LockSurface();

		data.plasma.renderPlasma(data.screen);
		for (Star& star : data.stars) {
			star.Draw();
		}

		MoleDemo::UnlockSurface();
		MoleDemo::UpdateSurface();
	}

	void Synch(Data& data) {
		std::this_thread::sleep_for(data.GetNextDelayTime());
		data.SetNextFrameTime();
	}
}