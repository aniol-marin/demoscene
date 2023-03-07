#include <SDL.h>
import <iostream>;
import <vector>;
import <cstdlib>;
#include <thread>
#include <chrono>

enum class ProgramStatus {
	TERMINATE_OK,
	TERMINATE_ERROR,
	RUNNING,
};

struct Point2 {
	int x, y;
};

struct Color {
	int r, g, b, a;
};

class Star {
	Point2 position;
	int speed;
	double brightness;
	Color color;
	void Reset(Point2 screenSize, int maxSpeed, bool initial) {
		position.x = initial * (rand() % screenSize.x);
		position.y = rand() % screenSize.y;
		speed = 1 + rand() % maxSpeed;
		brightness = (double)speed / (double)maxSpeed;
		color.r = 0xFF - (rand() % 0x1F);
		color.g = 0xFF - (rand() % 0x1F);
		color.b = 0xFF - (rand() % 0x1F);
		color.a = 0xFF;
	}
public:
	Star(Point2 screenSize, int maxSpeed) {
		Reset(screenSize, maxSpeed, true);
	}
	void Update(Point2 screenSize, int maxSpeed) {
		position.x += speed;
		if (position.x >= screenSize.x) {
			Reset(screenSize, maxSpeed, false);
		}
	}

	void Draw(SDL_Surface* screenSurface) {

		int bpp = screenSurface->format->BytesPerPixel;

		double trail{ brightness };
		int nextOffset{ 0 };
		while (trail > 0.0) {

			Uint8* pixel = (Uint8*)screenSurface->pixels + position.y * screenSurface->pitch + (position.x - nextOffset) * bpp;
			nextOffset++;
			trail -= 0.01;

			if (trail > 0 && position.x - nextOffset >= 0) {
				pixel[0] = (Uint8)(color.b * trail);
				pixel[1] = (Uint8)(color.g * trail);
				pixel[2] = (Uint8)(color.r * trail);
			}
		}
	}
};

struct Data {
	const Point2 screenSize;
	std::vector<Star> stars;
	ProgramStatus status;
	const int maxSpeed;
	const int maxStars;
	const int delayFPS;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event e;
	Data(Point2 screenSize, int speed, int stars, int fps) :
		screenSize{ screenSize },
		maxSpeed{ speed },
		maxStars{ stars },
		delayFPS{ 1000 / fps } {}
};



void Init(Data& data);
void Finalize(Data& data);
void PollEvents(Data& data);
void Update(Data& data);
void Draw(Data& data);
void Synch(Data& data);

int main(int argc, char* args[])
{
	Data data{ Point2{640, 480},10, 100, 60 };
	Init(data);

	while (data.status == ProgramStatus::RUNNING) {
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

		data.window = SDL_CreateWindow("Stars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, data.screenSize.x, data.screenSize.y, SDL_WINDOW_SHOWN);
		data.surface = SDL_GetWindowSurface(data.window);

		srand(0);

		for (int i = 0; i < data.maxStars; i++) {
			Star star{ data.screenSize, data.maxSpeed };
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
		star.Update(data.screenSize, data.maxSpeed);
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
	std::this_thread::sleep_for(std::chrono::milliseconds(data.delayFPS));
}