export module stars;

import std.compat;
import definitions;
import timer;
import effect;

namespace MoleDemo {

	export class Stars;
	class Star;
}


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

	void Update(permille intensity, milliseconds delta);
	void Draw(std::function<void(Point2D pixel, rgbaColor color)> putPixel);
};

namespace MoleDemo {

	Star::Star(const Screen& screen, const speed& maxSpeed) :
		maxSpeed{ maxSpeed },
		screen{ screen } {

		Reset();
	}

	Star::~Star() {
	}

	void Star::Reset() {
		progress = 0;
		position = {
			rand() % screen.w,
			0
		};
		baseSpeed = 1 + rand() % maxSpeed;
		currentSpeed = baseSpeed;
		brightness = permilleFactor * baseSpeed / maxSpeed;
		color = {
			static_cast<channel>(rand() % saturated),
			static_cast<channel>(rand() % saturated),
			static_cast<channel>(rand() % saturated)
		};
	}
	void Star::Update(permille intensity, milliseconds deltaTime) {
		currentSpeed += deltaTime;
		progress += currentSpeed;
		position = {
			position.x,
			position.y + progress / permilleFactor
		};

		if (position.y >= screen.h) {
			Reset();
		}
		else {
			currentColor = dessaturated.lerp(color, intensity);
		}
	}

	void Star::Draw(std::function<void(Point2D, rgbaColor)> putPixel) {

		int_fast64_t y{ static_cast<int_fast64_t>(position.y) };
		int_fast16_t trail{ (int_fast16_t)brightness };
		permille fade{ permilleFactor / (int)(1 + currentSpeed / maxSpeed) };
		while (trail > 0 && y >= 0) {
			rgbaColor finalColor{ empty.lerp(currentColor, (permille)trail).rgba() };

			putPixel(Point2D{ position.x, (point1D)y }, finalColor);

			if (0 < position.x) {
				point1D left{ position.x - 1 };
				putPixel(Point2D{ left, (point1D)y }, finalColor);
			}
			if (screen.w > position.x) {
				point1D right{ position.x + 1 };
				putPixel(Point2D{ right, (point1D)y }, finalColor);
			}

			--y;
			trail -= fade;
		}
	}

	Stars::Stars(Timer* timer, Screen* screen) :
		Effect{ timer, screen }
	{
		ClearBuffer(transparent);
	}

	Stars::~Stars() {
	}

	void Stars::Load() {
		srand(0);
	}

	void Stars::Unload() {
	}

	void Stars::Update(permille intensity, milliseconds delta) {

		if (stars.size() < maxStars) {
			for (int i = 0; i < newStarsPerFrame; i++) {
				stars.push_back(Star{ *screen, maxSpeed });
			}
		}

		for (Star& star : stars) {
			star.Update(intensity, delta);
		}
	}

	void Stars::Cache(StencilBuffer& mask) {
		ClearBuffer(transparent);
		for (Star& star : stars) {
			star.Draw([&](Point2D point, rgbaColor color) { PutPixel(point, color); });
		}
	}
}
