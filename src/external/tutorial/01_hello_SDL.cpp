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

	Uint32* getPixel(SDL_Surface* surface, int x, int y) {

		return reinterpret_cast<Uint32*>((Uint8*)surface->pixels + position.y * surface->pitch + x * surface->format->BytesPerPixel);
	}

	void Draw(SDL_Surface* screenSurface) {

		int trail{ miliBrightness };
		Uint8 nextOffset{ 0 };
		while (trail > 0) {

			if (position.x - nextOffset >= 0) {
				Uint32* pixel = getPixel(screenSurface, position.x - nextOffset, position.y);
				*pixel = color.mLerp(trail);
			}

			trail -= 20;
			nextOffset++;
		}
	}
};

struct Data {
	const Screen screen;
	const Uint8 maxSpeed;
	const Uint8 maxStars;
	std::vector<Star> stars;
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
	ms GetNextDelayTime() { return  std::chrono::milliseconds{ 1000 / fps }; }//std::chrono::duration_cast<ms>(previousTime  - Now()) + frameTime; }
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

		for (int i = 0; i < data.maxStars; i++) {
			Star star{ data.screen, data.maxSpeed };
			data.stars.push_back(star);
		}
	}

	data.status = data.window != NULL ? ProgramStatus::RUNNING : ProgramStatus::TERMINATE_ERROR;
}

void Finalize(Data& data) {

	if (data.status == ProgramStatus::TERMINATE_OK) {
		SDL_DestroyWindow(data.window);
		SDL_Quit();
	}
}

void PollEvents(Data& data) {

	SDL_PollEvent(&data.e);
}

void Update(Data& data) {

	for (Star& star : data.stars) {
		star.Update(data.screen, data.GetDeltaTime(), data.maxSpeed);
	}
}

void Draw(Data& data) {

	SDL_FillRect(data.surface, NULL, SDL_MapRGB(data.surface->format, 0x0, 0x5, 0x10));
	for (Star& star : data.stars) {
		star.Draw(data.surface);
	}

	SDL_UpdateWindowSurface(data.window);
}

void Synch(Data& data) {

	std::this_thread::sleep_for(data.GetNextDelayTime());
	data.SetNextFrameTime();
}