import effects;

namespace MoleDemo {

	Star::Star(Screen* screenSize, const int maxSpeed) :
		screen{ screenSize } {
		Reset(*screenSize, maxSpeed, true);
	}

	Star::~Star() {
	}

	void Star::Reset(const Screen& screen, const uint8_t maxSpeed, const bool initial) {
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

	void Star::Update(const Screen& screen, uint16_t deltaTime, const int maxSpeed) {
		position.x += 1 + speed * deltaTime * maxSpeed / 100; // position shift must be at least 1 in order to avoid stalling for very low delta times at very slow speeds
		if (position.x >= screen.w) {
			Reset(screen, maxSpeed, false);
		}
	}

	void Star::Draw(std::function<void(Point2D pixel, uint32_t color)> putPixel) {

		int trail{ miliBrightness };
		uint8_t nextOffset{ 0 };
		while (trail > 0) {

			if (position.x - nextOffset >= 0) {
				putPixel(Point2D{ (uint16_t)(position.x - nextOffset), position.y }, color.mLerp(transparent, trail));
			}

			trail -= 20;
			nextOffset++;
		}
	}

	Stars::Stars(Timer* timer, Screen* screen) :
		Effect{ timer, screen }
	{
		ClearBuffer(0x0);
	}

	void Stars::Load() {
		int maxStars = 100;
		int maxSpeed = 10;
		srand(0);
		for (int i = 0; i < maxStars; i++) {
			Star star{ screen, maxSpeed };
			stars.push_back(star);
		}
	}

	void Stars::Unload() {
	}

	void Stars::Update(uint_fast16_t intensity) {

		uint16_t time = timer->GetDeltaTime();
		for (Star& star : stars) {
			star.Update(*screen, time, 1 + maxSpeed * intensity / 100);
		}
	}

	void Stars::Cache(std::vector<bool>& mask) {
		ClearBuffer(0x0);
		for (Star& star : stars) {
			star.Draw([&](Point2D point, uint32_t color) { PutPixel(point, color); });
		}
	}
}