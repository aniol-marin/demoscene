module effects;

namespace MoleDemo {

	Star::Star(Screen* screenSize, const uint_fast16_t& maxSpeed) :
		maxSpeed{ (uint_fast8_t)(maxSpeed) },
		screen{ screenSize } {
		Reset(*screenSize, maxSpeed, true);
	}

	Star::Star(const Star& star) :
		Star{ star.screen, star.maxSpeed } {}

	Star::~Star() {
	}

	void Star::Reset(const Screen& screen, const uint_fast16_t& maxSpeed, const bool initial) {
		position.x = initial * (rand() % screen.w);
		position.y = rand() % screen.h;
		speed = rand() % maxSpeed;
		brightness = permilleFactor * speed / maxSpeed;
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

	void Star::Update(const Screen& screen, milliseconds deltaTime, const int maxSpeed) {
		position.x += 1 + speed * deltaTime * maxSpeed / 100; // position shift must be at least 1 in order to avoid stalling for very low delta times at very slow speeds
		if (position.x >= screen.w) {
			Reset(screen, maxSpeed, false);
		}
	}

	void Star::Draw(std::function<void(Point2D pixel, rgbaColor color)> putPixel) {

		int_fast64_t trail{ brightness };
		int_fast64_t x{ position.x };
		while (trail > 0 && x >= 0) {

			putPixel(Point2D{ (point1D)x, position.y }, color.lerp(transparent, (permille)trail).rgba());

			--x;
			trail -= 20;
		}
	}

	Stars::Stars(Timer* timer, Screen* screen) :
		Effect{ timer, screen }
	{
		ClearBuffer(0x0);
	}

	Stars::~Stars() {
	}

	void Stars::Load() {
		uint_fast8_t maxStars = 100;
		uint_fast8_t maxSpeed = 10;
		srand(0);
		for (int i = 0; i < maxStars; i++) {
			Star star{ screen, maxSpeed };
			stars.push_back(star);
		}
	}

	void Stars::Unload() {
	}

	void Stars::Update(permille intensity) {

		milliseconds time = timer->GetDeltaTime();
		for (Star& star : stars) {
			star.Update(*screen, time, 1 + maxSpeed * intensity / 100);
		}
	}

	void Stars::Cache(StencilBuffer& mask) {
		ClearBuffer(transparent);
		for (Star& star : stars) {
			star.Draw([&](Point2D point, rgbaColor color) { PutPixel(point, color); });
		}
	}
}
