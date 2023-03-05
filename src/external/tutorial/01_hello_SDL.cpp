#include <SDL.h>
import <iostream>;
import <vector>;
import <cstdlib>;

struct Point2 {
	int x, y;
};

struct Color {
	int r, g, b, a;
};

struct Data {
	const Point2 screen;
	const int maxSpeed;
	const int maxStars;
	const int delayFPS;
	SDL_Surface* surface;
	Data(Point2 screen, int speed, int stars, int fps) :
		screen{ screen },
		maxSpeed{ speed },
		maxStars{ stars },
		delayFPS{ 1000 / fps } {}
};

class Star {
	Point2 position;
	int speed;
	double brightness;
	Color color;
	Data data;
public:
	Star(Data& data) :
		data{ data } {
		Reset(true);
	}
	void Update(SDL_Surface* screenSurface) {
		position.x += speed;
		if (position.x >= data.screen.x) Reset(false);

		int bpp = screenSurface->format->BytesPerPixel;

		double trail{ brightness };
		int nextOffset{ 0 };
		while (trail > 0.0) {

			Uint8* pixel = (Uint8*)screenSurface->pixels + position.y * screenSurface->pitch + position.x * bpp - nextOffset;
			nextOffset++;
			trail -= 0.01;

			if (trail > 0 && position.x - nextOffset >= 0) {
				pixel[0] = (Uint8)(color.r * trail);
				pixel[1] = (Uint8)(color.g * trail);
				pixel[2] = (Uint8)(color.b * trail);
			}
		}
	}
	void Reset(bool initial) {
		position.x = initial * (rand() % data.screen.x);
		position.y = rand() % data.screen.y;
		speed = 1 + rand() % data.maxSpeed;
		brightness = (double)speed / (double)data.maxSpeed;
		color.r = 0xFF - ((rand() % 20) / 100.0);
		color.g = 0xFF - ((rand() % 30) / 100.0);
		color.b = 0xFF - ((rand() % 10) / 100.0);
		color.a = 0xFF;
	}
};

void FillStars(SDL_Surface*, std::vector<Star>&);

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	Data data{ Point2{640, 480},10, 100, 15 };

	if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
		window = SDL_CreateWindow("Stars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, data.screen.x, data.screen.y, SDL_WINDOW_SHOWN);
		if (window != NULL) {

			data.surface = SDL_GetWindowSurface(window);
			SDL_Event e;
			SDL_PollEvent(&e);
			srand(0);
			std::vector<Star> stars{};
			for (int i = 0; i < data.maxStars; i++) {
				Star star{ data };
				stars.push_back(star);
			}

			while (e.type != SDL_QUIT) {
				SDL_FillRect(data.surface, NULL, SDL_MapRGB(data.surface->format, 0x0, 0x5, 0x10));
				FillStars(data.surface, stars);
				SDL_UpdateWindowSurface(window);
				SDL_PollEvent(&e);
				SDL_Delay(data.delayFPS);
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


void FillStars(SDL_Surface* surface, std::vector<Star>& stars) {
	for (Star& star : stars) {
		star.Update(surface);
	}
}