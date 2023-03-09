#include <SDL.h>

module demo;

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

using Uint1 = unsigned char;
using Uint2 = unsigned short int;
using Uint24 = std::bitset<24>;
using Window = SDL_Window;
using Surface = SDL_Surface;
using Event = SDL_Event;
using Time = std::chrono::system_clock::time_point;
auto& Now{ std::chrono::system_clock::now };
auto& TimeToUint{ std::chrono::system_clock::to_time_t };

struct Point2D {
	Uint16 x, y;
};

struct Screen {
	const Uint2 w, h;
	Screen(Uint2 width, Uint2 heigth) :
		w{ width },
		h{ heigth } {}
};

struct Color {
	Uint8 r, g, b, a;
	Uint24 rgb() const { return  r << sizeof(Uint8) * 2 + g << sizeof(Uint8) + b; }
	Uint32 rgba() const { return a << sizeof(Uint8) * 3 + r << sizeof(Uint8) * 2 + g << sizeof(Uint8) + b; }
};

class Star {
	Point2D position;
	Uint1 speed;
	Uint2 miliBrightness;
	Color color;
	void Reset(const Screen& screen, const Uint1 maxSpeed, const bool initial) {
		position.x = initial * (rand() % screen.w);
		position.y = rand() % screen.h;
		speed = 1 + rand() % maxSpeed;
		miliBrightness = (speed * 1000) / maxSpeed;
		color.r = 0xFF - (rand() % 0x1F);
		color.g = 0xFF - (rand() % 0x1F);
		color.b = 0xFF - (rand() % 0x1F);
		color.a = 0xFF;
	}
public:
	Star(const Screen& screenSize, const int maxSpeed) {
		Reset(screenSize, maxSpeed, true);
	}
	void Update(const Screen& screen, const int maxSpeed) {
		position.x += speed;
		if (position.x >= screen.w) {
			Reset(screen, maxSpeed, false);
		}
	}

	Uint24* getPixel(SDL_Surface* surface, int x, int y) {
		return static_cast<Uint24*>(surface->pixels) + position.y * surface->pitch + x;
	}

	void Draw(SDL_Surface* screenSurface) {

		int bpp = screenSurface->format->BytesPerPixel;

		Uint2 trail{ miliBrightness };
		int nextOffset{ 0 };
		while (trail > 0) {

			Uint24* pixel{ getPixel(screenSurface, position.x - nextOffset, position.y) };
			nextOffset++;
			trail -= 100;

			if (trail > 0 && position.x - nextOffset >= 0) {
				*pixel = color.rgb();
			}
		}
	}
};

struct Data {
	const Screen screen;
	const Uint8 maxSpeed;
	const Uint8 maxStars;
	std::vector<Star> stars;
	ProgramStatus status;
	Uint8 deltaTime;
	Window* window;
	Surface* surface;
	Event e;
	Data(Point2D screenSize, Uint1 speed, Uint1 stars, Uint1 fps) :
		screen{ screenSize.x, screenSize.y },
		maxSpeed{ speed },
		maxStars{ stars },
		initialTime{ Now() },
		msPerFrame{ (unsigned int)1000 / fps }
	{}
	int GetDeltaTime() const { return deltaTime; }
	int GetNextDelayTime() const { return TimeToUint(Now()) - TimeToUint(previousTime); }
	bool Running() const { return status == ProgramStatus::RUNNING; }
	void SetNextFrameTime() {
		previousTime = Now();
	}
private:
	const Uint16 msPerFrame;
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
	Data data{ Point2D{640, 480},10, 100, 60 };
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
		star.Update(data.screen, data.maxSpeed);
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

	std::this_thread::sleep_for(std::chrono::milliseconds(data.GetNextDelayTime()));
}