#include <SDL.h>

export module demo;

import <iostream>;
import <vector>;
import <cstdlib>;
import <bitset>;
import <thread>;
import <chrono>;

enum class ProgramStatus {
	TERMINATE_OK,
	TERMINATE_ERROR,
	RUNNING,
};

using Window = SDL_Window;
using Surface = SDL_Surface;
using Pixel = Uint32;
using Event = SDL_Event;
using Clock = std::chrono::steady_clock;
using Time = Clock::time_point;
using ms = std::chrono::milliseconds;
Time Now() { return Clock::now(); }
Uint16 delay(Time since, Time until) {
	return (until - since).count() / 1000000; //TODO cast properly to milliseconds
	//return std::chrono::duration<Uint16, ms>(until - since).count();
}



struct Point2D {
	Uint16 x, y;
};

struct Screen {
	const Uint16 w, h;
	Screen(Uint16 width, Uint16 heigth) :
		w{ width },
		h{ heigth } {}
};

struct Color {
	Uint8 r, g, b, a;
	Uint32 rgba() const { return to32(a, r, g, b); }
	Uint32 mLerp(Uint16 milliUnits) {
		return to32(
			a * milliUnits / 1000,
			r * milliUnits / 1000,
			g * milliUnits / 1000,
			b * milliUnits / 1000
		);
	};
private:
	const Uint32 to32(Uint8 a, Uint8 r, Uint8 g, Uint8 b) const {
		return b |
			(g << 8) |
			(r << 16) |
			(a << 24);
	}
};

Pixel* getPixel(SDL_Surface* surface, Uint16 x, Uint16 y) {
	return reinterpret_cast<Uint32*>((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
}
void putPixel(Pixel& pixel, const Color& color) {
	pixel = color.rgba();
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
	Star(const Screen& screenSize, const int maxSpeed) {
		Reset(screenSize, maxSpeed, true);
	}
	void Update(const Screen& screen, Uint8 deltaTime, const int maxSpeed) {
		position.x += 1 + speed * deltaTime / 1000; // position shift must be at least 1 in order to avoid stalling for very low delta times at very slow speeds
		if (position.x >= screen.w) {
			Reset(screen, maxSpeed, false);
		}
	}

	void Draw(SDL_Surface* screenSurface) {

		int trail{ miliBrightness };
		Uint8 nextOffset{ 0 };
		while (trail > 0) {

			if (position.x - nextOffset >= 0) {
				Uint32* pixel = getPixel(screenSurface, position.x - nextOffset, position.y);
				*pixel = color.mLerp(trail);
				//putPixel(*pixel, color.mLerp(trail));
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
			palette[i].r = (unsigned char)(128 + 127 * cos(i * M_PI / 128 + (double)deltaTime / 740));
			palette[i].g = (unsigned char)(128 + 127 * sin(i * M_PI / 128 + (double)deltaTime / 630));
			palette[i].b = (unsigned char)(128 - 127 * cos(i * M_PI / 128 + (double)deltaTime / 810));
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

	void renderPlasma(Surface& surface, Screen screen) {

		Uint32* pixel;
		int indexColor;
		for (Uint16 j = 0; j < screen.h; j++) {
			for (Uint16 i = 0; i < screen.w; i++) {

				pixel = getPixel(&surface, i, j);
				indexColor = (plasma1[src1] + plasma2[src2]) % 256;
				putPixel(*pixel, palette[indexColor]);

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
	Window* window;
	Surface* surface;
	Event e;
	Data(Point2D screenSize, Uint8 speed, Uint8 stars, Uint8 fps) :
		screen{ screenSize.x, screenSize.y },
		maxSpeed{ speed },
		maxStars{ stars },
		fps{ fps },
		initialTime{ Now() },
		previousTime{ Now() }
	{}
	Uint16 GetDeltaTime() const { return deltaTime; }
	ms GetNextDelayTime() { return  std::chrono::milliseconds{ 1000 / fps }; }//std::chrono::duration_cast<ms>(previousTime - Now()) + frameTime; }
	bool Running() const { return status == ProgramStatus::RUNNING; }
	void SetNextFrameTime() {
		deltaTime = delay(previousTime, Now());
		previousTime = Now();
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

int main(int argc, char* args[])
{
	Data data{ Point2D{640, 480},100, 100, 24 };
	Init(data);

	while (data.Running()) {
		PollEvents(data);
		Update(data);
		Draw(data);
		Synch(data);
	}
	Finalize(data);

	return 0;
}

void Init(Data& data) {

	if (SDL_Init(SDL_INIT_VIDEO) >= 0) {

		data.window = SDL_CreateWindow("Stars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, data.screen.w, data.screen.h, SDL_WINDOW_SHOWN);
		data.surface = SDL_GetWindowSurface(data.window);

		srand(0);

		data.plasma.Init(data.screen, data.GetDeltaTime());

		for (int i = 0; i < data.maxStars; i++) {
			Star star{ data.screen, data.maxSpeed };
			data.stars.push_back(star);
		}

		data.status = data.window != NULL ? ProgramStatus::RUNNING : ProgramStatus::TERMINATE_ERROR;
	}
}

void Finalize(Data& data) {

	if (data.status == ProgramStatus::TERMINATE_OK) {
		SDL_DestroyWindow(data.window);
		SDL_Quit();
	}
}

void PollEvents(Data& data) {
	while (SDL_PollEvent(&data.e) != 0)
	{
		if (data.e.type == SDL_KEYDOWN) {
			if (data.e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				data.status = ProgramStatus::TERMINATE_OK;
			}
		}
		//User requests quit
		if (data.e.type == SDL_QUIT)
		{
			data.status = ProgramStatus::TERMINATE_OK;
		}
	}
}

void Update(Data& data) {

	for (Star& star : data.stars) {
		star.Update(data.screen, data.GetDeltaTime(), data.maxSpeed);
	}
	data.plasma.updatePlasma(data.screen, data.GetDeltaTime());
}

void Draw(Data& data) {

	SDL_FillRect(data.surface, NULL, SDL_MapRGB(data.surface->format, 0x0, 0x5, 0x10));

	SDL_LockSurface(data.surface);
	data.plasma.renderPlasma(*data.surface, data.screen);
	for (Star& star : data.stars) {
		star.Draw(data.surface);
	}
	SDL_UnlockSurface(data.surface);

	SDL_UpdateWindowSurface(data.window);
}

void Synch(Data& data) {

	std::this_thread::sleep_for(data.GetNextDelayTime());
	data.SetNextFrameTime();
}